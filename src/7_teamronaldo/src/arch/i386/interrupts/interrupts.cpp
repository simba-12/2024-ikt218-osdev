#include "interrupts.h"

#define NUM_INTERRUPTS 256
static void (*interrupt_handlers[NUM_INTERRUPTS])(void) = {0};

void register_interrupt_handler(uint32_t n, void (*handler)(void)) {
    if (n < NUM_INTERRUPTS) {
        interrupt_handlers[n] = handler;
    }
}
