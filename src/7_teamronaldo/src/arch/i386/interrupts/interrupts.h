#ifndef INTERRUPTS_H
#define INTERRUPTS_H
// IRQ numbers after PIC remapping
#define IRQ0_TIMER 0
#define IRQ1_KEYBOARD 1
#include <stdint.h> // Changed from <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

void register_interrupt_handler(uint32_t n, void (*handler)(void));

#ifdef __cplusplus
}
#endif

#endif // INTERRUPTS_H
