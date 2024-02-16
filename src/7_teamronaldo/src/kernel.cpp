
extern "C" {
    #include "libc/gdt.h"
    #include "libc/terminal.h"
}

// Assume terminal_writestring is defined elsewhere in your kernel
extern void terminal_writestring(const char*);

extern "C" int kernel_main() {
    static int run_count = 0;
    if (run_count == 0) {
        terminal_writestring("Hello, World! \n");
        run_count++;
    } else {
        terminal_writestring("Entered kernel_main again!\n");
    }
   
    // Initialize the GDT
     init_gdt();

    // Print confirmation message using a kernel-specific function
    terminal_writestring("GDT setup successfully.\n");
    
    // Further kernel initialization...

    return 0;
}