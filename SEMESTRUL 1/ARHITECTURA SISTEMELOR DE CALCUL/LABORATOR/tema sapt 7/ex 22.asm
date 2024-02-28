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
;Se dau 2 siruri de octeti S1 si S2 de aceeasi lungime. Sa se construiasca sirul D astfel incat fiecare element din D sa reprezinte minumul dintre elementele de pe pozitiile corespunzatoare din S1 si S2.
;S: 1, 3, 6, 2, 3, 7
;t: 6, 3, 8, 1, 2, 5
;D: 1, 3, 6, 1, 2, 5
    s db 1,3,6,2,3,7
    l equ $-s
    t db 1,3,6,1,2,5
    d times 1 dq 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l ; lungimea sirului
        mov esi, 0 ; incrementare
        mov eax, 0 ; golire
        mov ebx, 0
        jecxz sfarsit ; se va termina cand ecx va fi 0
        repeta:
            mov al, [s+esi] 
            mov bl, [t+esi]
            cmp al, bl
            jle done  
                mov [d+esi], al ; daca al < bl
            done:
                mov [d+esi], bl ; daca al >= bl
            inc esi
         
        loop repeta 
        sfarsit: l ; terminare loop
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
