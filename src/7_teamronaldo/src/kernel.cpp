#define IRQ0_TIMER 32
#define IRQ1_KEYBOARD 33

extern "C" {
    #include "libc/gdt.h"
    #include "libc/terminal.h"
    #include "arch/i386/interrupts/interrupts.h"
    #include "arch/i386/interrupts/keyboard.h"
}

// Function declarations for ISR handlers and IDT initialization
extern "C" void isr0_handler() {
    // ISR 0 handler implementation
    terminal_writestring("ISR 0 triggered\n");
}

extern "C" void isr1_handler() {
    // ISR 1 handler implementation
    terminal_writestring("ISR 1 triggered\n");
}

extern "C" void isr2_handler() {
    // ISR 2 handler implementation
    terminal_writestring("ISR 2 triggered\n");
}

extern "C" void init_idt();

// Assume terminal_writestring and other terminal functions are defined elsewhere in your kernel
extern void terminal_writestring(const char*);
extern void terminal_initialize(void); // If you have a separate initialization function for terminal

// Kernel entry point
extern "C" int kernel_main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    terminal_initialize();  // Initialize the terminal if not already done
    terminal_writestring("Hello, World! \n");

    // Initialize the GDT
    init_gdt();
    terminal_writestring("GDT setup successfully.\n");

    // Initialize IDT and register interrupt handlers
    init_idt(); // Assuming this function is implemented to initialize your IDT
    register_interrupt_handler(IRQ0_TIMER, isr0_handler); // IRQ numbers are used for clarity
    register_interrupt_handler(IRQ1_KEYBOARD, isr1_handler);

    // Initialize the keyboard
    init_keyboard();
    terminal_writestring("Keyboard initialized\n");

    // Uncomment the following lines to test the ISRs after implementation
    asm volatile("int $0x00"); // Test interrupt 0
    asm volatile("int $0x01"); // Test interrupt 1
    asm volatile("int $0x02"); // Test interrupt 2
    //asm volatile("int $0x21");

    // Enter an infinite loop or your main scheduler if you have one
    while(1) { /* Halt CPU or perform other operations */ }

    return 0;
}
