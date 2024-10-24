bits 32 

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data

    a db 10
    b dw 3
    c dd 1
    d dq 3
    val1 resw 1

segment code use32 class=code

    ; 29. (a+a)-(b+b)-(c+d)+(d+d)  = 20-6-4+6 = 16    a - byte, b - word, c - double word, d - qword - Interpretare cu semn

    start:
        
        ; a+a
        mov al, [a]     ; al = a
        add al, [a]     ; al = a + a
        cbw       
        ;b+b
        mov bx, [b]     ; bx = b
        add bx, [b]     ; bx = b + b       
        ;(a+a)-(b+b)
        sub ax, bx      ; ax = ax - bx
        mov [val1], ax  ; val1 = ax    
        ;c+d
        mov ax, [c]     ; dx:ax = c
        cdq                    
        mov ebx, [d]    ; ecx:ebx = d
        add eax, ebx    ; edx+ecx+CF : eax+ebx
        adc edx, ecx        
        ;(c+d)+(d+d)
        add eax, ebx    ; edx+ecx+CF : eax+ebx
        adc edx, ecx
        add eax, ebx    ; edx+ecx+CF : eax+ebx
        adc edx, ecx
        ;(a+a)-(b+b)-(c+d)+(d+d)
        mov ebx, eax   
        mov ax, [val1]  

        push    dword 0      