#include <stdint.h>
#include "idt.h"
#include "util.h"
#include <stdio.h>
#include "keyboard.h" 
# include "vga.h"

void initkeyboard(){
    irq_install_handler(1, &keyboardHandler);
}

void keyboardHandler(struct InterruptRegisters *regs){
    char scanCode = inPortB(0x60) & 0x7F; 
    char press = inPortB(0x60) & 0x80; 

    printf("Scan code: %d, Press: %d\r\n", scanCode, press);
}
