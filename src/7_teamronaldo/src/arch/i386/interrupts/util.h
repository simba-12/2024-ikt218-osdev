
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

void printf(const char *format, ...);
void memset(void *dest, char val, uint32_t count);
void outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port);  // this is for keyboard 
size_t strlen(const char *str);
void outb(uint16_t port, uint8_t value); // Add this line for the outb function



// Function to get the current tick count
uint32_t get_current_tick();

struct InterruptRegisters {
    //uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

#endif // UTIL_H
