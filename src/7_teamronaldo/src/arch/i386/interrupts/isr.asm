
section .text
global isr0, isr1, isr2 ; Adjusted to remove underscore for clarity
extern isr_handler       ; Assuming the handler in C is named isr_handler

; ISR for keyboard (IRQ1 remapped to vector 33)
global isr33
extern keyboard_interrupt_handler

isr33:
    cli                    ; Clear interrupts to prevent reentry
    push byte 0            ; Push a dummy error code
    push byte 33           ; Push interrupt number
    jmp isr_common_stub    ; Jump to common stub

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

; isr_common_stub:
;     pusha
;     mov ax, ds
;     push eax
;     mov ax, 0x10
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov eax, esp
;     push eax
;     call isr_handler ; Ensure this matches the C function name
;     pop eax
;     pop eax
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     popa
;     add esp, 8
;     sti
;     iret

isr_common_stub:
    pusha                   ; Push all registers
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
    pop eax                 ; Restore original DS into EAX
    mov ds, ax              ; Restore DS
    mov es, ax              ; Restore ES
    mov fs, ax              ; Restore FS
    mov gs, ax              ; Restore GS
    popa                    ; Pop all registers
    add esp, 8              ; Clean up the pushed error code and interrupt number
    sti                     ; Set interrupts to re-enable further interrupts
    iret                    ; Return from interrupt
