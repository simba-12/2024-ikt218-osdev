#ifndef KSTDIO_H
#define KSTDIO_H

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void printf(const char* format, ...);
void itoa(int value, char* str, int base);
void reverse(char* str);
void remove_leading_zeros(char* str);

#ifdef __cplusplus
}
#endif

#endif // KSTDIO_H
