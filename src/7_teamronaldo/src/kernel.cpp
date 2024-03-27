
extern "C" {
    #include "libc/gdt.h"
    #include "libc/terminal.h"
    #include "../../../arch/i386/interrupts/interrupts.h"
    #include "../../../arch/i386/interrupts/keyboard.h"
   


}

// Assume terminal_writestring is defined elsewhere in your kernel
extern void terminal_writestring(const char*);

extern "C" int kernel_main() {
    static int run_count = 0;
    if (run_count == 0) {
        terminal_writestring("Hello, World! \n");
        run_count++;
    } else {
        terminal_writestring("Entered kernel_main again!\n");
    }
   
    // Initialize the GDT
     init_gdt();
    // Print confirmation message using a kernel-specific function
    terminal_writestring("GDT setup successfully.\n");
    
    // Further kernel initialization...
     // Initialize the keyboard
    init_keyboard();
    terminal_writestring("Keyboard initialized.\n");


    return 0;
}



// // // These are the include directives for your GDT, terminal output, and keyboard handler.
// // extern "C" {
// //     #include "libc/gdt.h"
// //     #include "libc/terminal.h"
// //     #include "arch/i386/interrupts/keyboard.h"
// // }

// // // Forward declaration of a function that prints strings to the terminal.
// // extern void terminal_writestring(const char*);

// // // The Keyboard Interrupt Service Routine should be defined somewhere in your keyboard handler.
// // // It's the function that gets called whenever a keyboard interrupt occurs.
// // extern void keyboard_interrupt_handler();

// // // This function will be used as an idle loop for your kernel.
// // void kernel_main_loop() {
// //     // This is a simple idle loop.
// //     // The 'hlt' instruction halts the CPU until the next interrupt is fired, which is efficient.
// //     while (true) {
// //         asm volatile ("hlt");
// //     }
// // }

// // // This is the entry point of your kernel after the bootloader hands off control.
// // extern "C" int kernel_main() {
// //     static int run_count = 0;
// //     if (run_count == 0) {
// //         terminal_writestring("Hello, World! \n");
// //         run_count++;
// //     } else {
// //         terminal_writestring("Entered kernel_main again!\n");
// //     }
   
// //     // Initialize the Global Descriptor Table (GDT).
// //     init_gdt();
// //     terminal_writestring("GDT setup successfully.\n");
    
// //     // Initialize the keyboard.
// //     init_keyboard();
// //     terminal_writestring("Keyboard initialized.\n");

// //     // Register the keyboard interrupt handler.
// //     // This is hypothetical; the actual function name or mechanism might differ.
// //     // For example, it could be something like this:
// //     // register_interrupt_handler(IRQ1_KEYBOARD, keyboard_interrupt_handler);
    
// //     // Enter the kernel's main loop.
// //     kernel_main_loop();

// //     // Code should never reach this point.
// //     return 0;
// // }


// // // extern "C" {
// // //     #include "libc/gdt.h"
// // //     #include "libc/terminal.h"
// // //     #include "../../../arch/i386/interrupts/keyboard.h"
   


// // // }

// // // // Assume terminal_writestring is defined elsewhere in your kernel
// // // extern void terminal_writestring(const char*);

// // // extern "C" int kernel_main() {
// // //     static int run_count = 0;
// // //     if (run_count == 0) {
// // //         terminal_writestring("Hello, World! \n");
// // //         run_count++;
// // //     } else {
// // //         terminal_writestring("Entered kernel_main again!\n");
// // //     }
   
// // //     // Initialize the GDT
// // //      init_gdt();
// // //     // Print confirmation message using a kernel-specific function
// // //     terminal_writestring("GDT setup successfully.\n");
    
// // //     // Further kernel initialization...
// // //      // Initialize the keyboard
// // //     init_keyboard();
// // //     terminal_writestring("Keyboard initialized.\n");




// // //     return 0;
// // // }



// // // These are the include directives for your GDT, terminal output, and keyboard handler.
// // extern "C" {
// //     #include "libc/gdt.h"
// //     #include "libc/terminal.h"
// //     #include "arch/i386/interrupts/keyboard.h"
// // }

// // // Forward declaration of a function that prints strings to the terminal.
// // extern void terminal_writestring(const char*);

// // // The Keyboard Interrupt Service Routine should be defined somewhere in your keyboard handler.
// // // It's the function that gets called whenever a keyboard interrupt occurs.
// // extern void keyboard_interrupt_handler();

