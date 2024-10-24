bits 32 

global start        

extern exit            
extern scanf, printf
extern fopen, fread, fprintf, fclose
  
import exit msvcrt.dll 

import scanf msvcrt.dll
import printf msvcrt.dll

import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    string times 100 db 0
    format_string db "%s", 0
    
    number dd 0
    format_number db "%d", 0
    
    mod_acces db 'a+', 0
    descriptor_fisier_citire dd -1
    buffer dd 0
    
    fisier_afisare db "output.txt", 0
    descriptor_fisier_afisare dd -1
    
    cuvant times 200 db 0

segment code use32 class=code
    start:
        push dword string
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        push dword number
        push dword format_number
        call [scanf]
        add esp, 4 * 2
        
        ; deschid fisierul din care citesc
        push dword mod_acces
        push dword string
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je stop
        mov [descriptor_fisier_citire], eax
        
        ; deschid fisierul in care salvez
        push dword mod_acces
        push dword fisier_afisare
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je stop
        mov [descriptor_fisier_afisare], eax
        
        mov ebx, 0
        mov edi, cuvant
        cld
        
        while_read_from_file:
            ; fread(buffer, size, count, descriptor_fisier)
            push dword [descriptor_fisier_citire]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 0
            je end_while_read
            
            mov eax, [buffer]
            
            cmp eax, 'a'
            je not_consoana
            cmp eax, 'e'
            je not_consoana
            cmp eax, 'i'
            je not_consoana
            cmp eax, 'o'
            je not_consoana
            cmp eax, 'u'
            je not_consoana
            
            cmp eax, ' '
            je space
            
            ; daca s-a ajuns aici, inseamna ca am dat de o consoana
            add ebx, 1
            jmp not_consoana
                
            space:
                ; verific criteriul si execut operatiile necesare
                mov eax, [number]
                cmp eax, ebx
                jne not_consoana
                
                ; pun cuvantul citit in fisierul de iesire
                mov edi, cuvant
                mov esi, cuvant
                cld
                
                lodsd
                while_cuvant:
                    cmp eax, 0
                    je sfarsit_cuvant
                    
                    push dword eax
                    push dword "%c"
                    push dword [descriptor_fisier_afisare]
                    call [fprintf]
                    add esp, 4 * 3
                    
                    mov eax, 0
                    stosd
                    
                    jmp while_cuvant
                    
                sfarsit_cuvant:
                    ; mai pun in fisier un spatiu
                    push dword ' '
                    push dword "%c"
                    push dword [descriptor_fisier_afisare]
                    call [fprintf]
                    add esp, 4 * 3
                    
                    mov edi, cuvant
                
            not_consoana:
                ; adaug litera in cuvant
                stosd
            
            jmp while_read_from_file
        
        end_while_read:
            nop
        
        ; inchid fisierele deschise
        push dword [descriptor_fisier_citire]
        call [fclose]
        add esp, 4
        
        push dword [descriptor_fisier_afisare]
        call [fclose]
        add esp, 4
    stop:
        push dword 0  
        call [exit]       
