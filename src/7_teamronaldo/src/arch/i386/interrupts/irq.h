#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

#define PIC1            0x20    // IO base address for master PIC
#define PIC2            0xA0    // IO base address for slave PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)
#define PIC_EOI         0x20    // End-of-interrupt command code

#define ICW1_ICW4       0x01    // ICW4 (not) needed
#define ICW1_SINGLE     0x02    // Single (cascade) mode
#define ICW1_INTERVAL4  0x04    // Call address interval 4 (8)
#define ICW1_LEVEL      0x08    // Level triggered (edge) mode
#define ICW1_INIT       0x10    // Initialization - required!

#define ICW4_8086       0x01    // 8086/88 (MCS-80/85) mode
#define ICW4_AUTO       0x02    // Auto (normal) EOI
#define ICW4_BUF_SLAVE  0x08    // Buffered mode/slave
#define ICW4_BUF_MASTER 0x0C    // Buffered mode/master
#define ICW4_SFNM       0x10    // Special fully nested (not)

#ifdef __cplusplus
extern "C" {
#endif

// Remap the PIC controllers, giving them new IRQ numbers.
void irq_remap(void);

// Enable interrupts for the specified IRQ.
void irq_enable(uint8_t irq);

// Disable interrupts for the specified IRQ.
void irq_disable(uint8_t irq);

// Send end of interrupt signal to PIC.
void irq_end_of_interrupt(uint8_t irq);

// Example IRQ handler
// void irq_handler(int irq);

#ifdef __cplusplus
}
#endif

// Include the keyboard initialization function prototype
void init_keyboard();

#endif // IRQ_H
