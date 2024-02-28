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
    a db 1
    b dw 2
    c dd 8
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; ... 14. c-b-(a+a)-b
     ; c - b
     mov eax, 0
     mov ebx, 0
     mov ecx, 0
     mov edx, 0
        mov eax, [c]
        sub ax, [b] ; eax = 8-2 = 6

    ; (a + a)
        mov bl, [a] 
        add bl, [a] ; al = 1 + 1 = 2
        cbw 
        
    ; c - b - (a + a) - b
        sub eax, ebx
        sbb edx, ecx
        sub eax, [b] ; 6 - 2 - 2 = 2

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
