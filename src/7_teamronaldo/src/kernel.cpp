// // // // // // // #define IRQ0_TIMER 32
// // // // // // // #define IRQ1_KEYBOARD 33

// // // // // // // extern "C" {
// // // // // // //     #include "libc/gdt.h"
// // // // // // //     #include "libc/terminal.h"
// // // // // // //     #include "arch/i386/interrupts/interrupts.h"
// // // // // // //     #include "arch/i386/interrupts/keyboard.h"
// // // // // // //     #include "arch/i386/interrupts/idt.h"
// // // // // // //     #include "arch/i386/interrupts/irq.h"
// // // // // // //     #include "arch/i386/interrupts/isr.h"


// // // // // // // }

// // // // // // // // Function declarations for ISR handlers and IDT initialization
// // // // // // // extern "C" void isr0_handler() {
// // // // // // //     // ISR 0 handler implementation
// // // // // // //     terminal_writestring("ISR 0 triggered\n");
// // // // // // // }

// // // // // // // extern "C" void isr1_handler() {
// // // // // // //     // ISR 1 handler implementation
// // // // // // //     terminal_writestring("ISR 1 triggered\n");
// // // // // // // }

// // // // // // // extern "C" void isr2_handler() {
// // // // // // //     // ISR 2 handler implementation
// // // // // // //     terminal_writestring("ISR 2 triggered\n");
// // // // // // // }

// // // // // // // extern "C" void init_idt();

// // // // // // // // Assume terminal_writestring and other terminal functions are defined elsewhere in your kernel
// // // // // // // extern void terminal_writestring(const char*);
// // // // // // // extern void terminal_initialize(void); // If you have a separate initialization function for terminal

// // // // // // // // Kernel entry point
// // // // // // // extern "C" int kernel_main(uint32_t magic, struct multiboot_info* mb_info_addr) {
// // // // // // //     terminal_initialize();  // Initialize the terminal if not already done
// // // // // // //     terminal_writestring("Hello, World! kernel.cpp \n");

// // // // // // //     // Initialize the GDT
// // // // // // //     init_gdt();
// // // // // // //     terminal_writestring("GDT setup successfully. kernel.cpp\n");

// // // // // // //     // Initialize IDT and register interrupt handlers
// // // // // // //     init_idt(); // Assuming this function is implemented to initialize your IDT
// // // // // // //     register_interrupt_handler(IRQ0_TIMER, isr0_handler); // IRQ numbers are used for clarity
// // // // // // //     register_interrupt_handler(IRQ1_KEYBOARD, isr1_handler);


// // // // // // //     // Initialize the keyboard
// // // // // // //     init_keyboard();
// // // // // // //     terminal_writestring("Keyboard initialized from kernel.cpp\n");

// // // // // // //     // Uncomment the following lines to test the ISRs after implementation
// // // // // // //     asm volatile("int $0x00"); // Test interrupt 0
// // // // // // //     asm volatile("int $0x01"); // Test interrupt 1
// // // // // // //     asm volatile("int $0x02"); // Test interrupt 2
// // // // // // //     //asm volatile("int $0x21");

// // // // // // //     // Enter an infinite loop or your main scheduler if you have one
// // // // // // //     while(1) { /* Halt CPU or perform other operations */ }

// // // // // // //     return 0;
// // // // // // // }






// // // // // // #define IRQ0_TIMER 32
// // // // // // //#define IRQ1_KEYBOARD 33

// // // // // // extern "C" {
// // // // // //     #include "libc/gdt.h"
// // // // // //     #include "libc/terminal.h"

// // // // // //     #include "arch/i386/interrupts/idt.h"
// // // // // //     #include "arch/i386/interrupts/util.h"
// // // // // //     #include "arch/i386/interrupts/vga.h"

// // // // // // }

// // // // // // // Assume terminal_writestring and other terminal functions are defined elsewhere in your kernel
// // // // // // extern void terminal_writestring(const char*);
// // // // // // extern void terminal_initialize(void); // If you have a separate initialization function for terminal

// // // // // // // Kernel entry point
// // // // // // extern "C" int kernel_main(uint32_t magic, struct multiboot_info* mb_info_addr) {
// // // // // //     terminal_initialize();  // Initialize the terminal if not already done
// // // // // //     terminal_writestring("Hello, World! kernel.cpp \n");

// // // // // //     // Initialize the GDT
// // // // // //     //init_gdt();
// // // // // //     initGdt();

// // // // // //     terminal_writestring("GDT setup successfully. kernel.cpp\n");

// // // // // //     initIdt();
// // // // // //   


// // // // // //     // Uncomment the following lines to test the ISRs after implementation
// // // // // //      //asm volatile("int $0x00"); // Test interrupt 0
// // // // // //      //asm volatile("int $0x01"); // Test interrupt 1
// // // // // //      //asm volatile("int $0x02"); // Test interrupt 2

// // // // // //     // Enter an infinite loop or your main scheduler if you have one
// // // // // //     while(1) { /* Halt CPU or perform other operations */ }

// // // // // //     return 0;
// // // // // // }




// // //  extern "C" {
// // //     #include "libc/gdt.h"
// // //     #include "libc/terminal.h"
// // //     #include "arch/i386/interrupts/idt.h"
// // //     #include "arch/i386/interrupts/util.h"
// // //     #include "arch/i386/interrupts/vga.h"
// // //     #include "multiboot2.h" // Make sure this include is correct

// // //     int kernel_main(uint32_t magic, struct multiboot_tag *mb_info) {
// // //         terminal_initialize();
// // //         terminal_writestring("Hello, World! kernel.cpp \n");

