

// In your C file (potentially isr.c)

#include "isr.h"
#include "terminal.h"
#include "kstdio.h"

// Corrected to take a pointer to registers_t
/*void isr_handler(registers_t* regs) {
    // Write the interrupt message
    terminal_writestring("Received interrupt: ");

    // Convert interrupt number to string
    char int_num_str[10]; // Enough space for 32-bit integer
    itoa(regs->int_no, int_num_str, 10); // Convert to string with base 10, corrected to use pointer

    // Write the converted interrupt number to the terminal
    terminal_writestring(int_num_str);
    terminal_writestring("\n");
}*/
// itoa - integer to ASCII conversion
void itoa(int num, char *str, int base) {
    int i = 0;
    bool isNegative = false;

    // Handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // In standard itoa(), negative numbers are handled only with base 10.
    // Otherwise, numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    // Remove the leading zeros
    remove_leading_zeros(str);
}

void reverse(char *str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void remove_leading_zeros(char* str) {
    int index, i;
    index = 0;

    // Find index of first non-zero character
    while(str[index] == '0') {
        index++;
    }

    // If no non-zero character found, it's a string of all zeros
    if (str[index] == '\0') {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Shift all characters to the beginning of the string
    for(i = 0; str[i + index] != '\0'; i++) {
        str[i] = str[i + index];
    }
    str[i] = '\0'; // Null-terminate the string
}

