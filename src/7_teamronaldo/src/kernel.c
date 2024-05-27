#include <stdint.h>
#include "multiboot2.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "util.h"
#include "memory.h"
#include "pit.h" // Include PIT header file
#include "song.h" // Include Song header file
#include "song_player.h"

extern uint32_t end;  // Declared to use the address where the kernel memory ends
extern int kernel_main();
int main(uint32_t magic, struct multiboot_tag *mb_info) {
    // Verify multiboot magic number
    if (magic != (uint32_t)MULTIBOOT2_BOOTLOADER_MAGIC) {
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
    initkeyboard();
    printf("Keyboard initialization done\n");

    // Initialize the kernel's memory manager using the end address of the kernel.
    init_kernel_memory(&end);

    // Initialize paging for memory management.
    init_paging();

    // Print memory information.
    printf("Initial Memory Layout:\n");
    print_memory_layout();
    printf("\n");

    // Initialize PIT for music
    init_pit();

 

    // Infinite loop to continuously play songs
    kernel_main();

    return 0;
}
