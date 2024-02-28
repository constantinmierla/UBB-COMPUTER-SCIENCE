bits 32 

global start        

extern exit, fopen, fread, printf            
import exit msvcrt.dll   
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll 

segment data use32 class=data
    fisier db "input.txt", 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    buffer db 0
    
    suma db 0

segment code use32 class=code
    start:
        ; fopen(nume, mod)
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp, 4 * 2
        
        ; verific daca s a deschis corect
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        ; in ebx retin cifra curenta
        ; in edx construiesc numarul
        mov ebx, 0
        mov edx, 0
        while_parsare:
            pushad
            ; fscanf(variabila, size, count, descriptor)
            push dword [descriptor_fisier]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 0
            je end_citire
            
            popad
            
            mov ebx, [buffer]
            cmp ebx, ' '
            je space
            
            ; altfel e cifra
            push eax
            mov eax, edx
            
            sub ebx, '0'
            mov edx, 10
            mul edx
            add eax, ebx ; am construit numarul
            
            mov edx, eax
            pop eax
            
            jmp continua
            
            space:
                cmp edx, 8
                jae nu_e_bine
                
                ; e bine 
                mov ebx, [suma]
                add ebx, edx
                mov [suma], ebx
                
            nu_e_bine:
                mov edx, 0
            
            continua:
                nop
                
            jmp while_parsare
        
        end_citire:
            push dword [suma]
            push dword '%d'
            call [printf]
            add esp, 4 * 2
            
    
    finish:
        push dword 0    
        call [exit]       
