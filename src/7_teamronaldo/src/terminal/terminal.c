#include "libc/terminal.h"
#include "libc/stddef.h" 
#include "libc/kstd.h"




// VGA text mode buffer address
volatile char* const VGA_TEXT_MODE_BUFFER = (char*)0xB8000;
// Screen size
const unsigned int VGA_WIDTH = 80;
const unsigned int VGA_HEIGHT = 25;


// Current cursor position
unsigned int terminal_row = 0;
unsigned int terminal_column = 0;
// Terminal color and buffer
unsigned char terminal_color = 0x02; // White on Black
volatile char* terminal_buffer = (volatile char*)VGA_TEXT_MODE_BUFFER;

void terminal_initialize(void) {
    for (unsigned int y = 0; y < VGA_HEIGHT; y++) {
        for (unsigned int x = 0; x < VGA_WIDTH; x++) {
            const size_t index = (y * VGA_WIDTH + x) * 2;
            terminal_buffer[index] = ' ';
            terminal_buffer[index + 1] = terminal_color;
        }
    }
}


void terminal_putentryat(char c, char color, int x, int y) {
    const size_t index = (y * VGA_WIDTH + x) * 2;
    terminal_buffer[index] = c;
    terminal_buffer[index + 1] = color;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)  // Now comparing unsigned int with unsigned int
            terminal_row = 0;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {  // Now comparing unsigned int with unsigned int
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)  // Now comparing unsigned int with unsigned int
                terminal_row = 0;
        }
    }
}


void terminal_writestring(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++)
        terminal_putchar(string[i]);
}
