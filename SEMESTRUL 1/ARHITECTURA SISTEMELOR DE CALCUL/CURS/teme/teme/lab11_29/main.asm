bits 32

global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

extern functie_afisare
extern parsare_cuvant

segment data use32 class=data
    format_text db "%s", 0
    text1 times 100 db 0
    nr_cuv dd 0
    
    sir_numere times 100 dd 0
    format_nr db "%d ", 0

segment code use32 class=code
    start:
        mov edx, 0    ; retin numarul de cuvinte
    
        mov edi, sir_numere
        cld
        
        repeta:
            ; citesc cuvant
            push dword text1
            push dword format_text
            call [scanf]
            add esp, 4 * 2
            
            ; verifici daca am ajuns la punct
            mov esi, text1
            lodsb
            cmp al, '.'
            je citire_finalizata
            
            ; apelez functia de parsare a cuvantului
            push dword text1
            call parsare_cuvant
            
            ; incrementez nr de cuvinte
            mov edx, [nr_cuv]
            add edx, 1
            mov [nr_cuv], edx
        jmp repeta

        citire_finalizata:
            ; afisez numerele pe ecran
            push dword sir_numere
            push dword [nr_cuv]
            call functie_afisare
            
    sfarsit:
        push dword 0
        call [exit]