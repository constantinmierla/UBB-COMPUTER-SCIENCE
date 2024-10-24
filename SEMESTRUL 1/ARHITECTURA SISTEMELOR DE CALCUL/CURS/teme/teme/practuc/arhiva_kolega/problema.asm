bits 32 

global start        

extern exit, scanf, fopen, fclose, fscanf, fprintf               
import exit msvcrt.dll 
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll   
import fscanf msvcrt.dll
import fprintf msvcrt.dll

; Să citesc un nume de fisier si un numar de la tastatura. În fisierul respectiv erau cuvinte separate de spatii și linii și trebuia sa scrii în alt fișier doar acele cuvinte care au numărul de consoane egal cu numărul citit de la tastatură.

segment data use32 class=data
    nume_fisier_input times 100 db 0
    nume_fisier_output db 'output.txt', 0
    mod_acces db 'a+', 0
    descriptor_input dd -1
    descriptor_output dd -1
    
    numar_citit dd 0
    
    format_str db '%s', 0
    format_str_fisier db '%s ', 0
    format_int db '%d', 0
    
    string_fisier times 100 db 0
    numar_consoane dd 0

segment code use32 class=code
    start:
        ; scanf
        push dword nume_fisier_input
        push dword format_str
        call [scanf]
        add esp, 4 * 2
        
        push dword numar_citit
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        ; fopen()
        push dword mod_acces
        push dword nume_fisier_input
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_input], eax
        
        push dword mod_acces
        push dword nume_fisier_output
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_output], eax
        
        ; citesc din fisierul input
        while_citire:
            ; fscanf()
            push dword string_fisier
            push dword format_str
            push dword [descriptor_input]
            call [fscanf]
            add esp, 4 * 3
            
            ; verific daca am ajuns la sfarsitul fisierului
            cmp eax, -1
            je stop_citire
            
            ; parcurg sirul string
            mov esi, string_fisier
            cld
            while_caractere:
                lodsb     ; al = caracterul string_fisier[i]
                
                cmp al, 0
                je stop_caractere
                
                ; verific daca e consoana
                cmp al, 'a'
                je vocala
                cmp al, 'e'
                je vocala
                cmp al, 'i'
                je vocala
                cmp al, 'o'
                je vocala
                cmp al, 'u'
                je vocala
                
                ; daca am ajuns aici, inseamna ca e consoana
                ; actualizez numarul de vocale
                mov eax, [numar_consoane]
                inc eax
                mov [numar_consoane], eax
                
                vocala:
                    nop
            jmp while_caractere
                
            stop_caractere:
                ; verific daca numarul de consoane este egal cu nr citit de la tastatura
                mov eax, [numar_consoane]
                mov ebx, [numar_citit]
                cmp eax, ebx
                je sunt_egale
                
                ; nu sunt egale, nu trebuie sa afisez, dar actualizez numarul de consoane la 0
                jmp actualizare
                
                sunt_egale:
                    ; afisez cuvantul in fisier
                    push dword string_fisier
                    push dword format_str_fisier
                    push dword [descriptor_output]
                    call [fprintf]
                    add esp, 4 * 3
                
                actualizare:
                    ; readuc la 0 nr de consoane
                    mov eax, 0
                    mov [numar_consoane], eax
                    
                    ; readuc la 0 sirul de stringuri
                    mov edi, string_fisier
                    cld
                    mov ecx, 100
                    act_string:
                        mov al, 0
                        stosb
                    loop act_string
        jmp while_citire
            
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
