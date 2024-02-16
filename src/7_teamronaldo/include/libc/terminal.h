#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

void terminal_initialize(void);
void terminal_writestring(const char* string);

#ifdef __cplusplus
}
#endif

#endif // TERMINAL_H
