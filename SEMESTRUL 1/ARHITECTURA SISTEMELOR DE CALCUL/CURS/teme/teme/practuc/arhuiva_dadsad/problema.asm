bits 32

global start

extern exit, fopen, fscanf, printf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    nume_fisier db "numere.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    n dd 0
    format db "%d", 0
    format_afisare db '%d ', 0
    mesaj db "Suma numerelor este: %d", 0
    
segment code use32 class=code
start:
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 2*4
    
    cmp eax, 0
    je eroare
    mov [descriptor_fisier], eax
    
    mov ebx, 0
    
    citire:
        push dword n
        push dword format
        push dword [descriptor_fisier]
        call [fscanf]
        add esp, 4*3
        
        cmp eax, 0
        je afisare
        
        pushad
        push dword [n]
        push dword format_afisare
        call [printf]
        add esp, 4*2
        popad
        
        cmp eax, 0
        je afisare
        
        add ebx, [n]
    jmp citire
    
    afisare:
        push dword ebx
        push dword mesaj
        call [printf]
        add esp, 4*2
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4*1
    eroare:
push dword 0
call [exit]