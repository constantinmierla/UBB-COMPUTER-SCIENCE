bits 32 

global start        

extern exit, scanf, fopen, fclose, fscanf, printf               
import exit msvcrt.dll 
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 
import fscanf msvcrt.dll 
import printf msvcrt.dll 

; citeste de la tastatura un nr din fisier si un numar
; in fisier numere
; afisez cate numere sunt mai mici sau egale decat numarul citit de la tastatura

segment data use32 class=data
    nume_fisier times 100 db 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    numar_count db 0
    numar_citit dd 0
    numar_aux dd 0
    
    format_int db '%d', 0
    format_string db '%s', 0
    
    mesaj_afisare db '%d numere sunt mai mici sau egale decat numarul %d citit de la tastatura', 0

segment code use32 class=code
    start:
        push dword nume_fisier
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        push dword numar_citit
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
        
        citire:
            ;fscanf()
            push dword numar_aux
            push dword format_int
            push dword [descriptor_fisier]
            call [fscanf]
            add esp, 4 * 3
            
            ; verific daca s a citit ceva
            cmp eax, -1   ; EOF: end of file
            je stop_citire
            
            mov eax, [numar_aux]
            mov ebx, [numar_citit]
            cmp eax, ebx
            jle mai_mic_sau_egal
            
            jmp continua
            
            mai_mic_sau_egal:
                ; updatez nr de numere
                mov al, [numar_count]
                inc al
                mov [numar_count], al
                
            continua:
                nop
        jmp citire
            
        stop_citire:
            nop
            
        ; afisez
        push dword [numar_citit]
        mov eax, 0
        mov al, [numar_count]
        push eax
        push mesaj_afisare
        call [printf]
        add esp, 4 * 2
        
        ; fclose()
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
    
    finish:
        push dword 0    
        call [exit]       
