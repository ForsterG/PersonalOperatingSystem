    
    
    
    mov ebx, 0h
    xor eax, eax
    mov es, ax
    mov di, 0x8000
    mov ecx, 24
    mov edx, 0534D4150h
    xor eax, eax
    mov eax, 0E820h
    int 15h

int15loop:
cmp ebx, 0
je int15looparound
jc int15error ; check carry
cmp eax, edx ;eax shoudl be edx ;es:di should be same
jne int15error
xor eax, eax
mov eax, 0E820h
mov ecx, 24 ;ecx bytes returned ;ebx continuation
add di, 24
int 15h
jmp int15loop
int15error:
int15looparound: