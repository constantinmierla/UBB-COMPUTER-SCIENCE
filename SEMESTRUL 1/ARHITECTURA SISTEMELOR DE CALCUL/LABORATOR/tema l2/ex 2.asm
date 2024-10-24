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
    ;15: a-b-d+2+c+(10-b)
    ;30: d-(a+b)-(c+c)
    a db 3
    b db 1
    c db 5
    d db 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;ex 15 a-b-d+2+c+(10-b)
    MOV AL, [a] ; AL = a = 3
    SUB AL, [b] ; AL = a-b = 3-1 = 2
    SUB AL, [d] ; AL = a-b-d = 2-1 = 1
    ADD AL, 2   ; AL = a-b-d+2 = 1+2 = 3
    ADD AL, [c] ; AL = a-b-d+2+c = 3+5 = 8
    MOV DL, 10  ; DL = 10
    SUB DL, [b] ; DL = 10-b = 10-1 = 9
    ADD AL, DL  ; AL = a-b-d+2+c+(10-b) = 8+9 = 17 
    
    MOV EAX, 0
    MOV EDX, 0
    
        ;ex 30 d-(a+b)-(c+c)
    MOV AL, [d] ; AL = d
    MOV DL, [a] ; DL = a
    ADD DL, [b] ; DL = a + b
    SUB AL, DL  ; AL = d - (a+b)
    MOV DL, [c] ; DL = c
    ADD DL, [c] ; DL = c+c
    SUB AL, DL  ; AL = d - (a+b)- (c+c)
  
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
