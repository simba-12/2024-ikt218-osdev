// // // isr.cpp
// // #include "isr.h"
// // #include "kstdio.h"  // Correct path to your custom printf declaration

// // extern "C" void isr_handler(registers_t regs) {
// //     printf("Received interrupt: %d\n", regs.int_no);

// // }
// // isr.cpp
// #include "terminal.h" // Make sure this is the correct header file

// void isr_handler() {
//     terminal_writestring("ISR triggered\n");
// }


// isr.cpp
#include "isr.h"
#include "terminal.h" // Adjust this include path to wherever terminal_writestring is declared

extern "C" void isr_handler(registers_t regs) {
    // Assuming terminal_writestring can only print strings, you'd need a way to convert regs.int_no to a string
    // For simplicity, let's just indicate an interrupt was received for now:
    terminal_writestring("Received interrupt\n");
}
