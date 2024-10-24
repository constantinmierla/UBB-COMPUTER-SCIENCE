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
    ; ex 15 : (a*2)+2*(b-3)-d-2*c
    ; ex 30 : [(a-b)*5+d]-2*c
    a db 8
    b db 3
    c db 2
    d dw 3
; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AL, [a]       ; AL = a
    MOV BL, [b]       ; BL = b
    MOV CL, [c]       ; CL = c
    MOV DX, [d]       ; DX = d

    ;ex 15 (a*2) + 2*(b-3) - d - 2*c

    ADD AL, AL ; AX = 2*a = 2*8 = 16
    SUB BL, 3 ; BX = b-3 = 0
    ADD BL, BL ; BX = (b-3)*2 = 0
    ADD CL, CL ; CX = 2*c = 4
    ADD AX, BX ; AX = 2*a + 2*(b-3) = 16 + 0 = 16
    SUB AX, DX ; AX = 2*a + 2*(b-3) - d = 16 - 3 = 13
    SUB AX, CX ; AX = 2*a + 2*(b-3) - d - 2*c = 13-4 = 9
    
    
    MOV EAX, 0
    MOV EDX, 0
    MOV EBX, 0
    MOV ECX, 0
        ; ex 30 : [(a-b)*5+d]-2*c

    MOV AL, 5 ; AL = 5
    MOV DL, [a] ; DL = a = 8
    SUB DL, [b] ; DL = a-b = 8-3=5
    MUL DX ; AX = 5*(a-b) =25
    ADD AX, [d] ; 5*(a-b)+d = 25+3=28
    MOV BL, [c] ; BL = c = 2
    ADD BL, BL ;  BL = 2*c = 4
    SUB AX, BX ;  AX = [(a-b)*5+d]-2*c = 24
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
