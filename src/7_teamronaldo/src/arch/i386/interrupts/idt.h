#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "util.h"

// Forward declarations for interrupt and IRQ handlers.
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
//extern void isr128();
//extern void isr177();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// IDT entry structure
struct idt_entry_struct {
    uint16_t base_low;
    uint16_t sel;       // Selector
    uint8_t always0;    // This must always be zero.
    uint8_t flags;      // More flags
    uint16_t base_high;
} __attribute__((packed));

// Pointer structure for loading with 'lidt'
struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void initIdt();
void setIdtGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void isr_handler(struct InterruptRegisters * regs);

void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r));
void irq_uninstall_handler(int irq);
void irq_handler(struct InterruptRegisters* regs);

#endif // IDT_H















