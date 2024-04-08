#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#define NUM_INTERRUPTS 256

#ifdef __cplusplus
extern "C" {
#endif

void register_interrupt_handler(uint32_t n, void (*handler)(void));

#ifdef __cplusplus
}
#endif

#endif // INTERRUPTS_H
