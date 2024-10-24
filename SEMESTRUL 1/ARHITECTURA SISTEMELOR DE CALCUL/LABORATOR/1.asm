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
;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
;15. a+b-c+(d-a)
;30. (b+c+a)-(d+c+a)
    a db 2
    b dw 5
    c dd 3
    d dq 3
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;15. a+b-c+(d-a)
        mov EAX, 0
        mov AL, [a]
        mov AH, 0
        mov DX, [b]
        ADD AX, DX ; a+b = 7
        mov EDX, 0
        mov EDX, [c] ; c
        SUB EAX, EDX ; a+b-c = 4
        push EAX
        mov EAX, 0
        mov EAX, [d] 
        mov EBX, 0
        mov BL, [a]
        sub EAX, EBX ; d-a = 1
        mov EBX, EAX
        mov EAX, 0
        pop EAX ; a+b-c = 4
        add EAX, EBX ; a+b-c+(d-a) = 4+1 = 5
        mov EAX, 0
        mov EBX, 0
        mov ECX, 0
        mov EDX, 0
        ;30. (b+c+a)-(d+c+a)
        mov EAX, d
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
