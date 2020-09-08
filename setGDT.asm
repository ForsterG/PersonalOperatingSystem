[SECTION .text]

[GLOBAL] _ZN21GlobalDescriptorTable6setGDTEtt

_ZN21GlobalDescriptorTable6setGDTEtt:
    pop eax
    pop ebx
    pop ecx
    pop edx

    mov ds, dx
    mov es, dx
    mov fs, dx
    
    push edx
    push ecx
    push ebx
    push eax
    ret
