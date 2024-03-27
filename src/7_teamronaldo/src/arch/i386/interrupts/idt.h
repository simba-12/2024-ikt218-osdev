// #ifndef IDT_H
// #define IDT_H

// #include <stdint.h>

// struct idt_entry {
//     uint16_t base_lo;
//     uint16_t sel;
//     uint8_t  always0;
//     uint8_t  flags;
//     uint16_t base_hi;
// } __attribute__((packed));

// struct idt_ptr {
//     uint16_t limit;
//     uint32_t base;
// } __attribute__((packed));

// void init_idt();
// void idt_set_entry(int num, uint32_t base, uint16_t sel, uint8_t flags);

// #endif // IDT_H


#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_idt();
void idt_set_entry(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif // IDT_H
