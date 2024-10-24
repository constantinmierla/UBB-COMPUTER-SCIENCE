bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data

    a db 2
    b db 2
    c db 6
    d dd -3
    x dq 1

segment code use32 class=code
    start:
    ;29. (a+b)/(c-2)-d+2-x = (2+2)/(6-2)-(-3)+2-1= 4/4+3+1 = 1+4 = 5;     a,b,c-byte; d-doubleword; x-qword       - CU SEMN
    mov eax, 0
    mov al, [a]     ; al = a
    add al, [b]     ; al = al + b = a + b
    mov bl, [c]     ; bl = c
    sub bl, 2       ; bl = bl - 2 = c - 2
    cbw
    ;(a+b)/(c-2)   
    idiv byte bl     ; al = (a+b)/(c-2)   
    cbw
    cwd             
    ;(a+b)/(c-2)-d 
    mov ebx, [d]    ; ebx = d
    sub eax, ebx    ; eax =eax - ebx 
    ;(a+b)/(c-2)-d+2  
    add eax, 2      ; eax = eax + 2
    cwd
    ;(a+b)/(c-2)-d+2-x
    mov ebx, [x]    ; ebx = x
    sub eax, ebx    
    sbb edx, ecx
    
 
        push    dword 0      
        call    [exit]       