
#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Structure to hold register state during interrupt handling
typedef struct {
    uint32_t ds;        // Data segment selector
    // Registers pushed by pusha instruction
    uint32_t edi, esi, ebp, unused, ebx, edx, ecx, eax;
    // Interrupt number and error code (if applicable)
    uint32_t int_no, err_code; 
    // Processor automatically pushes the rest
    uint32_t eip, cs, eflags, esp, ss;
} registers_t;

#ifdef __cplusplus
extern "C" {
#endif

// Function to handle interrupts - now takes a pointer to registers_t
void isr_handler(registers_t* regs);

// Function to register interrupt handlers
void register_interrupt_handler(uint32_t n, void (*handler)(registers_t* r));

#ifdef __cplusplus
}
#endif

#endif // ISR_H

