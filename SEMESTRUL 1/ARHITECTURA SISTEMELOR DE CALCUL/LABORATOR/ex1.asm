bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a resd 1
segment code use32 class=code
    start:
    
        xchg eax, a
        push    dword 0
        call    [exit]
