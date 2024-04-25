

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {  // Ensure C linkage for C++ compilers.
#endif

// Function prototypes for memory management
void init_kernel_memory(uint32_t* kernel_end);
void* malloc(size_t size);
void free(void* ptr);
void init_paging();
void print_memory_layout();
char* pmalloc(size_t size);
void pfree(void* ptr);

// Constants for the memory management
#define NUM_PAGES_DIRS 256
#define NUM_PAGE_FRAMES (0x100000000 / 0x1000 / 8)
#define MAX_PAGE_ALIGNED_ALLOCS 32
#define SOME_THRESHOLD 4096  // This is just an example value.


// Declaration of global variables for memory management
extern uint8_t physicalMemoryBitmap[NUM_PAGE_FRAMES / 8];
extern uint32_t last_alloc;
extern uint32_t heap_end;
extern uint32_t heap_begin;
extern uint32_t pheap_begin;
extern uint32_t pheap_end;
extern uint8_t *pheap_desc;
extern uint32_t memory_used;

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H
