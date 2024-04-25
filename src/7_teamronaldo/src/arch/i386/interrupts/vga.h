
#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

void vga_initialize(void);
void printf(const char *format, ...);



// Add function prototypes for cursor movement functions here
void move_cursor_left(void);
void move_cursor_right(void);
void move_cursor_up(void);
void move_cursor_down(void);

#endif
