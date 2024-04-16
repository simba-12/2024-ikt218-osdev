// // #include "vga.h"
// // #include <string.h>

// // static volatile uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
// // static size_t terminal_row;
// // static size_t terminal_column;
// // static uint8_t terminal_color;
// // static uint16_t* terminal_buffer;

// // void vga_initialize(void) {
// //     terminal_row = 0;
// //     terminal_column = 0;
// //     terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
// //     terminal_buffer = (uint16_t*) VGA_MEMORY;
// //     for (size_t y = 0; y < VGA_HEIGHT; y++) {
// //         for (size_t x = 0; x < VGA_WIDTH; x++) {
// //             const size_t index = y * VGA_WIDTH + x;
// //             terminal_buffer[index] = vga_entry(' ', terminal_color);
// //         }
// //     }
// // }

// // uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
// //     return fg | bg << 4;
// // }

// // uint16_t vga_entry(unsigned char uc, uint8_t color) {
// //     return (uint16_t) uc | (uint16_t) color << 8;
// // }

// // void vga_set_cursor(size_t x, size_t y) {
// //     terminal_row = y;
// //     terminal_column = x;
// // }

// // void vga_put_char(char c, uint8_t color, size_t x, size_t y) {
// //     const size_t index = y * VGA_WIDTH + x;
// //     terminal_buffer[index] = vga_entry(c, color);
// // }

// // void vga_write(const char* data, size_t size) {
// //     for (size_t i = 0; i < size; i++) {
// //         char c = data[i];
// //         if (c == '\n') {
// //             terminal_column = 0;
// //             if (++terminal_row == VGA_HEIGHT)
// //                 terminal_row = 0;
// //         } else {
// //             vga_put_char(c, terminal_color, terminal_column, terminal_row);
// //             if (++terminal_column == VGA_WIDTH) {
// //                 terminal_column = 0;
// //                 if (++terminal_row == VGA_HEIGHT)
// //                     terminal_row = 0;
// //             }
// //         }
// //     }
// // }

// // void vga_write_string(const char* data) {
// //     vga_write(data, strlen(data));
// // }








// #include "vga.h"
// #include <stdarg.h>

// static volatile uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
// static size_t terminal_row = 0;
// static size_t terminal_column = 0;
// static const uint8_t terminal_color = 0x07; // Light grey on black

// void vga_initialize(void) {
//     for (size_t y = 0; y < VGA_HEIGHT; y++) {
//         for (size_t x = 0; x < VGA_WIDTH; x++) {
//             const size_t index = y * VGA_WIDTH + x;
//             VGA_MEMORY[index] = ' ' | (uint16_t)terminal_color << 8;
//         }
//     }
// }

// static void vga_put_char(char c) {
//     if (c == '\n') {
//         terminal_column = 0;
//         if (++terminal_row == VGA_HEIGHT)
//             terminal_row = 0;
//     } else {
//         const size_t index = terminal_row * VGA_WIDTH + terminal_column;
//         VGA_MEMORY[index] = (uint16_t)c | (uint16_t)terminal_color << 8;
//         if (++terminal_column == VGA_WIDTH) {
//             terminal_column = 0;
//             if (++terminal_row == VGA_HEIGHT)
//                 terminal_row = 0;
//         }
//     }
// }

// void printf(const char *format, ...) {
//     va_list args;
//     va_start(args, format);

//     while (*format != '\0') {
//         if (*format == '%') {
//             format++;
//             if (*format == 's') {
//                 char *str = va_arg(args, char *);
//                 while (*str) {
//                     vga_put_char(*str++);
//                 }
//             }
//         } else {
//             vga_put_char(*format);
//         }
//         format++;
//     }

//     va_end(args);
// }






#include "vga.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static volatile uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;
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

// Custom printf function that handles %s, %d, and %x.
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

