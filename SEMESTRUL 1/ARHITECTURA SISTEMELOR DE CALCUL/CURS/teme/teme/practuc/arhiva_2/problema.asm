bits 32 

global start        

extern exit, scanf, fopen, fprintf, fclose, printf                
import exit msvcrt.dll 
import scanf msvcrt.dll 
import fopen msvcrt.dll
import fprintf msvcrt.dll  
import fclose msvcrt.dll
import printf msvcrt.dll

; Se citește de la tastatură un număr N și apoi N numere.
; Să se calculeze suma numerelor pare introduse, să se calculeze suma numerelor impare introduse, apoi diferența dintre cele două sume.
; Să se afișeze în fișierul output.txt cele 3 rezultate, în baza 16, pe linii separate


segment data use32 class=data
    nr_elemente dd 0
    nr_elemente_aux dd 0
    format_int db "%d", 0
    
    numere times 100 dd 0
    numar dd 0
    
    suma_pare dd 0
    suma_impare dd 0
    diferenta_sume dd 0
    
    nume_fisier db "output.txt", 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    format_hexa db "%x", 13, 10
    
    verific dd 0

segment code use32 class=code
    start:
        push dword nr_elemente
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, [nr_elemente]
        mov [nr_elemente_aux], ecx
        cmp ecx, 0
        je finish
        
        mov edi, numere
        cld
        
        citeste_numere:
            mov [nr_elemente], ecx
            
            push dword numar
            push dword format_int
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [numar]
            stosd
            
            mov ecx, [nr_elemente]
        loop citeste_numere
        
        mov ecx, [nr_elemente_aux]
        mov esi, numere
        cld
        
        prelucrare_numere:
            mov [nr_elemente_aux], ecx
            
            lodsd
            mov [numar], eax
            mov edx, 0
            mov ebx, 2
            div ebx
            
            cmp edx, 1
            je impar
            
            ; par 
            mov eax, [numar]
            mov edx, [suma_pare]
            add edx, eax
            mov [suma_pare], edx
            jmp continua
            
            ; impare
            impar:
                mov eax, [numar]
                mov edx, [suma_impare]
                add edx, eax
                mov [suma_impare], edx
            
            continua:
                nop
                
            mov ecx, [nr_elemente_aux]
        loop prelucrare_numere
        
        mov eax, [suma_pare]
        mov ebx, [suma_impare]
        
        cmp eax, ebx
        ja mai_mare_pare
        
        sub ebx, eax
        mov [diferenta_sume], ebx
        jmp fisiere
        
        mai_mare_pare:
            sub eax, ebx
            mov [diferenta_sume], eax
        
        fisiere:
            ; fopen(fisier, mod)
            push dword mod_acces
            push dword nume_fisier
            call [fopen]
            add esp, 4 * 2
            
            cmp eax, 0
            je finish
            mov [descriptor_fisier], eax
            
            ; fprintf(descriptor_fisier, format, numar)
            push dword [suma_pare]
            push dword format_hexa
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4 * 3
            
            push dword [suma_impare]
            push dword format_hexa
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4 * 3
            
            push dword [diferenta_sume]
            push dword format_hexa
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4 * 3
            
            ; fclose()
            push dword [descriptor_fisier]
            call [fclose]
            add esp, 4 * 1
    
    finish:
        push dword 0    
        call [exit]       
