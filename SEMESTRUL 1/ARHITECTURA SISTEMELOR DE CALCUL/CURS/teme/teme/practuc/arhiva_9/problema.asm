bits 32 

global start        

extern exit, fopen, scanf, fprintf, fclose, fread               
import exit msvcrt.dll   
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

; De la tastatura se citeste un nume de fisier input. 
; Se creaza un alt fisier de output in care se pune continutul fisierului de input su toate caracterele mici schimbate cu codul lor ascii.

segment data use32 class=data
    nume_fisier_input times 100 db 0
    descriptor_input dd -1
    
    nume_fisier_out db "output.txt", 0
    descriptor_output dd -1
    
    format_string db '%s', 0
    mod_acces db 'a+', 0
    
    buffer db 0
    
    format_char db '%c', 0
    format_int db '%d', 0

segment code use32 class=code
    start:
        push dword nume_fisier_input
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        ; fopen
        push dword mod_acces
        push dword nume_fisier_input
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_input], eax
        
        push dword mod_acces
        push dword nume_fisier_out
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_output], eax
        
        ; fread
        push dword [descriptor_input]
        push dword 1
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4 * 4
        while_caractere_in_input:
            cmp eax, 0
            je stop_citire
            
            mov eax, 0
            mov al, [buffer]
            cmp eax, 0
            je in_output
            
            cmp eax, 'a'
            jb in_output
            cmp eax, 'z'
            ja in_output
            
            ; daca am aj aici, inseamna ca e litera si ii pun codul ascii
            ; fprintf
            push eax
            push dword format_int
            push dword [descriptor_output]
            call [fprintf]
            add esp, 4 * 3
            jmp citire
            
            in_output:
                ; pun caracterul asa cum e elk
                push eax
                push dword format_char
                push dword [descriptor_output]
                call [fprintf]
                add esp, 4 * 3
                
            citire:
                ; fread
                push dword [descriptor_input]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4
        jmp while_caractere_in_input
            
        stop_citire:
            nop
            
        ; fclose()
        push dword [descriptor_input]
        call [fclose]
        add esp, 4
        
        push dword [descriptor_output]
        call [fclose]
        add esp, 4
    
    finish:
        push dword 0    
        call [exit]       
