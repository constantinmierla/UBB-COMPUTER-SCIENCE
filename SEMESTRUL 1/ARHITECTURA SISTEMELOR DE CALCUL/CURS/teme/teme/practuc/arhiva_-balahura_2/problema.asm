bits 32 

global start        

extern exit, scanf, fopen, fclose, fread, printf               
import exit msvcrt.dll  
import scanf msvcrt.dll  
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; de la tastatura: nume de fisier si un nr
; in fisier: cuvinte separate prin '/'
; sa se afiseze cate cuvinte au nr de vocale egal cu nr citit de la tastatura

segment data use32 class=data
    nume_fisier times 100 db 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    numar dd 0
    
    format_str db '%s', 0
    format_int db '%d', 0
    
    numar_count dd 0
    numar_vocale dd 0
    buffer db 0
    
    mesaj_afisare db '%d cuvinte au %d vocale', 0

segment code use32 class=code
    start:
        ; scanf
        push dword nume_fisier
        push dword format_str
        call [scanf]
        add esp, 4 * 2
        
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
        push dword 1
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4 * 4
        while_citire:
            cmp eax, 0
            je stop_citire
            
            mov al, [buffer]
            
            cmp al, '/'
            je terminare_cuvant
            
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
            
            ; daca am ajuns aici inseamna ca e consoana, trec peste
            jmp continuare_citire
            
            vocala:
                ; actualizez numarul de vocale
                mov eax, [numar_vocale]
                inc eax
                mov [numar_vocale], eax
                jmp continuare_citire
            
            terminare_cuvant:
                ; verific numarul de vocale si actualizez datele
                mov eax, [numar_vocale]
                mov ebx, [numar]
                
                cmp eax, ebx
                je egale
                
                ; nu sunt egale, trebuie doar sa actualizez nr_vocale
                jmp actualizare
                
                egale:
                    ; actualizez numarul de cuvinte
                    mov eax, [numar_count]
                    inc eax
                    mov [numar_count], eax
                    
                actualizare:
                    mov eax, 0
                    mov [numar_vocale], eax
                
            continuare_citire:
                ; fread()
                push dword [descriptor_fisier]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4
        jmp while_citire
            
        stop_citire:
            nop
            
        ; verific nr de vocale al ultimului cuvant
        mov eax, [numar_vocale]
        mov ebx, [numar]
        
        cmp eax, ebx
        je sunt_egale
        
        ; nu sunt egale, afisez datele
        jmp afisare
        
        sunt_egale:
            mov eax, [numar_count]
            inc eax
            mov [numar_count], eax
        
        afisare:
            push dword [numar]
            push dword [numar_count]
            push dword mesaj_afisare
            call [printf]
            add esp, 4 * 3
        
        ; fclose()
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4 
    
    finish:
        push dword 0    
        call [exit]       