// // // This function will be used as an idle loop for your kernel.
// // void kernel_main_loop() {
// //     // This is a simple idle loop.
// //     // The 'hlt' instruction halts the CPU until the next interrupt is fired, which is efficient.
// //     while (true) {
// //         asm volatile ("hlt");
// //     }
// // }

// // // This is the entry point of your kernel after the bootloader hands off control.
// // extern "C" int kernel_main() {
// //     static int run_count = 0;
// //     if (run_count == 0) {
// //         terminal_writestring("Hello, World! \n");
// //         run_count++;
// //     } else {
// //         terminal_writestring("Entered kernel_main again!\n");
// //     }
   
// //     // Initialize the Global Descriptor Table (GDT).
// //     init_gdt();
// //     terminal_writestring("GDT setup successfully.\n");
    
// //     // Initialize the keyboard.
// //     init_keyboard();
// //     terminal_writestring("Keyboard initialized.\n");

// //     // Register the keyboard interrupt handler.
// //     // This is hypothetical; the actual function name or mechanism might differ.
// //     // For example, it could be something like this:
// //     // register_interrupt_handler(IRQ1_KEYBOARD, keyboard_interrupt_handler);
    
// //     // Enter the kernel's main loop.
// //     kernel_main_loop();

// //     // Code should never reach this point.
// //     return 0;
// // }

// #include "libc/gdt.h"
// #include "libc/terminal.h"
// #include "../../../arch/i386/interrupts/interrupts.h"
// #include "../../../arch/i386/interrupts/keyboard.h"

// // Assume terminal_writestring and terminal_readchar are defined elsewhere in your kernel
// extern "C" void terminal_writestring(const char*);
// extern "C" char terminal_readchar();

// // ISR for keyboard (this needs to be written and linked to the actual keyboard interrupt)
// extern "C" void keyboard_isr_handler();

// // Keyboard buffer (this is a simplistic representation, you'll want a proper ring buffer)
// #define KEYBOARD_BUFFER_SIZE 256
// char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
// unsigned int keyboard_buffer_write_index = 0;
// unsigned int keyboard_buffer_read_index = 0;

// // Function to read a character from the keyboard buffer
// char read_char_from_keyboard_buffer() {
//     // If the read index is equal to the write index, there is no new data
//     if (keyboard_buffer_read_index == keyboard_buffer_write_index) {
//         return '\0';  // No new character
//     }
    
//     char ch = keyboard_buffer[keyboard_buffer_read_index];
//     keyboard_buffer_read_index = (keyboard_buffer_read_index + 1) % KEYBOARD_BUFFER_SIZE;
//     return ch;
// }

// // Main kernel loop
// void kernel_main_loop() {
//     while (true) {
//         // Halt the CPU until an interrupt happens
//         asm volatile ("hlt");
        
//         // Process keyboard input if available
//         char ch = read_char_from_keyboard_buffer();
//         if (ch != '\0') {
//             // Do something with the character
//             // For example, echo it back to the terminal
//             char str[2] = {ch, '\0'};
//             terminal_writestring(str);
//         }
//     }
// }

// extern "C" int kernel_main() {
//     // Initialize the GDT
//     init_gdt();
//     terminal_writestring("GDT setup successfully.\n");

//     // Initialize the keyboard and register the ISR
//     init_keyboard();
//     terminal_writestring("Keyboard initialized.\n");
//     register_interrupt_handler(IRQ1_KEYBOARD, keyboard_isr_handler);

//     // Enter the kernel's main loop
//     kernel_main_loop();

//     // The code should never reach this point
//     return 0;
// }


// extern "C" {
//     #include "gdt.h"
//     #include "terminal.h"
//     #include "../../../arch/i386/interrupts/interrupts.h"
//     #include "../../../arch/i386/interrupts/keyboard.h"
//     // You can include other C headers that need C linkage here.
// }

// // Assume these functions are defined in their respective C files
// extern "C" void init_gdt();
// extern "C" void init_keyboard();

// extern "C" int kernel_main() {
//     terminal_initialize(); // Initialize your terminal first
//     terminal_writestring("Kernel Initialized\n");

//     init_gdt(); // Initialize the Global Descriptor Table
//     terminal_writestring("GDT initialized.\n");

//     init_keyboard(); // Set up keyboard handling
//     terminal_writestring("Keyboard ready. Type something:\n");

//     // Enable interrupts on the processor (if not already enabled in init_keyboard)
//     asm volatile("sti");

//     while(true) {
//         asm volatile("hlt"); // Wait for the next interrupt
//     }
//     return 0; // We should never get here
// }
