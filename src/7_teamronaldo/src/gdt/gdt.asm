
section .text
global gdt_flush

gdt_flush:
    ; Argument (pointer to gdt_ptr structure) is passed in via the stack
    mov eax, [esp + 4]  ; Get the gdt_ptr address from the stack

    lgdt [eax]          ; Load the new GDT with the lgdt instruction

    ; Update data segment registers
    mov ax, 0x10      ; 0x10 is the selector for the data segment in GDT, assuming a flat memory model
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Far jump to update the code segment register (CS)
    ; The jump target is a label in the same segment to ensure the offset is correct
    jmp 0x08:flush_cs   ; 0x08 is the selector for the code segment in GDT

flush_cs:
    ret
