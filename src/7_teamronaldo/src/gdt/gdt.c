
#include "libc/gdt.h"

// Define the GDT entry array and GDT pointer
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// Assembly function to load the new GDT and refresh segment registers
extern void gdt_flush(uint32_t);

// Function to initialize a GDT entry
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
    gdt[num].access = access;
}

// Function to initialize the GDT
void init_gdt() {
    // Set up the GDT pointer
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    // NULL Segment
    gdt_set_gate(0, 0, 0, 0, 0);
    // Code Segment: Base address = 0, Limit = 4GB, 
    // Access byte = Present, Ring 0, Code, Read/Execute
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Data Segment: Base address = 0, Limit = 4GB, 
    // Access byte = Present, Ring 0, Data, Read/Write
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Flush the old GDT and install the new changes
    gdt_flush((uint32_t)&gp);

 
}
