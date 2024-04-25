
#include "pit.h"
#include "util.h" // Include for inb() and outb()
#include <stdint.h>
#include "idt.h" // Include for irq_install_handler()

volatile uint32_t timer_ticks = 0;


extern volatile uint32_t timer_ticks;  // Ensure this is defined where the PIT handler increments it.


void timer_handler(struct InterruptRegisters *regs) {
    timer_ticks++;  // Increment a counter every time the timer fires
    /*if (timer_ticks % 1000 == 0) {
        printf("100 ticks have passed.\n");
    }*/
}

// Initialize the PIT (Programmable Interval Timer)
void init_pit() {
    // Set PIT to mode 3 (square wave generator) and set the frequency divisor to achieve about 1000 Hz
    outb(PIT_CMD_PORT, 0x36); // 0x36 = 00110110 (Channel 0, lobyte/hibyte, mode 3)
    uint16_t divisor = 1193;  // Divisor calculated to get approximately 1000 Hz
    outb(PIT_CHANNEL0_PORT, divisor & 0xFF); // Lower byte of the divisor
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xFF); // Higher byte of the divisor


    // Register the timer handler as the interrupt handler for IRQ0
    irq_install_handler(0, timer_handler);
}

// Sleep using interrupts for the specified number of milliseconds
void sleep_interrupt(uint32_t milliseconds) {
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t current_tick = get_current_tick();
    uint32_t end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks) {
        asm volatile("sti"); // Enable interrupts
        asm volatile("hlt"); // Halt the CPU until the next interrupt
        current_tick = get_current_tick();
    }
}


// Sleep using busy waiting for the specified number of milliseconds
void sleep_busy(uint32_t milliseconds) {
    uint32_t start_tick = timer_ticks;
    uint32_t end_tick = start_tick + milliseconds; // Calculate the end tick upfront

    while (timer_ticks < end_tick) {
        // Busy wait: No operation inside, just waiting for the time to pass
    }
}


