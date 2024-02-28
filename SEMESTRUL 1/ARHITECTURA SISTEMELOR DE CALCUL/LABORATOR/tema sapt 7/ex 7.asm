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
    ;Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. Sa se obtina sirul D prin intercalarea elementelor celor doua siruri.
    ;S: 1, 3, 5, 7
    ;t: 2, 6, 9, 4
    ;D: 1, 2, 3, 6, 5, 9, 7, 4
    s db 1,3,5,7 ; declar sirul s
    ls equ $-s ; stabilesc lungimea sirului l
    t db 2,6,9,4 ; declar sirul t
    l equ $-t ; stabilesc lungimea sirului t
    d times 1 dq 0 ; rezerv spatiul pentru noul sir d care va contine intercalarea
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov eax, 0
    mov esi, 0 ; incrementare pt sirul s/t
    mov edi, 0 ; incrementare pt sirul d
    mov ecx, ls ; nr de loop uri
    jecxz sfarsit ; instructiune de jump conditional se va termina cand ecx va ajunge 0
    repeta: ; intructiune loop
           mov al, [s+esi] ; pun in registrul al, fiecare element din sirul s
           mov [d+edi], al ; din registru pun in variabila d / 0 2 4
           inc edi
           mov al, [t+esi] ; pun in registrul al, fiecare element din sirul t
           mov [d+edi], al ; din registru pun in variabila d / 1 3 5
           inc esi ; incrementez esi ul
           inc edi
    loop repeta
    sfarsit: ; aici se termina loop ul
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
