
#include <stdbool.h>  // Include for bool, true, and false
#include "memory.h"
#include "util.h"  // Assumed to contain utility functions like memset

typedef struct {
    uint32_t status;
    uint32_t size;
} alloc_t;


// Bitmap for physical memory management
uint8_t physicalMemoryBitmap[NUM_PAGE_FRAMES / 8];

// Page directory and usage arrays
static uint32_t pageDirs[NUM_PAGES_DIRS][1024] __attribute__((aligned(4096)));
static uint8_t pageDirUsed[NUM_PAGES_DIRS];
static uint32_t* page_directory = 0;   // Define a pointer to the page directory and initialize it to zero
static uint32_t page_dir_loc = 0;      // Define the location of the page directory and initialize it to zero
static uint32_t* last_page = 0; 

// Global variables for heap management
uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;

void init_kernel_memory(uint32_t* kernel_end) {
    // Clear the bitmap initially
    memset(physicalMemoryBitmap, 0, sizeof(physicalMemoryBitmap));

    // Bitmap approach for page management
    size_t kernel_end_page = ((size_t)kernel_end) / 4096;  // Convert address to page number
    for (size_t i = 0; i <= kernel_end_page; i++) {
        size_t byte_index = i / 8;
        size_t bit_index = i % 8;
        physicalMemoryBitmap[byte_index] |= (1 << bit_index);
    }

    // Initialize the heap for general-purpose allocations
    last_alloc = (uint32_t)kernel_end + 0x1000;
    heap_begin = last_alloc;
    pheap_end = 0x400000;
    pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
    heap_end = pheap_begin;
    memset((uint8_t*)heap_begin, 0, heap_end - heap_begin);
    pheap_desc = (uint8_t*)malloc(MAX_PAGE_ALIGNED_ALLOCS);
    memset(pheap_desc, 0, MAX_PAGE_ALIGNED_ALLOCS);
}



void free(void* ptr) {
    // Check if the pointer is within the page heap or general heap range
    if ((uint32_t)ptr >= pheap_begin && (uint32_t)ptr < pheap_end) {
        // It's a page-aligned allocation, handle with pfree
        pfree(ptr);
    } else if ((uint32_t)ptr >= heap_begin && (uint32_t)ptr < heap_end) {
        // It's a regular heap allocation, find the header and free
        alloc_t* alloc = (alloc_t*)((uint32_t)ptr - sizeof(alloc_t));
        alloc->status = 0;
        memory_used -= alloc->size + sizeof(alloc_t);
    } else {
        // Handle error - pointer is not within any known range
        printf("free: Invalid pointer %p\n", ptr);
    }
}

char* pmalloc(size_t size) {
    // Ensure the allocation size is page-aligned
    if (size & 0xFFF) {
        size &= 0xFFFFF000;
        size += 0x1000;
    }
    
    // Search for a free page in the page heap
    for (int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++) {
        if (pheap_desc[i] == 0) {
            pheap_desc[i] = 1; // Mark as used
            uint32_t addr = pheap_begin + (i * 4096);
            memory_used += size;
            return (char*)addr;
        }
    }
    
    // Out of memory
    printf("pmalloc: Out of memory\n");
    return NULL;
}

void pfree(void* ptr) {
    // Calculate the index into the page heap
    uint32_t index = ((uint32_t)ptr - pheap_begin) / 4096;
    if (index < MAX_PAGE_ALIGNED_ALLOCS) {
        pheap_desc[index] = 0; // Mark as free
        memory_used -= 4096; // Update memory used
    } else {
        // Handle error - pointer is not within page heap range
        printf("pfree: Invalid pointer %p\n", ptr);
    }
}

void print_memory_layout() {
    printf("Memory Layout:\n");
    printf("Memory used: %d bytes\n", memory_used);
    printf("Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
    printf("Heap size: %d bytes\n", heap_end - heap_begin);
    printf("Heap start: 0x%X\n", heap_begin);
    printf("Heap end: 0x%X\n", heap_end);
    printf("PHeap start: 0x%X\n", pheap_begin);
    printf("PHeap end: 0x%X\n", pheap_end);
}

// Function to map virtual addresses to physical addresses
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
    uint16_t id = virt >> 22;        // Get the upper 10 bits of the virtual address to use as index in the page directory
    for(int i = 0; i < 1024; i++)   // Loop through all 1024 page table entries
    {
        last_page[i] = phys | 3;    // Set the page table entry to the physical address with the present and write permissions set
        phys += 4096;               // Increment the physical address by the page size of 4 KB
    }
    page_directory[id] = ((uint32_t)last_page) | 3;  // Set the page directory entry for the virtual address to the physical address of the page table with present and write permissions set
    last_page = (uint32_t *)(((uint32_t)last_page) + 4096); // Move to the next page in memory
}

// Function to enable paging
void paging_enable()
{
    asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc)); // Load the physical address of the page directory into the CR3 register
    asm volatile("mov %cr0, %eax");         // Load the CR0 register into the EAX register
    asm volatile("orl $0x80000000, %eax");  // Set the paging enable bit in the EAX register
    asm volatile("mov %eax, %cr0");         // Load the EAX register into the CR0 register to enable paging
}



void init_paging()
{
    printf("Setting up paging\n");
    page_directory = (uint32_t*)0x400000;      // Set the page directory to start at 4 MB
    page_dir_loc = (uint32_t)page_directory;  // Set the physical address of the page directory
    last_page = (uint32_t *)0x404000;         // Set the last page to start at 4 MB + 4 KB
    for(int i = 0; i < 1024; i++)             // Loop through all 1024 page directory entries
    {
        page_directory[i] = 0 | 2;            // Set the page directory entry to not present with supervisor level read/write permissions
    }
     paging_map_virtual_to_phys(0, 0);         // Map the first 4 MB of virtual memory to the first 4 MB of physical memory
     paging_map_virtual_to_phys(0x400000, 0x400000); // Map the next 4 MB of virtual memory to the next 4 MB of physical memory
     paging_enable();                          // Enable paging
     printf("Paging was successfully enabled!\n");
 }

void* malloc(size_t size) {
    // Align the size to 4 bytes
    size = (size + 3) & ~3;

    // Check if the size is suitable for page-based allocation
    if (size >= SOME_THRESHOLD) {
        // Call the page-based allocation function
        return pmalloc(size);
    }

    // Loop through blocks to find an available block with enough size
    uint8_t* mem = (uint8_t*)heap_begin;
    while ((uint32_t)mem < last_alloc) {
        alloc_t* a = (alloc_t*)mem;

        // If the current block is free and large enough, use it
        if (!a->status && a->size >= size) {
            a->status = 1;  // Mark block as used
            memory_used += a->size + sizeof(alloc_t);
            return mem + sizeof(alloc_t);
        }

        // Move to the next block
        mem += a->size + sizeof(alloc_t);
    }

    // No suitable block found in the existing heap, expand the heap
    if (last_alloc + size + sizeof(alloc_t) >= heap_end) {
        // Heap is full, cannot allocate
        return NULL;
    }

    // Create a new block at the end of the heap
    alloc_t* alloc = (alloc_t*)last_alloc;
    alloc->status = 1;  // Mark block as used
    alloc->size = size;

    // Move the last_alloc pointer up for the next allocation
    last_alloc += size + sizeof(alloc_t);

    memory_used += size + sizeof(alloc_t);
    return (void*)((uint32_t)alloc + sizeof(alloc_t));
}


