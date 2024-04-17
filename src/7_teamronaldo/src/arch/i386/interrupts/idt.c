
// #include "stdint.h"
// #include "util.h"
// #include "idt.h"
// #include "vga.h"
// #include "keyboard.h"




// struct idt_entry_struct idt_entries[256];
// struct idt_ptr_struct idt_ptr;

// extern void idt_flush(uint32_t);

// void initIdt(){
//   idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
//   idt_ptr.base = (uint32_t) &idt_entries;

//   memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);


//      // 0x20 commands and 0x21 data
//     outPortB(0x20, 0x11);
//     outPortB(0xA0, 0x11);

//     outPortB(0x21, 0x20);
//     outPortB(0xA1, 0x28);

//     outPortB(0x21, 0x04);
//     outPortB(0xA1, 0x02);

//     outPortB(0x21, 0x01);
//     outPortB(0xA1, 0x01);

//     outPortB(0x21, 0x0);
//     outPortB(0xA1, 0x0);


//     setIdtGate(0,(uint32_t)isr0, 0x08, 0x8E);
//     setIdtGate(1, (uint32_t)isr1, 0x08, 0x8E);
//     setIdtGate(2, (uint32_t)isr2, 0x08, 0x8E);
//     setIdtGate(3, (uint32_t)isr3, 0x08, 0x8E);
//     setIdtGate(4, (uint32_t)isr4, 0x08, 0x8E);
//     setIdtGate(5, (uint32_t)isr5, 0x08, 0x8E);
//     setIdtGate(6, (uint32_t)isr6, 0x08, 0x8E);
//     setIdtGate(7, (uint32_t)isr7, 0x08, 0x8E);
//     setIdtGate(8, (uint32_t)isr8, 0x08, 0x8E);
//     setIdtGate(9, (uint32_t)isr9, 0x08, 0x8E);
//     setIdtGate(10, (uint32_t)isr10, 0x08, 0x8E);
//     setIdtGate(11, (uint32_t)isr11, 0x08, 0x8E);
//     setIdtGate(12, (uint32_t)isr12, 0x08, 0x8E);
//     setIdtGate(13, (uint32_t)isr13, 0x08, 0x8E);
//     setIdtGate(14, (uint32_t)isr14, 0x08, 0x8E);
//     setIdtGate(15, (uint32_t)isr15, 0x08, 0x8E);
//     setIdtGate(16, (uint32_t)isr16, 0x08, 0x8E);
//     setIdtGate(17, (uint32_t)isr17, 0x08, 0x8E);
//     setIdtGate(18, (uint32_t)isr18, 0x08, 0x8E);
//     setIdtGate(19, (uint32_t)isr19, 0x08, 0x8E);
//     setIdtGate(20, (uint32_t)isr20, 0x08, 0x8E);
//     setIdtGate(21, (uint32_t)isr21, 0x08, 0x8E);
//     setIdtGate(22, (uint32_t)isr22, 0x08, 0x8E);
//     setIdtGate(23, (uint32_t)isr23, 0x08, 0x8E);
//     setIdtGate(24, (uint32_t)isr24, 0x08, 0x8E);
//     setIdtGate(25, (uint32_t)isr25, 0x08, 0x8E);
//     setIdtGate(26, (uint32_t)isr26, 0x08, 0x8E);
//     setIdtGate(27, (uint32_t)isr27, 0x08, 0x8E);
//     setIdtGate(28, (uint32_t)isr28, 0x08, 0x8E);
//     setIdtGate(29, (uint32_t)isr29, 0x08, 0x8E);
//     setIdtGate(30, (uint32_t)isr30, 0x08, 0x8E);
//     setIdtGate(31, (uint32_t)isr31, 0x08, 0x8E);


// // will add IRQ 
//     setIdtGate(32, (uint32_t)irq0, 0x08, 0x8E);
//     setIdtGate(33, (uint32_t)irq1, 0x08, 0x8E);
//     setIdtGate(34, (uint32_t)irq2, 0x08, 0x8E);
//     setIdtGate(35, (uint32_t)irq3, 0x08, 0x8E);
//     setIdtGate(36, (uint32_t)irq4, 0x08, 0x8E);
//     setIdtGate(37, (uint32_t)irq5, 0x08, 0x8E);
//     setIdtGate(38, (uint32_t)irq6, 0x08, 0x8E);
//     setIdtGate(39, (uint32_t)irq7, 0x08, 0x8E);
//     setIdtGate(40, (uint32_t)irq8, 0x08, 0x8E);
//     setIdtGate(41, (uint32_t)irq9, 0x08, 0x8E);
//     setIdtGate(42, (uint32_t)irq10, 0x08, 0x8E);
//     setIdtGate(43, (uint32_t)irq11, 0x08, 0x8E);
//     setIdtGate(44, (uint32_t)irq12, 0x08, 0x8E);
//     setIdtGate(45, (uint32_t)irq13, 0x08, 0x8E);
//     setIdtGate(46, (uint32_t)irq14, 0x08, 0x8E);
//     setIdtGate(47, (uint32_t)irq15, 0x08, 0x8E);





