; Se citește de la tastatură un nume de fișier, un caracter c și un număr n.
; Se determină dacă numărul de apariții ale caracterului c în textul fișierului este egal cu numărul n,
; afișându-se la consolă un mesaj corespunzător (formatat ca în exemplu).

bits 32

global start

extern exit, scanf, printf, fopen, fread
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll

segment data use32 class=data
    fisier db 0
    nume_fisier db 0
    format_string db "%s", 0
    
    litera db 0
    format_char db "%c", 0
    
    numar dd 0
    format_int db "%d", 0
    
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    buffer dd 0
    numar_aparitii db 0
    
    mesaj_false db "Numarul de aparitii al caracterului %c nu este egal cu numarul %d citit.", 0
    mesaj_true db "Numarul de aparitii al caracterului %c este egal cu numarul %d citit.", 0
    
segment code use32 class=code
    start:
        push dword fisier
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        mov esi, fisier
        mov edi, nume_fisier
        cld
        
        while_parsare:
            lodsb   ; al = caracter
            
            cmp al, ' ' 
            je terminare_fisier
            stosb
            jmp while_parsare
        
        terminare_fisier:
        
        lodsb ; al = litera citita
        mov [litera], al
        
        lodsb ; al = ' '
        
        ; citesc nr
        while_parsare_2:
            lodsb
            cmp al, '.'
            je end_numar
            
            sub al, '0'
            
            push ebx
            mov ebx, 0
            mov bl, al
            mov eax, [numar]
            mov edx, 10
            mul edx
            add al, bl
            adc ah, 0    ; eax e numarul citit, presupunem ca incape
            mov [numar], eax
            pop ebx
            jmp while_parsare_2
        end_numar:
        
        
        ; fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp, 4 * 2
        
        ; verific daca fisierul a fost creat cu succes
        cmp eax, 0
        je stop
        mov [descriptor_fisier], eax
        
        while_read_from_file:
            push dword [descriptor_fisier]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            ; verificam daca am citit ceva
            cmp eax, 0
            je end_while_read_char
            
            cmp eax, [litera]
            jne nu_e_acea_litera
            
            ; litera citita din fisier = litera citita de la tastatură
            ; incrementez nr de aparitii
            push ebx
            mov ebx, [numar_aparitii]
            add ebx, 1
            mov [numar_aparitii], ebx
            pop ebx
            
            nu_e_acea_litera:
                nop
            jmp while_read_from_file
            
        end_while_read_char:
            nop
            
        ; verific daca nr de aparitii din fisier este egal sau nu cu nr citit de la tastatură
        mov eax, [numar]
        mov ebx, [numar_aparitii]
        
        push dword numar
        push dword format_int
        call [printf]
        add esp, 4 * 2
        
        cmp eax, ebx
        je sunt_egale
        
        nu_sunt_egale:
            push dword numar
            push dword litera
            push dword mesaj_false
            call [printf]
            add esp, 4 * 3
            jmp stop
            
        sunt_egale:
            push dword numar
            push dword litera
            push dword mesaj_true
            call [printf]
            add esp, 4 * 3
        
    stop:
        push dword 0
        call [exit]