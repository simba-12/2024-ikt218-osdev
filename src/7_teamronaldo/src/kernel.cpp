#include "memory.h"
#include "vga.h"


void* operator new(size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// For C++14 sized deallocation (required by C++20 as warnings indicate)
void operator delete(void* ptr, size_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept {
    free(ptr);
}


 extern "C" int kernel_main(void);
int kernel_main(){
  // Allocate and free memory
    void* ptr1 = malloc(1024);
    void* ptr2 = malloc(4096);
    char* ptr3 = (char*)malloc(2048); // Allocate memory using malloc
    free(ptr1);
    free(ptr3); // Free memory using free
    print_memory_layout();
    void* ptr4 = malloc(0xFFFFFFFF);  // Try to allocate more memory than available
    if (ptr4 == NULL) {
        //printf("Out of memory: Unable to allocate memory.\n");
    }

     return 0;

}