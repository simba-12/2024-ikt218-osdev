

// // #include <stdint.h>
// // #include "multiboot2.h"

// // #include "vga.h"
// // #include "gdt.h"
// // #include "idt.h"
// // #include "keyboard.h"
// // #include "util.h" 

// // int main(uint32_t magic, struct multiboot_tag *mb_info) {
// //     // Initialize VGA, GDT, and IDT
// //     vga_initialize();
// //     printf("Welcome to your OS kernel!\n");

// //     initGdt();
// //     printf("GDT is done\n");

// //     initIdt();
// //     // Enable interrupts
// //     asm volatile("sti");
// //     printf("IDT is done\n");
    
   

// //     //  // Trigger a breakpoint exception
// //     //asm volatile("int $0x00");
// //     //asm volatile("int $0x03");
// //     // asm volatile("int $0x06");


// //     // Test keyboard (uncomment if needed)
// //     initkeyboard();
// //      printf("Keyboard initialization done\n");

   

// //     // Infinite loop to halt CPU
// //     while (1) {
// //         // Uncomment the following line if you want to halt CPU
// //          asm volatile("hlt");
// //     }

// // return 0;
// // }




// #include <stdint.h>
// #include "multiboot2.h"
// #include "vga.h"
// #include "gdt.h"
// #include "idt.h"
// #include "keyboard.h"
// #include "util.h"
// #include "memory.h"

// extern uint32_t end;  // Declared to use the address where the kernel memory ends

// int main(uint32_t magic, struct multiboot_tag *mb_info) {
//     // Verify multiboot magic number
//     if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
//         vga_initialize();
//         printf("Error: Invalid magic number.\n");
//         while (1) { asm volatile("hlt"); }  // Halt the CPU on error
//     }
    

//     // Initialize VGA for text output
//     vga_initialize();
//     printf("Welcome to your OS kernel!\n");

//     // Initialize Global Descriptor Table
//     initGdt();
//     printf("GDT initialized.\n");

//     // Initialize Interrupt Descriptor Table
//     initIdt();
//     printf("IDT initialized.\n");

//     // Enable CPU interrupts
//     asm volatile("sti");

//     // Initialize the keyboard
//      initkeyboard();  // Corrected from initKeyboard to initkeyboard
//     printf("Keyboard initialization done\n");

//     // Initialize the kernel's memory manager using the end address of the kernel.
//     init_kernel_memory(&end);

//     // Initialize paging for memory management.
//     init_paging();

//     // Print memory information.
//     print_memory_layout();

//     // // Infinite loop to prevent the kernel from exiting
//      while (1) {
//          asm volatile("hlt");  // Halt the CPU to save power
//      }
//      // Print a hello world message.
//     printf("Hello World!\n");

//     // Call the C++ main function of the kernel.
//     //return kernel_main();
//     return 0;
// }






#include <stdint.h>
#include "multiboot2.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "util.h"
#include "memory.h"
#include <stdio.h> 
#include  "pit.h"

extern uint32_t end;  // Declared to use the address where the kernel memory ends

int main(uint32_t magic, struct multiboot_tag *mb_info) {
    // Verify multiboot magic number
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_initialize();
        printf("Error: Invalid magic number.\n");
        while (1) { asm volatile("hlt"); }  // Halt the CPU on error
    }
    

    // Initialize VGA for text output
    vga_initialize();
    printf("Welcome to your OS kernel!\n");

    // Initialize Global Descriptor Table
    initGdt();
    printf("GDT initialized.\n");

    // Initialize Interrupt Descriptor Table
    initIdt();
    printf("IDT initialized.\n");

    // Enable CPU interrupts
    asm volatile("sti");

    // Initialize the keyboard
    initkeyboard();  // Corrected from initKeyboard to initkeyboard
    printf("Keyboard initialization done\n");

    // Initialize the kernel's memory manager using the end address of the kernel.
    init_kernel_memory(&end);

    // Initialize paging for memory management.
    init_paging();

    // Print memory information.
    printf("Initial Memory Layout:\n");
    print_memory_layout();
    printf("\n");


//       init_pit();
//      while(true){
        
//          printf("[%d]: Sleeping with interrupts (LOW CPU).\n", timer_ticks);
//           sleep_interrupt(0);
//           printf("[%d]: Slept using interrupts.\n", timer_ticks++);

//     //     printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", timer_ticks);
//         sleep_busy(5000);
//         printf("[%d]: Slept using busy-waiting.\n", timer_ticks++);

//      };

//     // Call the C++ main function of the kernel.
//     return kernel_main();

// return 0;
// }




    // Allocate and free memory
    printf("Allocating memory...\n");
    void* ptr1 = malloc(1024);
    void* ptr2 = malloc(4096);
    char* ptr3 = (char*)malloc(2048); // Allocate memory using malloc
    printf("Memory allocated.\n");

    printf("Freeing memory...\n");
    free(ptr1);
    free(ptr3); // Free memory using free
    printf("Memory freed.\n");

    // Print memory layout after allocation and deallocation
    printf("\nMemory Layout After Allocation and Deallocation:\n");
    print_memory_layout();
    printf("\n");

    // Test edge case: allocate more memory than available
    printf("Attempting to allocate more memory than available...\n");
    void* ptr4 = malloc(0xFFFFFFFF);  // Try to allocate more memory than available
    if (ptr4 == NULL) {
        printf("Out of memory: Unable to allocate memory.\n");
    }

    // Infinite loop to prevent the kernel from exiting
    while (1) {
        asm volatile("hlt");  // Halt the CPU to save power
    }
    // Print a hello world message.
    printf("Hello World!\n");

    // Call the C++ main function of the kernel.
    //return kernel_main();
    return 0;
}
