bits 32 

global start        

extern exit, scanf, printf              
import exit msvcrt.dll 
import scanf msvcrt.dll 
import printf msvcrt.dll  

; Se citeste o propozitie de la tastatura. 
; Sa se numere literele din fiecare cuvant si sa se afiseze aceste numere pe ecran.

segment data use32 class=data
    litera dd 0
    format_char db '%c', 0
    sir_de_caractere times 100 dd 0
    
    nr_caractere dd 0
    nr_cuvinte dd 0
    nr_litere_cuv_curent dd 0
    numere times 100 db 0
    
    format_int db '%d ', 0
    
    mesaj db "am ajuns aici", 0

segment code use32 class=code
    start:
        mov edi, sir_de_caractere
        cld
    
        push dword litera
        push dword format_char
        call [scanf]
        add esp, 4 * 2
        
        citire_tastatura:
            mov eax, [litera]
            cmp eax, '.'
            je cand_ii_gata_i_gata
            
            stosd
            
            mov eax, [nr_caractere]
            add eax, 1
            mov [nr_caractere], eax
            
            push dword litera
            push dword format_char
            call [scanf]
            add esp, 4 * 2
        jmp citire_tastatura  
            
        cand_ii_gata_i_gata:
            nop
        
        mov edi, numere
        mov esi, sir_de_caractere
        cld
        mov ecx, [nr_caractere]
        parsare_cuvinte:
            mov [nr_caractere], ecx
            lodsd    ; eax = caracter
            cmp eax, ' '
            je spatiu
            
            mov eax, [nr_litere_cuv_curent]
            add eax, 1
            mov [nr_litere_cuv_curent], eax
            jmp continua_parsare
            
            spatiu:
                ; prelucrare informatii
                mov eax, [nr_litere_cuv_curent]
                stosd
                
                mov eax, 0
                mov [nr_litere_cuv_curent], eax
                
                mov eax, [nr_cuvinte]
                add eax, 1
                mov [nr_cuvinte], eax
            
            continua_parsare:
                nop
            
            mov ecx, [nr_caractere]
        loop parsare_cuvinte
        
        ; pun nr de litere al ultimului cuvant in sirul de numere
        mov eax, [nr_litere_cuv_curent]
        stosd
        ; actualizez nr de cuvinte
        mov eax, [nr_cuvinte]
        add eax, 1
        mov [nr_cuvinte], eax
        
        mov esi, numere
        cld
        mov ecx, [nr_cuvinte]
        afisare:
            mov [nr_cuvinte], ecx
            
            lodsd   ; eax = nr litere
            push eax
            push dword format_int
            call [printf]
            add esp, 4 * 2
            
            mov ecx, [nr_cuvinte]
        loop afisare
            
    
    finish:
        push dword 0    
        call [exit]       
