bits 32

global start

extern exit, printf              
import exit msvcrt.dll
import printf msvcrt.dll  

extern afisare_hexa
extern afisare_binar 

segment data use32 class=data
    sir_numere dd 256, 32, 123, 127, 92, 123, 421, 42, 12, 0, 12431
    nr dd ($-sir_numere)/4
    
    mesaj_hexa db "baza 16: ", 0
    mesaj_binar db "baza 2: ", 0
    format_hexa db "%x ", 0
    format_binar db "%d", 0
    space db " ", 0
    new_line db "", 10, 13, 0

segment code use32 class=code
    start:
        mov esi, sir_numere
        mov ecx, [nr]
        jecxz final
        
        push ecx 
        
        ; afisez mesaj hexa
        push dword mesaj_hexa
        call [printf]
        add esp, 4 * 1
        
        pop ecx
        
        ; afisez numerele in baza 16
        push esi
        push ecx
        call afisare_hexa
        
        ; new line
        push dword new_line
        call [printf]
        add esp, 4 * 1
        
        ; afisez mesaj binar
        push dword mesaj_binar
        call [printf]
        add esp, 4 * 1
        
        ; afisez numerele in baza 2
        push sir_numere
        push dword [nr]
        call afisare_binar
        
    final:
        ; exit(0)
        push dword 0      
        call [exit]       