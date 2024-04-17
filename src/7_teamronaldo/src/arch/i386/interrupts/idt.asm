section .text
global idt_flush
global isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9
global isr10, isr11, isr12, isr13, isr14, isr15
global irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9
global irq10, irq11, irq12, irq13, irq14, irq15
extern isr_handler
extern irq_handler

idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ;sti
    ret

%macro ISR_NOERRCODE 1
isr%1:
    cli
    push dword 0  ; Error code placeholder
    push dword %1 ; ISR number
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
isr%1:
    cli
    push dword %1 ; ISR number (error code is already on the stack)
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_NOERRCODE 9
ISR_NOERRCODE 15

ISR_ERRCODE 8   ; Double Fault Exception
ISR_ERRCODE 10  ; Invalid TSS Exception
ISR_ERRCODE 11  ; Segment Not Present
ISR_ERRCODE 12  ; Stack-Segment Fault
ISR_ERRCODE 13  ; General Protection Fault
ISR_ERRCODE 14  ; Page Fault

isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call isr_handler
    pop eax
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

%macro IRQ 2
irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39 
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

irq_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call irq_handler
    pop eax
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret
