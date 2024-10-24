bits 32

global start

extern exit, scanf, printf, fopen, fread,fclose

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    fisier db 0
    format_string db "%s", 0
    
    litera db 0
    format_char db "%c", 0
    
    numar db 0
    format_int db "%d", 0
    mod_acces db "r", 0
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
        
        push dword litera
        push dword format_char
        call [scanf]
        add esp, 4 * 2
        
        push dword numar
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        ; fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp, 4 * 2
        
        ; verific daca fisierul a fost creat cu succes
        cmp eax, 0
        je final
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
            jne while_read_from_file

            push ebx
            mov ebx, [numar_aparitii]
            add ebx, 1
            mov [numar_aparitii], ebx
            pop ebx
            
            jmp while_read_from_file

        end_while_read_char:
            
        ;verific daca nr de aparitii din fisier este egal sau nu cu nr citit de la tastatură
        mov eax, [numar]
        mov ebx, [numar_aparitii]
        
        cmp eax, ebx
        je sunt_egale
        
        nu_sunt_egale:
            push dword [numar]
            push dword [litera]
            push dword mesaj_false
            call [printf]
            add esp, 4 * 3
            jmp final 
            
        sunt_egale:
            push dword [numar]
            push dword [litera]
            push dword mesaj_true
            call [printf]
            add esp, 4 * 3
            
        
    final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       