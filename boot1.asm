[BITS 16]
[ORG 0x500]

    mov ax, 7h ; build the stack environment at the top of our free memory
    mov ss, ax
    mov esp, 0xFFFF 

%include "main.size"
loadkernel:
    clc ; clear carry flag for error detection
    mov ax, 0h

    mov es, ax; buffer address segment
    mov bx, 2000h; buffer address address

    mov ah, 02h; command
    mov al, NumOfSectors ; sectors to read count
    mov ch, 0h; cylinder
    mov cl, 3h;sector
    mov dh, 0h; head
    mov dl, 80h; drive 1st hard disk
    int 13h ; call int

    jc loadBoot1Error ; error on carry = 1
    or ah, ah ; check for return code
    jnz loadBoot1Error
    jmp enterprotectedmode


msg1   db 'Error on reseting drive Aborting Boot Loader', 13, 10, 0
loadBoot1Error:
    mov si, msg1 ; point si to msg byte
    cld ;clear direction flag
    jmp ch_loop

ch_loop:
    lodsb ;load string byte
   or al, al ; check if the character is zero
   jz hang   ; get out if the character is zero
   mov ah, 0x0E ; bios function call display character
   ;mov bh, 0
   int 0x10 ; bios call print character
   jmp ch_loop
hang:
    jmp $ ; loop forever

enterprotectedmode:
        cli                     ; Disable interrupts, we want to be alone
        xor ax, ax
        mov ds, ax              ; Set DS-register to 0 - used by lgdt
        lgdt [gdt_desc]         ; Load the GDT descriptor
        
        mov eax, cr0            ; Copy the contents of CR0 into EAX
        or eax, 1               ; Set bit 0
        mov cr0, eax            ; Copy the contents of EAX into CR0
        jmp 08h:clear_pipe      ; Jump to code segment in gdt, offset clear_pipe
        
    


[BITS 32]                       ; We now need 32-bit instructions
clear_pipe:
        mov ax, 0000000000010000b ; second entry in the gdt
        mov ds, ax              ; Move a valid data segment into the data segment register
        mov ss, ax              ; Move a valid data segment into the stack segment register
        mov esp, 090000h        ; Move the stack pointer to 090000h
        jmp 08h:02000h          ; Jump to section 08h (code), offset 01000h, need to update to not be hardcoded to 0x2000




gdt:                    ; Address for the GDT
gdt_null:               ; Null Segment because we start at one
        dd 0
        dd 0
gdt_code:               ; Code segment, read/execute, nonconforming
        dw 0FFFFh
        dw 0
        db 0
        db 10011010b
        db 11001111b
        db 0
gdt_data:               ; Data segment, read/write, expand down
        dw 0FFFFh
        dw 0
        db 0
        db 10010010b
        db 11001111b
        db 0
gdt_end:                ; Used to calculate the size of the GDT
gdt_desc:                       ; The GDT descriptor
        dw gdt_end - gdt - 1    ; Limit (size)
        dd gdt                  ; Address of the GDT

times 510-($-$$) db 0 ; Fill up the file with zeros
dw 0AA55h ; Boot sector identifyer
;nasm -f bin boot0.asm -o boot0.bin
; load load kernel from drive into low memory
; turn on protected mode
; load kernel into high memory






