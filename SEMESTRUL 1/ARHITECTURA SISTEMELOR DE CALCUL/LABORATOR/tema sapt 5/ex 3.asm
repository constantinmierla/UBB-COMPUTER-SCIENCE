bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 2
    b db 1
    c db 4
    d dd 3
    x dq 2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;14. x+(2-a*b)/(a*3)-a+c; cu semn
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        mov edx, 0
        
         mov al, [a] ; al = a
         mov ah, 0
         mov bl, [b]
         mov bh, 0
         imul bx ; a*b = 2*1 = 2
         mov bx, ax
         mov ax, 2
         sub ax, bx ; (2-a*b) = 2-2 = 0
         push eax
         mov al, [a] ; ax = 2
         mov bl, 3   ; bx = 3 = (a*3)
         imul bl       ; ax = 6
         mov ah,0
         mov bx, ax   ; bx = 6
         pop eax      ; ax = 0
         idiv bx ; eax = 0 = (2-a*b)/(a*3)
         add eax, [x] ; eax = x+(2-a*b)/(a*3) = 1
         mov ebx, eax
         mov eax, 0
         mov al, [c] ; al = 4 ; al = c
         sub al, [a] ; al = 4-2 = 2 ; al = c-a
         cbw
         cwde
         add eax, ebx; eax = x+(2-a*b)/(a*3)-a+c = 3
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
