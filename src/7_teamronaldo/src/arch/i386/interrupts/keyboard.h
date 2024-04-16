// #ifndef KEYBOARD_H
// #define KEYBOARD_H

// #include "idt.h"

// void initkeyboard();
// void keyboardHandler(struct InterruptRegisters *regs);



// #endif /* KEYBOARD_H */




#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "idt.h"

void initkeyboard();
void keyboardHandler(struct InterruptRegisters *regs);


#endif /* KEYBOARD_H */
