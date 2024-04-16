

#include <stdint.h>
#include "multiboot2.h"

#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "util.h" 

int main(uint32_t magic, struct multiboot_tag *mb_info) {
    // Initialize VGA, GDT, and IDT
    vga_initialize();
    printf("Welcome to your OS kernel!\n");

    initGdt();
    printf("GDT is done\n");

    initIdt();
    // Enable interrupts
    asm volatile("sti");
    printf("IDT is done\n");
    
   

    //  // Trigger a breakpoint exception
    //asm volatile("int $0x00");
     //asm volatile("int $0x03");
    // asm volatile("int $0x06");




    

    // Test keyboard (uncomment if needed)
    initkeyboard();
     printf("Keyboard initialization done\n");

   

    // Infinite loop to halt CPU
    while (1) {
        // Uncomment the following line if you want to halt CPU
         //asm volatile("hlt");
    }

return 0;
}
