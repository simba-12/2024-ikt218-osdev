#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Function prototypes for ISR handlers
void isr0();
void isr1();
void isr2();

// Structure for an IDT entry
struct idt_entry {
    uint16_t base_lo;       // The lower 16 bits of the address to jump to
    uint16_t sel;           // Kernel segment selector
    uint8_t  always0;       // This must always be zero
    uint8_t  flags;         // More flags
    uint16_t base_hi;       // The upper 16 bits of the address to jump to
} __attribute__((packed)); // Tell GCC not to optimize this structure

// A pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr {
    uint16_t limit;
    uint32_t base;          // The address of the first element in our idt_entry array
} __attribute__((packed));

// Function declarations
void init_idt();
void idt_set_entry(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif // IDT_H