//    setIdtGate(128, (uint32_t)isr128, 0x08, 0x8E);
//    setIdtGate(177, (uint32_t)isr177, 0x08, 0x8E);

//    idt_flush((uint32_t)&idt_ptr);



// }

// // void setIdtGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){
// //     idt_entries[num].base_low = base & 0xFFFF;
// //     idt_entries[num].base_high = (base >> 16) & 0xFFFF;
// //     idt_entries[num].sel = sel;
// //     idt_entries[num].always0 = 0;
// //     //idt_entries[num].flags = flags | 0x60;
// //     idt_entries[num].flags = flags; // 'flags' should already be set to 0x8E
// // }



// void setIdtGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){
// //printf("Setting IDT gate %u, ISR address high 0x%X, low 0x%X\n", num, (unsigned int)(base >> 16), (unsigned int)(base & 0xFFFF));
//     idt_entries[num].base_low = base & 0xFFFF;
//     idt_entries[num].base_high = (base >> 16) & 0xFFFF;
//     idt_entries[num].sel = sel;
//     idt_entries[num].always0 = 0;
//     idt_entries[num].flags = flags;
// }




// const char *exception_messages[] = {
//   "Division By Zero",
//   "Debug",
//   "Non Maskable Interrupt",
//   "Breakpoint",
//   "Into Detected Overflow",
//   "Out of Bounds",
//   "Invalid Opcode",
//   "No Coprocessor",
//   "Double fault",
//   "Coprocessor Segment Overrun",
//   "Bad TSS",
//   "Segment not present",
//   "Stack fault",
//   "General protection fault",
//   "Page fault",
//   "Unknown Interrupt",
//   "Coprocessor Fault",
//   "Alignment Fault",
//   "Machine Check",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved",
//   "Reserved"

// };



// void isr_handler(struct InterruptRegisters* regs){
  
//   if (regs->int_no < 32){
//     printf(exception_messages[regs->int_no]);
//     printf("\n");
//     printf("Exception! System Halted\n");
//     for (;;);
//   }
// }






// void *irq_routines[16] = {
//   0, 0, 0, 0, 0, 0, 0, 0,
//   0, 0, 0, 0, 0, 0, 0, 0
// };

// void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r)) {
//   irq_routines[irq] = handler;
// }

// void irq_uninstall_handler(int irq) {
//   irq_routines[irq] = 0;
// }



// void irq_handler(struct InterruptRegisters* regs) {
//   void (*handler)(struct InterruptRegisters *regs);
//   handler = irq_routines[regs->int_no - 32];

//   if (handler) {
//     handler(regs);
//   }

//   if (regs->int_no >= 40){
//     outPortB(0xA0,0x20);
//   }
//   outPortB(0x20,0x20);
// }












#include "stdint.h"
#include "util.h"
#include "idt.h"
#include "vga.h" 
#include "keyboard.h" 


struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32_t);  // Assembly function to load the IDT.

