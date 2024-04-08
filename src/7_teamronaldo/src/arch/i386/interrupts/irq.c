#include "irq.h"       // Include your header file defining constants and function prototypes
#include "io.h"        // Assuming this provides inb() and outb() functions
#include "keyboard.h"  // Include the keyboard driver header file

// Function prototypes for internal functions
void irq_remap(void);
void irq_enable(uint8_t irq);
void irq_disable(uint8_t irq);
void irq_end_of_interrupt(uint8_t irq);

// Implementation of IRQ remapping
void irq_remap(void) {
    // Send the initialization command to both PICs
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // Remap the IRQs beyond the 0x20 offset to avoid conflicts with CPU exceptions
    outb(PIC1_DATA, 0x20); // Offset for master PIC (IRQs 0-7)
    outb(PIC2_DATA, 0x28); // Offset for slave PIC (IRQs 8-15)

    // Tell Master PIC that there is a slave PIC at IRQ2 (by setting the second bit)
    outb(PIC1_DATA, 0x04);

    // Tell Slave PIC its cascade identity (010 on the bus)
    outb(PIC2_DATA, 0x02);

    // Activate 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
}

// Enables a specific IRQ by clearing the mask bit for that line
void irq_enable(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8; // IRQ numbers 8-15 are on the slave PIC
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value); // Clear the bit to enable
}

// Disables a specific IRQ by setting the mask bit for that line
void irq_disable(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value); // Set the bit to disable
}

// Sends the End of Interrupt (EOI) command to the PICs
void irq_end_of_interrupt(uint8_t irq) {
    // Always send EOI to master PIC
    outb(PIC1_COMMAND, PIC_EOI);

    // If this IRQ came from the slave PIC, we need to acknowledge it there as well
    if (irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
}

// The handler for IRQ1 (keyboard interrupt)
void irq1_handler(void) {
    // Call the keyboard interrupt handler (provided by your keyboard driver)
    keyboard_callback();

    // Send EOI to acknowledge we've finished processing the keyboard interrupt
    irq_end_of_interrupt(IRQ1_KEYBOARD);
}
