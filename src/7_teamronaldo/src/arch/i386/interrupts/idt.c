#include "idt.h"
///#include "isr.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void irq1();

struct idt_entry idt[256];
struct idt_ptr idtp;

void *memset(void *s, int c, size_t n) {
    unsigned char* p = s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

void idt_set_entry(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_idt() {
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;
    idtp.base = (uint32_t)&idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    idt_set_entry(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_entry(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_entry(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_entry(33,(uint32_t)irq1, 0x08, 0x8E);
    __asm__ __volatile__("lidt %0" : : "m" (idtp));
}