// // //         initGdt();
// // //         terminal_writestring("GDT setup successfully. kernel.cpp\n");

// // //         initIdt();
// // //         terminal_writestring("IDT setup successfully. kernel.cpp\n");

    
// // //         while(1) {
// // //             // Halt CPU or perform other operations
// // //             asm volatile("hlt");
// // //         }

// // //         return 0; // This line will not be reached
// // //     }
// // // }









// // // // // extern "C" {
// // // // //     #include "libc/gdt.h"
// // // // //     #include "libc/terminal.h"
// // // // //     #include "arch/i386/interrupts/idt.h"
// // // // //     #include "arch/i386/interrupts/util.h"
// // // // //     #include "arch/i386/interrupts/vga.h"
// // // // //     #include "multiboot2.h" // Make sure this is the correct header for multiboot information.

// // // // //     // Prototype for an interrupt handler function, this should be defined in your IDT setup
// // // // //     extern void isr0(); // Division by zero handler.

// // // // //     int kernel_main(uint32_t magic, struct multiboot_tag *mb_info) {
// // // // //         terminal_initialize();
// // // // //         terminal_writestring("Hello, World! kernel.cpp \n");

// // // // //         // Initialize Global Descriptor Table.
// // // // //         initGdt();
// // // // //         terminal_writestring("GDT setup successfully. kernel.cpp\n");

// // // // //         // Initialize Interrupt Descriptor Table.
// // // // //         initIdt();
// // // // //         terminal_writestring("IDT setup successfully. kernel.cpp\n");

// // // // //         // Enable CPU interrupts.
// // // // //         asm volatile("sti");

// // // // //         // Test Division By Zero interrupt.
// // // // //         // Comment out this line when not testing interrupts.
// // // // //         // Remember, triggering interrupt 0 will cause the Division By Zero handler (isr0) to be executed.
//     // // // //         asm volatile("int $0x00");

// // // // //         // If the Division By Zero handler is set to halt the system, the execution should not proceed beyond this point.
// // // // //         // Hence, the following message should not appear on the screen if the ISR is working correctly.
// // // // //         terminal_writestring("This point should not be reached if ISR is halting the system.\n");

// // // // //         // Halt the CPU or perform other operations.
// // // // //         while(1) {
// // // // //             // This halts the CPU until the next interrupt is fired, which is more power-efficient than a spin wait.
// // // // //             asm volatile("hlt");
// // // // //         }

// // // // //         // The return statement here is purely for compliance with the "int" function return type.
// // // // //         // In a correctly functioning kernel that halts or enters a scheduler in the loop above,
// // // // //         // this line is effectively unreachable.
// // // // //         return 0;
// // // // //     }
// // // // // }


// // // #include <stdint.h>
// // // #include "multiboot2.h"
// // // #include "terminal.h"  // Ensure this file includes declarations for terminal functions
// // // #include "types.h"

// // // extern "C" {
// // //     int kernel_main(uint32_t magic, struct multiboot_tag *mb_info);
// // // }

// // // int kernel_main(uint32_t magic, struct multiboot_tag *mb_info) {
// // //     // Ensure magic number is correct
// // //     if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
// // //         // Handle error: invalid magic number
// // //         while (1) {}  // Hang if the magic number is wrong
// // //     }

// // // //     // Setup kernel which includes terminal initialization
// // // //    terminal_initialize();

// // // //     // Print "Hello World" to the terminal
// // // //     terminal_writestring("Hello World \n");
// // // //     // Initialize GDT
   
   
// // //     return 0;
// // // }

// // #include <stdint>  // Include for uint32_t
// // #include "multiboot2.h"  // Ensure this is correctly included if needed for struct multiboot_tag

// // extern "C" {
// //     int kernel_main(uint32_t magic, struct multiboot_tag *mb_info);
// // }

// // int kernel_main(uint32_t magic, struct multiboot_tag *mb_info) {
// //     // Ensure magic number is correct
// //     if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
// //         // Handle error: invalid magic number
// //         while (1) {}  // Hang if the magic number is wrong
// //     }

// //     // Your initialization code here
// //     return 0;
// // }
 

// // #include <stdint.h>  // Include for uint32_t
// // #include "multiboot2.h"  // Ensure this is correctly included if needed for struct multiboot_tag




// // int main(int argc, char *argv[]) {

    
// //     // Your initialization code here
// //     vga_initialize();
// //     //asm volatile ("int $0x00"); //Test
    

// //  vga_write_string("Hello from GDT!");
// //     // Your code here
// //     return 0;
// // }








// //  extern "C" {
// //     #include "libc/gdt.h"
// //     #include "libc/terminal.h"
// //     #include "arch/i386/interrupts/idt.h"
// //     #include "arch/i386/interrupts/util.h"
// //     #include "arch/i386/interrupts/vga.h"
// //     #include "multiboot2.h" // Make sure this include is correct

  

// #include <stdint.h>
// #include "multiboot2.h"
// #include "vga.h"

// int main(uint32_t magic, struct multiboot_tag *mb_info) {
//     // Initialize VGA
//     vga_initialize();

//     // Print message using vga_write_string
//     vga_write_string("Hello, Kernel World!\n");

//     return 0;
// }

// //     // Initialize GDT
// //     initGdt();
// //     vga_write_string("GDT setup successfully. kernel.cpp\n");

// //     // Initialize IDT
// //     initIdt();
// //     vga_write_string("IDT setup successfully. kernel.cpp\n");

// //     // // Infinite loop to halt CPU
// //     // while (1) {
// //     //     // Halt CPU or perform other operations
// //     //     asm volatile("hlt");
// //     // }
// // }