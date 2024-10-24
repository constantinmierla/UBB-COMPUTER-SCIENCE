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
;ex 15 : f*(e-2)/[3*(d-5)]
;ex 30 : 100/(e+h-3*a)
    a db 3
    d db 6
    e dw 8
    f dw 9
    h dw 10
; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    ;ex 15 f*(e-2)/[3*(d-5)]
    MOV EAX, 0
    MOV EBX, 0
    MOV ECX, 0
    MOV EDX, 0
    
    MOV AX, [f] ; AX = f = 9
    MOV BX, [e] ; BX = e = 8
    SUB BX, 2 ; BX = e-2 = 6
    MUL BX ; AX = f*(e-2) = 9*6=54
    
    MOV BX, [d] ; BX = d = 6
    SUB BX, 5 ; BX = d-5 = 1
    MOV ECX, EAX ; il mut pe f*(e-2) in ECX
    
    MOV EAX, 0
    MOV AX, 3
    MUL BX ; AX = 3*(d-5) = 3
    
    MOV EAX, ECX ; il duc inapoi pe f*(e-2) in EAX
    
    DIV BX ; AX = AX/BX = f*(e-2)/[3*(d-5)] = 54/3 = 18
    
    MOV EAX, 0
    MOV EBX, 0
    MOV ECX, 0
    MOV EDX, 0
    
    
    ;ex 30 : 100/(e+h-3*a)
    MOV BL, [e] ; BL = e = 8
    ADD BL, [h] ; BL = e+h = 8+10 = 18
    MOV BH, 0
    MOV AL, 3 ; AL = 3
    MUL byte [a] ; AX = 3*3 = 9
    SUB BX, AX ;  BX = e+h-3*a = 18-9 = 9
    MOV AX, 100; AX = 100
    MOV DX, 0
    DIV BX ; AX = AX//BX = 100/(e+h-3*a) = 100/9 = 11
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
