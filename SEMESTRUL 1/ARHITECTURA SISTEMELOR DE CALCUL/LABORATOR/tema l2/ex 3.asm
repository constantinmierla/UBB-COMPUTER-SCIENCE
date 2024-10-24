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
    ; ex 15: (a-b+c)-(d+d)
    ; ex 30:  a-b+(c-d+a)
    a dw 2
    b dw 1
    c dw 8
    d dw 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
    ;ex 15
    MOV AX, [a] ; AX = a = 2
    SUB AX, [b] ; AX = a-b = 2-1 = 1
    ADD AX, [c] ; AX = a-b+c = 1+8 = 9
    MOV DX, [d] ; DX = d = 1
    ADD DX, [d] ; DX = d+d = 1+1 = 2
    SUB AX, DX  ; AX = (a-b+c)-(d+d) = 9-2 = 7
    
    MOV EAX, 0
    MOV EDX, 0
    
    ;ex 30  a-b+(c-d+a)
    MOV AX, [a] ; AX = a = 2
    SUB AX, [b] ; AX = a-b = 2-1 = 1
    MOV DX, [c] ; DX = 8
    SUB DX, [d] ; DX = 8-1 = 7
    ADD DX, [a] ; DX = 7+2 = 9
    ADD AX, DX  ; 1+9 = 10
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
