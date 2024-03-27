#include "isr.h"
#include "stdio.h" // Ensure this is adapted to your environment.

void isr_handler(registers_t regs) {
    printf("Received interrupt: %d\n", regs.int_no);
    // Add specific handlers if needed.
}
