// // // File: keyboard.c
// // #include "keyboard.h"
// // #include "io.h"
// // #include "isr.h"
// // #include "kstdio.h" // Include for custom printf

// // // void keyboard_callback() {
// // //     uint8_t scancode = inb(0x60);
// // //    // printf("Scancode: %x\n", scancode);
// // //    terminal_writestring("Some message\n");

// // // }
// // void keyboard_callback() {
// //     static const char scancode_to_char[] = {
// //         0, 0, '1', '2', '3', '4', '5', '6', '7', '8', // 0-9
// //         '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', // 10-19
// //         // Add more for the rest of the characters...
// //         't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, // 20-29
// //         'a', 's', 'd', 'f', // ...continue mapping
// //         // Note: '\n' is for Enter key, 0 for keys we don't handle
// //     };
// //     uint8_t scancode = inb(0x60);

// //     // Check if scancode is in the range of known characters
// //     if (scancode < sizeof(scancode_to_char)) {
// //         char ch = scancode_to_char[scancode];
// //         if (ch) {
// //             char str[2] = {ch, '\0'};
// //             terminal_writestring(str);
// //         }
// //     }
// // }


// // void init_keyboard() {
// //     register_interrupt_handler(33, (void(*)(void))keyboard_callback);
// // }



// #include "keyboard.h"
// #include "io.h"
// #include "isr.h"
// #include "kstdio.h" // Include for custom printf
// #include "terminal.h" // For terminal_writestring()


// static int shift_pressed = 0;

// // Extended scancode_to_char array with placeholders for simplicity
// static const char scancode_to_char_lower[] = {
//     0, 0, '1', '2', '3', '4', '5', '6', '7', '8', // 0-9
//     '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', // 10-19
//     't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, // 20-29
//     'a', 's', 'd', 'f', 'g', 'h', 'i', 'j', 'k', 'l', // 30-39
//     'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', // 40-49
//     'w', 'x', 'y', 'z', '0', '-', '=', '[', ']', '\\', // 50-59
//     ';', '\'', '`', ',', '.', '/', ' ', 0, 0, 0, // 60-69
//     // Add more for other keys...
// };

// static const char scancode_to_char_upper[] = {
//     0, 0, '1', '2', '3', '4', '5', '6', '7', '8', // 0-9
//     '9', '0', '-', '=', 0, 0, 'Q', 'W', 'E', 'R', // 10-19
//     'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, // 20-29
//     'A', 'S', 'D', 'F', 'G', 'H', 'I', 'J', 'K', 'L', // 30-39
//     'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', // 40-49
//     'W', 'X', 'Y', 'Z', '0', '-', '=', '[', ']', '\\', // 50-59
//     ';', '\'', '`', ',', '.', '/', ' ', 0, 0, 0, // 60-69
//     // Add more for other keys...
// };


// // void keyboard_callback() {
// //     uint8_t scancode = inb(0x60);

// //     // Handle shift press and release
// //     if (scancode == 0x2A || scancode == 0x36) { // Pressed left or right shift
// //         shift_pressed = 1;
// //     } else if (scancode == 0xAA || scancode == 0xB6) { // Released left or right shift
// //         shift_pressed = 0;
// //     }

// //     if (scancode < sizeof(scancode_to_char_lower)) {
// //         char ch = shift_pressed ? scancode_to_char_upper[scancode] : scancode_to_char_lower[scancode];
// //         if (ch) {
// //             char str[2] = {ch, '\0'};
// //             terminal_writestring(str);
// //         }
// //     }
// // }

// // void init_keyboard() {
// //     // Assuming 33 is the correct IRQ number for the keyboard
// //     register_interrupt_handler(33, keyboard_callback);
// // }

// void keyboard_callback() {
//     uint8_t scancode = inb(0x60);

//     // Handle shift press and release
//     if (scancode == 0x2A || scancode == 0x36) { // Pressed left or right shift
//         shift_pressed = 1;
//     } else if (scancode == 0xAA || scancode == 0xB6) { // Released left or right shift
//         shift_pressed = 0;
//     }

//     if (scancode < sizeof(scancode_to_char_lower)) {
//         char ch = shift_pressed ? scancode_to_char_upper[scancode] : scancode_to_char_lower[scancode];
//         if (ch) {
//             char str[2] = {ch, '\0'};
//             terminal_writestring(str);
//         }
//     }
// }

// void init_keyboard() {
//     // Assuming 33 is the correct IRQ number for the keyboard
//     register_interrupt_handler(33, keyboard_callback);
// }




#include "keyboard.h"
#include "io.h"
#include "isr.h"
#include "kstdio.h" // Include for custom printf
#include "terminal.h" // For terminal_writestring()

// Array to map scancodes to ASCII characters
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

static int shift_pressed = 0;

// Keyboard callback function
void keyboard_callback() {
    uint8_t scancode = inb(0x60);

    // Check if Shift key is pressed
    if (scancode == 0x2A || scancode == 0x36) { // Pressed left or right shift
        shift_pressed = 1;
        return; // Ignore the Shift keypress itself
    } else if (scancode == 0xAA || scancode == 0xB6) { // Released left or right shift
        shift_pressed = 0;
        return; // Ignore the Shift keyrelease itself
    }

    // Map scancode to ASCII character based on Shift key state
    char ch;
    if (shift_pressed) {
        ch = scancode_to_ascii_upper[scancode];
    } else {
        ch = scancode_to_ascii_lower[scancode];
    }

    // Check if the character is valid and not NULL
    if (ch) {
        char str[2] = {ch, '\0'};
        terminal_writestring(str);
    }
}

// Initialize the keyboard
void init_keyboard() {
    // Assuming IRQ 1 is the correct IRQ number for the keyboard
    register_interrupt_handler(33, keyboard_callback);
}
