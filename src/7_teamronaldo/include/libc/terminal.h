#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> // Include for uint8_t type

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_writestring(const char* string);

extern uint8_t terminal_color; // Declare terminal_color as an external variable

#ifdef __cplusplus
}
#endif

#endif // TERMINAL_H
