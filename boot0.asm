[BITS 16]
[ORG 0x7C00]
;nasm -f bin boot0.asm -o boot0.bin

    cli
    jmp 0h:next_line ;Canonicalizing  by long jumping to %CS:%EIP
next_line:

    xor ax, ax ; zero out ax and set all data segments to 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ax, 7h ; build the stack environment at the top of our free memory
    mov ss, ax
    mov esp, 0xFFFF

reset_drive:
    clc ; clear carry flag for error checking
    mov ah, 0 ; Set up BIOS reset command
    int 13h ; call int 13

    jc resetDriveError; jump if carry = 1, check for error code
    or ah, ah ; check for return code
    
    jnz resetDriveError


%include "boot1.size" ; Contains the number of sectors that boot1 takes up and label NumOfSectors
loadBoot1:
    clc ; clear carry flag for error detection
    mov ax, 0h

    mov es, ax; buffer address segment
    mov bx, 500h; buffer address address

    mov ah, 02h; command
    mov al, NumOfSectors; sectors to read count
    mov ch, 0h; cylinder
    mov cl, 2h;sector
    mov dh, 0h; head
    mov dl, 80h; drive 1st hard disk
    int 13h ; call int

    jc loadBoot1Error ; error on carry = 1
    or ah, ah ; check for return code
    jnz loadBoot1Error
    jmp 0x500

msg2   db 'Error on loading Boot1 Aborting Boot Loader', 13, 10, 0
loadBoot1Error:
    mov si, msg2 ; point si to msg byte
    cld ;clear direction flag
    jmp ch_loop

msg1   db 'Error on reseting drive Aborting Boot Loader', 13, 10, 0
resetDriveError:
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

    


msg   db 'Hello World', 13, 10, 0
endBoot0:    
    mov si, msg
   cld
ch_loop_test:
   lodsb
   or al, al ; zero=end or str
   jz hang_test   ; get out
   mov ah, 0x0E
   mov bh, 0
   int 0x10
   jmp ch_loop_test
   
   hang_test:
   jmp hang_test

times 510-($-$$) db 0 ; Fill up the file with zeros
dw 0AA55h ; Boot sector identifyer