void initIdt() {
    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    // Remap the IRQ table
    outPortB(0x20, 0x11);
    outPortB(0xA0, 0x11);
    outPortB(0x21, 0x20);
    outPortB(0xA1, 0x28);
    outPortB(0x21, 0x04);
    outPortB(0xA1, 0x02);
    outPortB(0x21, 0x01);
    outPortB(0xA1, 0x01);
    outPortB(0x21, 0x0);


    //outPortB(0x21, 0xfd);
    outPortB(0xA1, 0x00);



    setIdtGate(0,(uint32_t)isr0, 0x08, 0x8E);
    setIdtGate(1, (uint32_t)isr1, 0x08, 0x8E);
    setIdtGate(2, (uint32_t)isr2, 0x08, 0x8E);
    setIdtGate(3, (uint32_t)isr3, 0x08, 0x8E);
    setIdtGate(4, (uint32_t)isr4, 0x08, 0x8E);
    setIdtGate(5, (uint32_t)isr5, 0x08, 0x8E);
    setIdtGate(6, (uint32_t)isr6, 0x08, 0x8E);
    setIdtGate(7, (uint32_t)isr7, 0x08, 0x8E);
    setIdtGate(8, (uint32_t)isr8, 0x08, 0x8E);
    setIdtGate(9, (uint32_t)isr9, 0x08, 0x8E);
    setIdtGate(10, (uint32_t)isr10, 0x08, 0x8E);
    setIdtGate(11, (uint32_t)isr11, 0x08, 0x8E);
    setIdtGate(12, (uint32_t)isr12, 0x08, 0x8E);
    setIdtGate(13, (uint32_t)isr13, 0x08, 0x8E);
    setIdtGate(14, (uint32_t)isr14, 0x08, 0x8E);
    setIdtGate(15, (uint32_t)isr15, 0x08, 0x8E);



    // Setup IDT entries for IRQs 0-15
    setIdtGate(32, (uint32_t)irq0, 0x08, 0x8E);
    setIdtGate(33, (uint32_t)irq1, 0x08, 0x8E);
    setIdtGate(34, (uint32_t)irq2, 0x08, 0x8E);
    setIdtGate(35, (uint32_t)irq3, 0x08, 0x8E);
    setIdtGate(36, (uint32_t)irq4, 0x08, 0x8E);
    setIdtGate(37, (uint32_t)irq5, 0x08, 0x8E);
    setIdtGate(38, (uint32_t)irq6, 0x08, 0x8E);
    setIdtGate(39, (uint32_t)irq7, 0x08, 0x8E);
    setIdtGate(40, (uint32_t)irq8, 0x08, 0x8E);
    setIdtGate(41, (uint32_t)irq9, 0x08, 0x8E);
    setIdtGate(42, (uint32_t)irq10, 0x08, 0x8E);
    setIdtGate(43, (uint32_t)irq11, 0x08, 0x8E);
    setIdtGate(44, (uint32_t)irq12, 0x08, 0x8E);
    setIdtGate(45, (uint32_t)irq13, 0x08, 0x8E);
    setIdtGate(46, (uint32_t)irq14, 0x08, 0x8E);
    setIdtGate(47, (uint32_t)irq15, 0x08, 0x8E);
    // Continue setting other gates...

    idt_flush((uint32_t)&idt_ptr);
}

void setIdtGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags | 0x60;  // User mode
}


static const char *exception_messages[] = {
    "Division By Zero Exception",
    "Debug Exception",
    "Non Maskable Interrupt Exception",
    "Breakpoint Exception",
    "Into Detected Overflow Exception",
    "Out of Bounds Exception",
    "Invalid Opcode Exception",
    "No Coprocessor Exception",
    "Double Fault Exception",
    "Coprocessor Segment Overrun Exception",
    "Bad TSS Exception",
    "Segment Not Present Exception",
    "Stack Fault Exception",
    "General Protection Fault Exception",
    "Page Fault Exception",
    "Unknown Interrupt Exception",
    "Coprocessor Fault Exception",
    "Alignment Check Exception (486+)",
    "Machine Check Exception (Pentium/586+)",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions",
    "Reserved Exceptions"
};




void isr_handler(struct InterruptRegisters * regs) {

    if (regs->int_no < 32) {
        outPortB(0x20, 0x20);  // Acknowledge the interrupt to the PIC

        // Use printf to display the exception message
        printf("Received exception: %s\n", exception_messages[regs->int_no]);

        // Here you can add any functionality you want to perform on an exception
        // For example, halting the system:
        for (;;);  // Infinite loop to halt the system
    }
}


void *irq_routines[16] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
 };


// void irq_handler(uint32_t irq_number) {
    
//     // the master and the slave when handling hardware interrupts.
//     if (irq_number >= 40) {
//         outPortB(0xA0, 0x20); // EOI to slave
//     }
//     outPortB(0x20, 0x20); // EOI to master



//     void (*handler)();
//     handler = irq_routines[irq_number - 32];
//     if (handler) {
//         handler();  // Call the custom handler.
//     }
// }

// void irq_install_handler(int irq, void (*handler)(void)) {
//     irq_routines[irq] = handler;
// }

// void irq_uninstall_handler(int irq) {
//     irq_routines[irq] = 0;
// }






void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r)) {
  irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) {
  irq_routines[irq] = 0;
}



void irq_handler(struct InterruptRegisters* regs) {
  void (*handler)(struct InterruptRegisters *regs);
  handler = irq_routines[regs->int_no - 32];

  if (handler) {
    handler(regs);
  }

  if (regs->int_no >= 40){
    outPortB(0xA0,0x20);
  }
  outPortB(0x20,0x20);
}

