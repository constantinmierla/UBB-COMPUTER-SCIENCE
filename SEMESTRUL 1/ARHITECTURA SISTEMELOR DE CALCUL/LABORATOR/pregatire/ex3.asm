bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll

extern fopen,fclose,printf,scanf,gets

import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import gets msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    mod_citire db "%s",0
    mod_afisare db "%d ",0
    sursa times 100 db -1
    destinatie times 100 db -1
    contor dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword sursa
        call [gets]
        add esp, 4
        
        mov esi, sursa
        mov edi, destinatie
        
        repeta:
        
            cmp byte[esi], 0
            je final
            
            cmp byte[esi], ' '
            je afiseaza
            jne stocheaza
            
            stocheaza:
                movsb 
                jmp repeta
            
            afiseaza:
                sub edi, 1
                    repeta1:
                        cmp edi, destinatie-1
                        je final1
                        
                        add byte[contor],1
                        sub edi, 1
                        jmp repeta1
                        
                    final1:
                        push dword [contor]
                        push dword mod_afisare
                        call [printf]
                        add esp, 4*2
                        
                        mov byte[contor], 0
                        mov edi, destinatie
                        add esi, 1
                        jmp repeta
            
            final:
                    sub edi, 1
                    repeta2:
                        cmp edi, destinatie-1
                        je final2
                        
                        add byte[contor],1
                        sub edi, 1
                        jmp repeta2
                        
                        
                        
                    final2:
                        push dword [contor]
                        push dword mod_afisare
                        call [printf]
                        add esp, 4*2
                        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
