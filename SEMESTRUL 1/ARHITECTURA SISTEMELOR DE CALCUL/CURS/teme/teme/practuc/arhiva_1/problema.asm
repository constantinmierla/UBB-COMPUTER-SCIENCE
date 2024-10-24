bits 32 

global start        

extern exit, fopen, fclose               
import exit msvcrt.dll    
import fopen msvcrt.dll
import fclose msvcrt.dll

; Se dă un șir de 10 numere în baza 16 în fișierul input.txt. 
; Să se determine cifra minimă din fiecare număr.
; Să se afișeze acest șir al cifrelor minime, în baza 10, pe ecran.


segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db 'r', 0
    descriptor_fisier dd -1
    
    buffer db 0
    numar dd 0

segment code use32 class=code
    start:
        ; fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        ; verific daca am deschis corect fisierul
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        mov ecx, 10
        citire:
            push ecx
            
            mov ecx, 8
            citire_un_numar:
                push ecx
                ; fread(text, size, count, desc)
                push dword [descriptor_fisier]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4
                
                pop ecx
                
                
            
        loop citire
        
        stop_citire
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
    
    finish:
        push dword 0    
        call [exit]       
