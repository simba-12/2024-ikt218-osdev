

#include "vga.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "keyboard.h"
#include "util.h" 


static volatile uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;
//static volatile uint16_t* const VGA_MEMORY = (uint16_t*)0xC00B8000;

static size_t terminal_row = 0;
static size_t terminal_column = 0;
static const uint8_t terminal_color = 0x07; // Light grey on black

void vga_initialize(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            VGA_MEMORY[index] = ' ' | (uint16_t)terminal_color << 8;
        }
    }
}




static void vga_put_char(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    } else if (c == '\b') {
        if (terminal_column > 0) {
            terminal_column--;
            const size_t index = terminal_row * VGA_WIDTH + terminal_column;
            VGA_MEMORY[index] = ' ' | (uint16_t)terminal_color << 8;
        } else if (terminal_row > 0) {
            // Move to the end of the previous line
            terminal_row--;
            terminal_column = VGA_WIDTH - 1;
            const size_t index = terminal_row * VGA_WIDTH + terminal_column;
            VGA_MEMORY[index] = ' ' | (uint16_t)terminal_color << 8;
        }
    } else if (c == '\r') {
        terminal_column = 0; // Move cursor to the beginning of the current line
    } else if (c == '\t') {
        // Handle tab character by advancing cursor to the next tab stop
        size_t tab_size = 4; // Assume tab size of 4 spaces
        size_t spaces_to_tab = tab_size - (terminal_column % tab_size);
        for (size_t i = 0; i < spaces_to_tab; i++) {
            vga_put_char(' '); // Insert spaces until the next tab stop
        }
    } else {
        const size_t index = terminal_row * VGA_WIDTH + terminal_column;
        VGA_MEMORY[index] = (uint16_t)c | (uint16_t)terminal_color << 8;
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_row = 0;
        }
    }
}



void move_cursor_left() {
    if (terminal_column > 0) {
        // Move the cursor left by one column
        terminal_column--;
    } else if (terminal_row > 0) {
        // Move to the end of the previous line
        terminal_row--;
        terminal_column = VGA_WIDTH - 1;
    }
    // Add a call to a function that will update the hardware cursor position here
    // update_cursor_position(terminal_row, terminal_column);
}

void move_cursor_right() {
    // Check if the cursor is not already at the rightmost position
    if (terminal_column < VGA_WIDTH - 1) {
        // Move the cursor to the right by incrementing its column position
        terminal_column++;
    } else {
        // If the cursor is at the rightmost position, move to the beginning of the next line
        terminal_column = 0;
        // Check if the cursor is not already at the bottommost position
        if (++terminal_row == VGA_HEIGHT) {
            // If the cursor is at the bottommost position, move to the topmost position
            terminal_row = 0;
        }
    }
}



void move_cursor_up() {
    if (terminal_row > 0) {
        // Move the cursor up by one row
        terminal_row--;
    }
}

void move_cursor_down() {
    if (terminal_row < VGA_HEIGHT - 1) {
        // Move the cursor down by one row
        terminal_row++;
    }
}

void vga_write(const char *data) {
    for (size_t i = 0; data[i] != '\0'; i++)
        vga_put_char(data[i]);
}

// Helper function to reverse a string; used in itoa.
static void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// Helper function to convert an integer to a null-terminated string.
static char* itoa(int n, char* s, int base) {
    int i = 0;
    bool isNegative = false;

    // Handle 0 explicitly, otherwise empty string is printed for 0
    if (n == 0) {
        s[i++] = '0';
        s[i] = '\0';
        return s;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise, numbers are considered unsigned.
    if (n < 0 && base == 10) {
        isNegative = true;
        n = -n;
    }

    // Process individual digits
    while (n != 0) {
        int rem = n % base;
        s[i++] = (rem > 9)? (rem - 10) + 'a' : rem + '0';
        n = n/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        s[i++] = '-';

    s[i] = '\0'; // Null-terminate string

    // Reverse the string
    reverse(s);

    return s;
}


void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // Check the next character
            switch (*format) {
                case 's': {  // String
                    char *str = va_arg(args, char*);
                    vga_write(str);
                    break;
                }
                case 'c': {  // Character
                    char chr = va_arg(args, int);
                    vga_put_char(chr);
                    break;
                }
                case 'd': {  // Signed decimal integer
                    int num = va_arg(args, int);
                    char buffer[20];
                    vga_write(itoa(num, buffer, 10));
                    break;
                }
                case 'x':
                case 'X': {  // Unsigned hexadecimal integer
                    unsigned int num = va_arg(args, unsigned int);
                    char buffer[20];
                    vga_write(itoa(num, buffer, 16));
                    break;
                }
                
            }
        } else {
            vga_put_char(*format);
        }
        format++;
    }

    va_end(args);
}
