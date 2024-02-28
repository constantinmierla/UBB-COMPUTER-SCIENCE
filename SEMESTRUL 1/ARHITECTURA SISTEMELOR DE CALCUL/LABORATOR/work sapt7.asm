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
    s1 db 2,3,9,5,6
    l1 equ $-s1
    s2 db 4,5,6,,4,8,9,20
    l2 equ $-s2
    d times (l1+l2) db 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        cmp l1, l2
        
        ja l1maimare 
        ; l1 < l2
                    
        mov ecx, l1
        mov esi, s1
        mov edi, s2
        
       
        repeta2:
        loop repeta2     
        
        l1maimare:
        mov ecx, l1
        mov esi, s1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
