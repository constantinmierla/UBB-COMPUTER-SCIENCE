bits 32 

global start        

extern exit, scanf, printf               
import exit msvcrt.dll  
import scanf msvcrt.dll
import printf msvcrt.dll  

; Se citeste de la tastatura un cuvant si un numar. 
; Daca numarul este par se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului 20. 
; Daca numarul este impar se cere criptarea cuvantului prin adaugarea dupa fiecare vocala a gruparii "p"+vocala.
; Se cere afisarea cuvantului criptat.

segment data use32 class=data
    cuvant_citit times 100 db 0
    cuvant_criptat times 201 db 0
    
    format_string db '%s', 0
    format_int db '%d', 0
    
    numar_citit dd 0

segment code use32 class=code
    start:
        push dword cuvant_citit
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        push dword numar_citit
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        ; verific paritatea numarului citi
        mov eax, [numar_citit]
        mov bx, ax
        shr eax, 16
        mov dx, ax
        mov ax, bx    ; dx:ax = eax
        
        mov bx, 2
        div bx
        
        cmp dx, 1
        je impar
        
        ; par
        mov esi, cuvant_citit
        mov edi, cuvant_criptat
        cld
        lodsb   ; al = caracter
        while_caracter:
            cmp al, 0
            je afisare_cuv_criptat
            
            add al, 20
            stosb
            lodsb
        jmp while_caracter
        
        impar:
            mov esi, cuvant_citit
            mov edi, cuvant_criptat
            cld
        
            lodsb   ; al = caracter
            while_caractere_2:
                cmp al, 0
                je afisare_cuv_criptat
                
                cmp al, 'a'
                je criptare_nebuna
                cmp al, 'e'
                je criptare_nebuna
                cmp al, 'i'
                je criptare_nebuna
                cmp al, 'o'
                je criptare_nebuna
                cmp al, 'u'
                je criptare_nebuna
                
                ; consoana, o stochez
                stosb
                jmp continua
                
                criptare_nebuna:
                    ; stochez intai vocala
                    mov bl, al  ; fac copie la vocala
                    stosb
                    
                    ; stochez 'p'
                    mov al, 'p'
                    stosb
                    
                    ; stochez iar vocala
                    mov al, bl
                    stosb
                
                continua:
                    lodsb
            jmp while_caractere_2
            
        afisare_cuv_criptat:
            push dword cuvant_criptat
            push dword format_string
            call [printf]
            add esp, 4 * 2
    
    finish:
        push dword 0    
        call [exit]       
