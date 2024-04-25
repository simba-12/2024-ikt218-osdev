
#include "util.h"
#include <stdarg.h> // Required for variable arguments
#include <stdio.h>

// // Global variable to store the tick count
 static uint32_t tick_count = 0;



void memset(void *dest, char val, uint32_t count) {
    char *temp = (char*) dest;
    for (; count != 0; count--) {
        *temp++ = val;
    }
}

void outPortB(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}



char inPortB(uint16_t port) {
    char rv;
    asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
    return rv;
}

size_t strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s) {}
    return (s - str);
}


// Implementation of get_current_tick function
uint32_t get_current_tick() {
    
    return tick_count;
}
