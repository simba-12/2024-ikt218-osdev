// // File: io.h
// #ifndef IO_H
// #define IO_H

// #include <stdint.h>

// static inline uint8_t inb(uint16_t port) {
//     uint8_t ret;
//     asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
//     return ret;
// }

// static inline void outb(uint16_t port, uint8_t data) {
//     asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
// }

// #endif // IO_H


#ifndef IO_H
#define IO_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

#endif // IO_H
