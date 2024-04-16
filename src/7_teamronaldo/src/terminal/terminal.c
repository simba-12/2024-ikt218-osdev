
// #define VGA_COLOR_LIGHT_GREY 0x07
// #define VGA_COLOR_BLACK 0x00

// #include "terminal.h"

// #define VGA_WIDTH 80
// #define VGA_HEIGHT 25
// #define VGA_MEMORY (uint16_t*)0xB8000

// static uint16_t* terminal_buffer;
// static int terminal_row;
// static int terminal_column;

// void terminal_initialize(void) {
//     terminal_buffer = VGA_MEMORY;
//     terminal_row = 0;
//     terminal_column = 0;
// }


// void terminal_backspace(void) {
//     if (terminal_column > 0) {
//         terminal_column--;
//     } else if (terminal_row > 0) {
//         terminal_row--;
//         terminal_column = VGA_WIDTH - 1;
//     }
//     terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = (uint16_t)(VGA_COLOR_LIGHT_GREY << 8) | ' ';
// }
// void terminal_putchar(char c) {
//     if (c == '\n') {
//         terminal_row++;
//         terminal_column = 0;
//     } else if (c == '\b') {
//         terminal_backspace();
//     } else {
//         terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = (uint16_t)((VGA_COLOR_LIGHT_GREY << 8) | c);
//         terminal_column++;
//         if (terminal_column >= VGA_WIDTH) {
//             terminal_column = 0;
//             terminal_row++;
//         }
//     }

//     // Correct place for the closing brace of the if statement
//     if (terminal_row >= VGA_HEIGHT) {
//         // Scroll up
//         for (int y = 1; y < VGA_HEIGHT; y++) {
//             for (int x = 0; x < VGA_WIDTH; x++) {
//                 terminal_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
//             }
//         }
//         // Clear the last line after scrolling up
//         for (int x = 0; x < VGA_WIDTH; x++) {
//             terminal_buffer[terminal_row * VGA_WIDTH + x] = (uint16_t)((VGA_COLOR_LIGHT_GREY << 8) | ' ');
//         }
//     }
// }

// void terminal_writestring(const char* string) {
//     for (size_t i = 0; string[i] != '\0'; i++) {
//         terminal_putchar(string[i]);
//     }
// }

