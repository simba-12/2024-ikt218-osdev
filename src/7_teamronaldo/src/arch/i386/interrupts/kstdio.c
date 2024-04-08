#include "kstdio.h"
#include "libc/terminal.h"  // Ensure terminal.h has the declarations for terminal functions.

// Helper function to reverse a string
void reverse(char* str) {
    int i = 0, j = 0;
    while (str[j] != '\0') j++; // string length
    j--;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Helper function to remove leading zeros from a string
void remove_leading_zeros(char* str) {
    int i = 0, j = 0;

    // Find first non-zero character
    while (str[i] == '0' && str[i] != '\0') i++;
    
    // If the string is all zeros, leave a single zero
    if (str[i] == '\0') {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Copy rest of string (overwriting leading zeros)
    while (str[i]) str[j++] = str[i++];

    // Null-terminate the modified string
    str[j] = '\0';
}

// Converts an integer value to a string
void itoa(int value, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle zero case
    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers if necessary
    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value;
    }

    // Convert digits to string
    while (value != 0) {
        int rem = value % base;
        str[i++] = (rem > 9)? (rem - 10) + 'a' : rem + '0';
        value = value / base;
    }

    // If number is negative, append '-'
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null-terminate string

    // Reverse the string
    reverse(str);

    // Remove any leading zeros
    if (base == 10) {
        remove_leading_zeros(str);
    }
}

// A simple implementation of printf supporting %s and %d
void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Look at the next format specifier
            if (*format == 's') {
                const char* s = va_arg(args, const char*);
                terminal_writestring(s);
            } else if (*format == 'd') {
                int d = va_arg(args, int);
                char buffer[12]; // Enough for a 32-bit integer
                itoa(d, buffer, 10);
                terminal_writestring(buffer);
            }
            format++; // Move past the format specifier
        } else {
            char c[2] = {*format, '\0'};
            terminal_writestring(c);
            format++; // Move to the next character in the format string
        }
    }

    va_end(args);
}
