bits 32 

global start        

extern exit, fopen, fclose, fread, printf               
import exit msvcrt.dll   
import fopen msvcrt.dll 
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; Se citesc din fisierul numere.txt mai multe numere (pare si impare). 
; Sa se creeze 2 siruri rezultat N si P astfel: N - doar numere impare si P - doar numere pare. Afisati cele 2 siruri rezultate pe ecran.

segment data use32 class=data
    nume_fisier db 'numere.txt', 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    ten dd 10
    buffer dd 0
    
    mesaj_pare db 13, 10, 'Numerele pare: ', 0
    sir_nr_pare times 100 dd 0
    descriptor_pare dd -1
    nr_pare dd 0
    
    mesaj_impare db 13, 10, 'Numerele impare: ', 0
    sir_nr_impare times 100 dd 0
    descriptor_impare dd -1
    nr_impare dd 0
    
    format_int db "%d ", 0
    
segment code use32 class=code
    start:
        ; fopen(nume, mod)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        mov eax, sir_nr_impare
        mov [descriptor_impare], eax
        mov eax, sir_nr_pare
        mov [descriptor_pare], eax
        
        citire_fisier:
            ; fread(buffer, size, count, descr)
            push dword [descriptor_fisier]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 0
            je end_citire_fisier
            
            mov eax, [buffer]
            
            cmp eax, ' '
            je citire_fisier
            
            cmp eax, '0'
            jb end_citire_fisier
            cmp eax, '9' 
            ja end_citire_fisier
            
            sub eax, '0'
            
            while_digit:
                pushad
                ; fread(buffer, size, count, descr)
                push dword [descriptor_fisier]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4
                
                cmp eax, 0
                jne more_char
                
                popad
                jmp end_while_digit
                
                more_char:
                    nop
                popad

                ; verificam daca caracterul citit e o cifra valida
                mov ebx, [buffer]
                cmp ebx, '0'
                jb end_while_digit
                cmp ebx, '9'
                ja end_while_digit

                ; daca caracterul e cifra, convertim din char in int
                sub ebx, 48

                ; update numar: eax = eax * 10 + ebx 
                mul dword [ten] ; edx:eax = eax * 10, dar tinem in evidenta doar eax
                                ; intrucat presupunem ca rezulttul incape intr un dword
                add eax, ebx

                ; citim din nou un caracter
                jmp while_digit
                
            end_while_digit:
                ; acum avem un numar in eax
                ; eax -> dx:ax
                mov bx, ax
                shr eax, 16
                mov dx, ax
                mov ax, bx
                
                mov bx, 2
                div bx
                
                cmp dx, 1
                je impar
                
                ; par
                mov edi, [descriptor_pare]
                cld 
                stosd
                mov [descriptor_pare], edi
                
                mov eax, [nr_pare]
                add eax, 1
                mov [nr_pare], eax
                jmp citire_fisier
                
                impar:
                    mov edi, [descriptor_impare]
                    cld 
                    stosd
                    mov [descriptor_impare], edi
                
                    mov eax, [nr_impare]
                    add eax, 1
                    mov [nr_impare], eax
        jmp citire_fisier
            
        end_citire_fisier:
            nop
        
        ; fclose(descr)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        ; afisari
        push dword mesaj_pare
        call [printf]
        add esp, 4 
        
        mov esi, sir_nr_pare
        mov ecx, [nr_pare]
        cld
        afisare_pare:
            mov [nr_pare], ecx
            
            lodsd
            push eax
            push dword format_int
            call [printf]
            add esp, 4 * 2
            
            mov ecx, [nr_pare]
        loop afisare_pare
        
        ; impare
        push dword mesaj_impare
        call [printf]
        add esp, 4 
        
        mov esi, sir_nr_impare
        mov ecx, [nr_impare]
        cld
        afisare_impare:
            mov [nr_impare], ecx
            
            lodsd
            push eax
            push dword format_int
            call [printf]
            add esp, 4 * 2
            
            mov ecx, [nr_impare]
        loop afisare_impare
    
    finish:
        push dword 0    
        call [exit]       
