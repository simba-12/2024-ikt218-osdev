#include "keyboard.h"
#include "io.h"
#include "isr.h"
#include "terminal.h"
#include <stdbool.h>
#include <stdint.h>

#define KEYBOARD_BUFFER_SIZE 256
static uint8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static int keyboard_buffer_head = 0;
static bool shift_pressed = false;
static bool keyboard_initialized = false;

// Lookup tables for scancode to ASCII conversion
static const char scancode_to_ascii_lower[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', // 0-9
    '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', // 10-19
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, // 20-29
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', // 30-39
    ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 40-49
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', // 50-59
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 60-69
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', // 70-79
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // 80-89
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 90-99
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 100-109
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 110-119
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 120-129
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 130-139
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 140-149
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 150-159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160-169
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 170-179
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 180-189
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 190-199
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 200-209
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 210-219
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 220-229
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 230-239
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 240-249
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 250-255
};

static const char scancode_to_ascii_upper[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', // 0-9
    '(', ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', // 10-19
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, // 20-29
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', // 30-39
    ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', // 40-49
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', // 50-59
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 60-69
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', // 70-79
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // 80-89
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 90-99
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 100-109
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 110-119
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 120-129
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 130-139
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 140-149
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 150-159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160-169
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 170-179
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 180-189
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 190-199
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 200-209
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 210-219
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 220-229
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 230-239
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 240-249
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 250-255
};

char scancode_to_ascii(uint8_t scancode) {
    // Check if the scancode is within the bounds of the lookup tables
    if (scancode >= sizeof(scancode_to_ascii_lower)) {
        return 0; // Return 0 if the scancode is not within the valid range
    }

    // Check if the Shift key is pressed and select the appropriate lookup table
    if (shift_pressed) {
        return scancode_to_ascii_upper[scancode];
    } else {
        return scancode_to_ascii_lower[scancode];
    }
}

void process_keyboard_buffer() {
    // Start processing from the beginning of the buffer.
    int i = 0;
    while (i < keyboard_buffer_head) {
        uint8_t scancode = keyboard_buffer[i++]; // Process each scancode in order.

        // Translate scancode to ASCII character
        char ch = scancode_to_ascii(scancode);

        // Print special characters for specific keys
        if (ch == '\n') {
            terminal_writestring("[Enter] ");
        } else if (ch == '\b') {
            terminal_writestring("[Backspace] ");
        } else {
            // If it's a printable character, write it to the terminal
            terminal_putchar(ch);
        }

        // Add debug output to print the raw scancode
        terminal_putchar('[');
        terminal_putchar('0' + ((scancode >> 4) & 0xF));
        terminal_putchar('0' + (scancode & 0xF));
        terminal_writestring("] ");
    }
    keyboard_buffer_head = 0; // Reset the buffer head after processing.
}

void keyboard_callback() {
    uint8_t scancode = inb(0x60);

    // Store the scancode in the buffer if there's space
    if (keyboard_buffer_head < KEYBOARD_BUFFER_SIZE) {
        keyboard_buffer[keyboard_buffer_head++] = scancode;
    }

    // Process the keyboard buffer to handle all scancodes including special keys
    process_keyboard_buffer();
}

// Initialize the keyboard
void init_keyboard() {
    if (!keyboard_initialized) {
        register_interrupt_handler(33, keyboard_callback); // Set keyboard interrupt handler
        terminal_initialize(); // Initialize terminal for output
        terminal_writestring("Keyboard initialized.\n");
        keyboard_initialized = true;
    }
}