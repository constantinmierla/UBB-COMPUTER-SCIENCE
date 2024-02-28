bits 32 

global start        

extern exit, scanf, fopen, fclose, fread, printf               
import exit msvcrt.dll 
import scanf msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll  

; Sa se citeasca de la tastatura un nume de fisier si un numar. 
; Sa se citeasca din fisierul dat cuvintele separate prin spatii si sa se afiseze in consola cuvintele care sunt pe pozitiile multipli de numarul citit de la tastatura.


segment data use32 class=data
    nume_fisier times 100 db 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    format_string db '%s', 0
    format_int db '%d', 0
    format_string_afisare db '%s ', 0
    
    numar dd 0
    
    buffer times 1000 db 0
    cuvant times 100 db 0
    
    pozitie_curenta db 1
    
    nr_caractere_actual db 0

segment code use32 class=code
    start:
        ; citire nume de fisier de la tastatura
        push dword nume_fisier
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        ; citire numar de la tastatura
        push dword numar
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        ; fopen()
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        ; fread()
        push dword [descriptor_fisier]
        push dword 1000
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4 * 4
        
        ; parcurg bufferul
        mov esi, buffer
        mov edi, cuvant
        cld 
        while_caractere:
            lodsb   ; al = caracter din sir
            
            cmp al, 0
            je stop_caractere
            
            cmp al, ' '
            je spatiu
            
            stosb   ; stochez caracterul pentru a retine cuvantul 
                    ; pe care il parcurg momentan
            mov al, [nr_caractere_actual]
            add al, 1
            mov [nr_caractere_actual], al
            jmp continua
            
            spatiu:
                mov dx, 0
                mov ax, 0
                mov al, [pozitie_curenta]
                mov ebx, [numar]
                
                ; presupunem ca numarul citit de la tastatura incape pe 2 Bytes
                div bx    ; dx:ax / bx -> dx rest
                
                cmp dx, 0
                je multiplu
                
                ; nu e multiplu
                jmp continua_spatiu
                
                multiplu:
                    ; daca e multiplu, afisez cuvantul pe ecran
                    push dword cuvant
                    push dword format_string_afisare
                    call [printf]
                    add esp, 4 * 2
                 
                ; trebuie sa resetez cuvant si pozitia curenta
                continua_spatiu:
                    mov al, [pozitie_curenta]
                    add al, 1
                    mov [pozitie_curenta], al
                    
                    mov ecx, 0
                    mov cl, [nr_caractere_actual]
                    mov edi, cuvant
                    cld
                    curatare_cuvant:
                        mov al, 0
                        stosb
                    loop curatare_cuvant
                    mov edi, cuvant
                    
                    mov al, 0
                    mov [nr_caractere_actual], al
                
            continua:
                nop
        jmp while_caractere    
            
        stop_caractere:
            nop
            
        ; verific ultimul cuvant
        mov dx, 0
        mov ax, 0
        mov al, [pozitie_curenta]
        mov ebx, [numar]
                
        ; presupunem ca numarul citit de la tastatura incape pe 2 Bytes
        div bx
        
        cmp dx, 0
        je e_bun
        
        ; nu e bun, merg la inchidere
        jmp close
        
        e_bun:
            push dword cuvant
            push dword format_string_afisare
            call [printf]
            add esp, 4 * 2
            
        close:
            ; fclose()
            push dword [descriptor_fisier]
            call [fclose]
            add esp, 4 * 1
    
    finish:
        push dword 0    
        call [exit]       
