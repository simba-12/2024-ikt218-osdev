#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void printf(const char *format, ...);
void memset(void *dest, char val, uint32_t count);
void outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port); // This is for keyboard
size_t strlen(const char *str);
void outb(uint16_t port, uint8_t value); // Standardized for C linkage

// Function to get the current tick count
uint32_t get_current_tick();

struct InterruptRegisters {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

#ifdef __cplusplus
}
#endif

#endif // UTIL_H
