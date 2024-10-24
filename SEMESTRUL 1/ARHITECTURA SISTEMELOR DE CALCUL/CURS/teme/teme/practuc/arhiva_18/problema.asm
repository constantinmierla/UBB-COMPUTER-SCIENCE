bits 32 

global start        

extern exit, fopen, fread, printf, fclose               
import exit msvcrt.dll   
import fopen msvcrt.dll
import fread msvcrt.dll 
import printf msvcrt.dll
import fclose msvcrt.dll

; Se citeste un sir din input.txt. sa se afiseze invers.

segment data use32 class=data
    nume_fisier db 'input.txt', 0
    descriptor_fisier dd -1
    mod_acces db 'a+', 0
    
    sir_caractere times 100 db 0
    descriptor_sir dd -1
    numar_caractere dd 0
    
    buffer db 0
    
    format_char db '%c', 0
    format_int db '%d', 0

segment code use32 class=code
    start:
        ; fopen
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        ; pregatire citire
        mov edi, sir_caractere
        cld
        
        ; fread
        push dword [descriptor_fisier]
        push dword 1
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4 * 4
        citire_fisier:
            cmp eax, 0
            je stop_citire
            
            mov al, [buffer]
            
            ; stochez caracterul din al
            stosb
            
            ; update nr de caractere
            mov eax, [numar_caractere]
            inc eax
            mov [numar_caractere], eax
            
            ; update descriptor_sir
            mov [descriptor_sir], edi
            
            ; citire
            push dword [descriptor_fisier]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
        jmp citire_fisier
        
        stop_citire:
            ; fclose()
            push dword [descriptor_fisier]
            call [fclose]
            add esp, 4
            
        ; afisare pe ecran
        mov ecx, [numar_caractere]
        inc ecx
        mov esi, edi
        std
        afisare_invers:
            std
            mov [numar_caractere], ecx
            
            mov eax, 0
            lodsb       ; eax -> caracter
            push eax
            push format_char
            call [printf]
            add esp, 4 * 2
            
            mov ecx, [numar_caractere]
        loop afisare_invers
        
    
    finish:
        push dword 0    
        call [exit]       
