bits 32 

global start        

extern exit, scanf, fopen, fread, fclose, printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; de la tastatura: nume de fisier si un nr
; in fisier: cuvinte separate prin '/'
; sa se afiseze cate cuvinte au nr de vocale egal cu nr citit de la tastatura

segment data use32 class=data
    nume_fisier times 100 db 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    format_string db '%s', 0
    format_int db '%d', 0
    format_char db '%c', 0
    
    mesaj_de_afisat db '%d cuvinte au %d vocale', 0
    
    numar_vocale dd 0
    numar_cuvinte dd 0
    numar_aux dd 0

    buffer db 0

segment code use32 class=code
    start:
        ; citire nume_fisier si numar_vocale
        push dword nume_fisier
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        push dword numar_vocale
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
        
        ; fread(b, count, size, desc)
        push dword [descriptor_fisier]
        push dword 1
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4 * 4
        while_citire_fisier:
            cmp eax, 0
            je stop_citire_fisier
            
            mov al, [buffer]
            cmp al, '/'
            je cuvant_terminat
            
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
            
            ; consoana
            jmp continuare
            
            vocala:
                ; incrementez numarul de vocale in cuvantul curent
                mov eax, [numar_aux]
                add eax, 1
                mov [numar_aux], eax
                jmp continuare
            
            cuvant_terminat:
                mov eax, [numar_aux]
                mov ebx, [numar_vocale]
                
                ; refac numar_aux = 0
                mov edx, 0
                mov [numar_aux], edx
                
                cmp eax, ebx
                je sunt_egale
                
                ; nu sunt egale
                jmp continuare
                
                sunt_egale:
                    mov eax, [numar_cuvinte]
                    add eax, 1
                    mov [numar_cuvinte], eax
                
            continuare:
                nop
            
            ; fread
            push dword [descriptor_fisier]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
        jmp while_citire_fisier
            
        stop_citire_fisier:
            nop
            
        ; tratez ultimul cuvant citit din fisier
        mov eax, [numar_aux]
        mov ebx, [numar_vocale]
        
        cmp eax, ebx
        je egale
        
        ; nu sunt egale
        jmp afisare
        
        egale:
            mov eax, [numar_cuvinte]
            add eax, 1
            mov [numar_cuvinte], eax
            
        ; afisare informatii
        afisare:
            push dword [numar_vocale]
            push dword [numar_cuvinte]
            push dword mesaj_de_afisat
            call [printf]
            add esp, 4 * 3
        
        ; fclose()
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4 * 1
    
    finish:
        push dword 0    
        call [exit]       
