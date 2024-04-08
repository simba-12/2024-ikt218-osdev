#include <stdint.h>
#include <multiboot2.h> // Assuming this is the correct header file

// Include the prototype for kernel_main
extern int kernel_main(uint32_t magic, struct multiboot_info* mb_info_addr);

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    // Call the C++ kernel_main function

    //asm volatile("int $0x1");

    return kernel_main(magic, mb_info_addr);
}
