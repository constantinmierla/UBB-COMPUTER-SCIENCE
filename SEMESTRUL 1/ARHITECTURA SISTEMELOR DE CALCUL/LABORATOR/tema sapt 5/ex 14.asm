bits 32 

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data
    
    a db 9
    b dw 2
    c dd 8
    d dq 4


segment code use32 class=code

    ;14. (a+d)-(c-b)+c = a+d - c + b + c = a + d + b   ;a - byte, b - word, c - double word, d - qword - Interpretare fara semn

    start:;;;
       ; mov eax,0
        ;mov ebx, 0
        ;mov ebx, [d] ; ebx = 4
        ;mov al, [a]; al = 9
        ;mov ah, 0
        ;add ax, [b] ; ax = 9+2 = 11
        ;add eax, ebx ; eax = 11+4 = 15
        mov eax, 0
        mov al, [a]
        mov ah, 0
        mov ebx, [d] 
        add eax, ebx ; a+d = 13
        mov ecx, 0
        mov cx, [c]
        add eax, ecx ; (a+d) + c = 13 + 8 = 21
        sub cx, [b] ; c-b = 8-2=6
        sub eax, ecx ; (a+d)-(c-b)+c = 21 - 6 = 15
        push    dword 0      
        call    [exit]      