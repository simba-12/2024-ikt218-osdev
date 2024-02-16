// #include <libc/stdint.h>
// // Simple function to print a null-terminated string to the screen
// void print(const char* data) {
//     static uint16_t* video_memory = (char*)0xB8000; // = (uint16_t*)VGA_TEXT_MODE_BUFFER;
//     static uint8_t x = 0, y = 0;
//     for (const char* p = data; *p; ++p) {
//         // Newline support
//         if (*p == '\n') {
//             x = 0;
//             ++y;
//             continue;
//         }
//         // Write the character and its attribute byte to video memory
//         video_memory[y * 80 + x] = (0x07 << 8) | *p; // 0x07 is light grey on black
//         ++x;
//         if (x >= 80) {
//             x = 0;
//             ++y;
//         }
//     }
// }
