section .text
global isr0
global isr1
global isr2
global isr33
global irq1
extern isr_handler

%define PIC_EOI 0x20
%define PIC1_COMMAND 0x20 ; Assuming PIC1_COMMAND is at I/O port 0x20
%define PIC2_COMMAND 0xA0 ; Assuming PIC2_COMMAND is at I/O port 0xA0

; IRQ 0 Handler (Timer)
irq0:
    ; Handle IRQ 0 interrupt here (Timer)
    ; Example: Update system clock, scheduler, etc.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 1 Handler (Keyboard)
irq1:
    ; Handle IRQ 1 interrupt here (Keyboard)
    ; Example: Read the scancode from the keyboard controller, process it, etc.
    ; Send End of Interrupt (EOI) signal to PIC
    cli
    ;mov al, PIC_EOI
    ;out PIC1_COMMAND, al
    jmp isr_common_stub
    ret

; IRQ 2 Handler (Cascade for Slave PIC)
irq2:
    ; Handle IRQ 2 interrupt here (Cascade for Slave PIC)
    ; Example: Handle cascaded interrupts from the slave PIC, if any.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    out PIC2_COMMAND, al
    ret

; IRQ 3 Handler (COM2/COM4)
irq3:
    ; Handle IRQ 3 interrupt here (COM2/COM4)
    ; Example: Handle interrupts from COM2/COM4 serial port.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 4 Handler (COM1/COM3)
irq4:
    ; Handle IRQ 4 interrupt here (COM1/COM3)
    ; Example: Handle interrupts from COM1/COM3 serial port.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 5 Handler (LPT2)
irq5:
    ; Handle IRQ 5 interrupt here (LPT2)
    ; Example: Handle interrupts from LPT2 parallel port.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 6 Handler (Floppy Disk)
irq6:
    ; Handle IRQ 6 interrupt here (Floppy Disk)
    ; Example: Handle interrupts from the floppy disk controller.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 7 Handler (LPT1)
irq7:
    ; Handle IRQ 7 interrupt here (LPT1)
    ; Example: Handle interrupts from LPT1 parallel port.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 8 Handler (RTC)
irq8:
    ; Handle IRQ 8 interrupt here (RTC)
    ; Example: Handle interrupts from the Real-Time Clock (RTC).
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 9 Handler (ACPI/IRQ2)
irq9:
    ; Handle IRQ 9 interrupt here (ACPI/IRQ2)
    ; Example: Handle interrupts from ACPI or IRQ2.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 10 Handler (Reserved)
irq10:
    ; Handle IRQ 10 interrupt here (Reserved)
    ; Example: Handle any specific device or reserved interrupt.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 11 Handler (Reserved)
irq11:
    ; Handle IRQ 11 interrupt here (Reserved)
    ; Example: Handle any specific device or reserved interrupt.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 12 Handler (PS/2 Mouse)
irq12:
    ; Handle IRQ 12 interrupt here (PS/2 Mouse)
    ; Example: Handle interrupts from PS/2 mouse controller.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 13 Handler (FPU/Coprocessor/Inter-processor)
irq13:
    ; Handle IRQ 13 interrupt here (FPU/Coprocessor/Inter-processor)
    ; Example: Handle interrupts from FPU, coprocessor, or inter-processor.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 14 Handler (Primary ATA Hard Disk)
irq14:
    ; Handle IRQ 14 interrupt here (Primary ATA Hard Disk)
    ; Example: Handle interrupts from the primary ATA hard disk controller.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

; IRQ 15 Handler (Secondary ATA Hard Disk)
irq15:
    ; Handle IRQ 15 interrupt here (Secondary ATA Hard Disk)
    ; Example: Handle interrupts from the secondary ATA hard disk controller.
    ; Send End of Interrupt (EOI) signal to PIC
    mov al, PIC_EOI
    out PIC1_COMMAND, al
    ret

isr33:
    cli
    push byte 0            ; Dummy error code
    push byte 33           ; Interrupt number (33 for keyboard)
    jmp isr_common_stub

isr0:
    cli
    push byte 0            ; Dummy error code
    push byte 0            ; Interrupt number (0)
    jmp isr_common_stub

isr1:
    cli
    push byte 0            ; Dummy error code
    push byte 1            ; Interrupt number (1)
    jmp isr_common_stub

isr2:
    cli
    push byte 0            ; Dummy error code
    push byte 2            ; Interrupt number (2)
    jmp isr_common_stub

; Common ISR stub for saving context and calling the C handler
isr_common_stub:
    pusha                   ; Push all general-purpose registers
    mov ax, ds              ; Save DS
    push eax                ; Push EAX (which contains DS)
    mov ax, 0x10            ; Load kernel data segment descriptor
    mov ds, ax              ; Set DS to kernel data segment
    mov es, ax              ; Set ES to kernel data segment
    mov fs, ax              ; Set FS to kernel data segment
    mov gs, ax              ; Set GS to kernel data segment
    mov eax, esp            ; Get stack pointer
    push eax                ; Push it (stack frame for C handler)
    call isr_handler        ; Call C ISR handler
    pop eax                 ; Clean up stack (original ESP)
    pop eax                 ; Restore original DS from stack to EAX
    mov ds, ax              ; Restore DS from EAX
    mov es, ax              ; Restore ES
    mov fs, ax              ; Restore FS
    mov gs, ax              ; Restore GS
    popa                    ; Pop all general-purpose registers
    add esp, 8              ; Clean up the stack (dummy error code and interrupt number)

    ; Check if there was an error during ISR handling
    jc error_occurred       ; If carry flag (CF) is set, jump to error handling
    sti                     ; Re-enable interrupts
    iret                    ; Return from interrupt

error_occurred:
    ; Error handling code here
    ; This code will be executed if an error occurred during ISR handling
    hlt                     ; Halt the system or perform other error handling actions
