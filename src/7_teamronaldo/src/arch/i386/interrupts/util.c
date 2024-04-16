// #include "stdint.h"
// #include "util.h"

// void memset(void *dest, char val, uint32_t count){
//   char *temp = (char*) dest;
//   for (; count != 0; count--){
//     *temp++ = val;
//   }
// }

// void outPortB(uint16_t port, uint8_t value){
//   asm volatile ("outb %b0, %w1" : : "a" (value), "dN" (port));

//   //asm volatile ("outb %0, %1" : : "dN" (port), "a" (value));
//  // asm volatile ("outb %0, %b1" : : "a"(value), "dN"(port));
    
// }



// char inPortB(uint16_t port){
//   char rv;
//   asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
//   return rv;
// }



// size_t strlen(const char *str) {
//     const char *s;
//     for (s = str; *s; ++s) {}
//     return (s - str);
// }



// // void vga_write_string(const char *message) {
// //     // Implementation of printing the message, e.g., using a UART or VGA buffer
// // }



//  void print(const char *message) {
//      // Implementation of printing the message, e.g., using a UART or VGA buffer
//  }





#include "util.h"
#include <stdarg.h> // Required for variable arguments
#include <stdio.h> 


void memset(void *dest, char val, uint32_t count) {
    char *temp = (char*) dest;
    for (; count != 0; count--) {
        *temp++ = val;
    }
}

void outPortB(uint16_t port, uint8_t value) {
    //asm volatile ("outb %b0, %w1" : : "a" (value), "dN" (port));
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

// this is for keyboard
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
