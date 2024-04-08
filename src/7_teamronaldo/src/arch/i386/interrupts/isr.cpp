#include "isr.h"
#include "terminal.h"

void isr0() {
    terminal_writestring("Interrupt 0 received\n");
}

void isr1() {
    terminal_writestring("Interrupt 1 received\n");
}

void isr2() {
    terminal_writestring("Interrupt 2 received\n");
}

void irq1_routine()
{
    terminal_writestring("Keyboard");
}

void isr_handler(registers_t* regs) {
    if (regs) { // Check if the pointer is valid
        switch (regs->int_no) {
            case 0:
                isr0();
                break;
            case 1:
                isr1();
                break;
            case 2:
                isr2();
                break;
            case 33:
                irq1_routine();
                break;
            default:
                // Print an error message for unknown interrupts
                terminal_writestring("Unknown interrupt received\n");
                break;
        }
    }
}

// Define an array of function pointers to store interrupt handlers
void (*interrupt_handlers[256])(registers_t* r);

// Function to register interrupt handlers
inline void register_interrupt_handler(uint32_t n, void (*handler)(registers_t* r)) {
    // Check if interrupt number is within valid range
    if (n < 256) {
        // Register the handler function for the specified interrupt number
        interrupt_handlers[n] = handler;
    }
}
