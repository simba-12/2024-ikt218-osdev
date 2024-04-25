// // #ifndef UTIL_H
// // #define UTIL_H

// // #include <stdint.h>


// // // Function to fill a block of memory with a particular value.
// // void memset(void *dest, char val, uint32_t count);

// // // Function to send a byte of data to a specified port.
// // void outPortB(uint16_t port, uint8_t value);

// // // This line belongs to keyboard
// // char inPortB(uint16_t port);


// // // void vga_write_string(const char *message);
// // void print(const char *message);


// // size_t strlen(const char *str);



// // struct InterruptRegisters{
// //   uint32_t cr2;
// //   uint32_t ds;
// //   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
// //   uint32_t int_no, err_code;
// //   uint32_t eip, cs, eflags, useresp, ss; // pushed by the processor automatically
// // };





// // // Additional utility function prototypes can be added here.

// // #endif // UTIL_H



// #ifndef UTIL_H
// #define UTIL_H

// #include <stdint.h>

// void printf(const char *format, ...);
// void memset(void *dest, char val, uint32_t count);
// void outPortB(uint16_t port, uint8_t value);
// char inPortB(uint16_t port);  // this is for keyboard 
// size_t strlen(const char *str);

// struct InterruptRegisters {
//     //uint32_t cr2;
//     uint32_t ds;
//     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
//     uint32_t int_no, err_code;
//     uint32_t eip, cs, eflags, useresp, ss;
// };

// #endif // UTIL_H





#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

void printf(const char *format, ...);
void memset(void *dest, char val, uint32_t count);
void outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port);  // this is for keyboard 
size_t strlen(const char *str);
void outb(uint16_t port, uint8_t value); // Add this line for the outb function




// Define TICKS_PER_MS constant
//#define TICKS_PER_MS 100 // This is just an example, you should adjust it according to your timer frequency

// Function to get the current tick count
uint32_t get_current_tick();

struct InterruptRegisters {
    //uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

#endif // UTIL_H
