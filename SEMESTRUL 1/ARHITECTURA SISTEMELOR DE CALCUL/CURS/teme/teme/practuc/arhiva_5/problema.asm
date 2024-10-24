bits 32 

global start        

extern exit, scanf, printf               
import exit msvcrt.dll   
import scanf msvcrt.dll 
import printf msvcrt.dll

segment data use32 class=data
    sir_citit times 100 db 0
    format_string db '%s', 0
    
    sir_litere_mici times 100 db 0
    descriptor_sir_mici dd -1
    nr_litere_mici dd 0
    
    sir_litere_mari times 100 db 0
    descriptor_sir_mari dd -1
    nr_litere_mari dd 0
    
    format_string_new_line db '%s', 13, 10

segment code use32 class=code
    start:
        ; citire sir
        push dword sir_citit
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        ; pregatire parcurgere
        mov eax, sir_litere_mari
        mov [descriptor_sir_mari], eax
        
        mov eax, sir_litere_mici
        mov [descriptor_sir_mici], eax
        
        mov esi, sir_citit
        cld 
        
        ; parcurgere sir
        parsare:
            lodsb     ; al = caracterul s[i]
            
            cmp al, 0
            je sfarsit_citire
            
            ; verific daca e litera mica
            cmp al, 'a'
            jl posibil_lit_mare
            cmp al, 'z'
            jg nu_e_litera
            
            ; aici e litera mica
            mov edi, [descriptor_sir_mici]
            stosb
            mov [descriptor_sir_mici], edi
            jmp continua
            
            posibil_lit_mare:
                cmp al, 'A'
                jl nu_e_litera
                cmp al, 'Z'
                ja nu_e_litera
                
                ; litera mare
                mov edi, [descriptor_sir_mari]
                stosb
                mov [descriptor_sir_mari], edi
                jmp continua
            
            nu_e_litera:
                nop
                
            continua:
                nop
        jmp parsare
            
        sfarsit_citire:
            nop
            
        ; afisez sirurile
        push dword sir_litere_mici
        push dword format_string_new_line
        call [printf]
        add esp, 4 * 2
        
        push dword sir_litere_mari
        call [printf]
        add esp, 4
    
    finish:
        push dword 0    
        call [exit]       
