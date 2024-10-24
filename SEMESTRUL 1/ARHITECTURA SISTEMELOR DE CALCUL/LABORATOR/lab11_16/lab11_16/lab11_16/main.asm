bits 32

global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

extern afisare_hexazecimal
extern afisare_zecimal
extern stocare_numere

segment data use32 class=data
    sir db '10110101', '10110001', '11100101', '10000110', '00110110'
    n equ ($-sir) / 8
    
    sir_numere times n db 0
    
    mesaj_zecimal db "Baza 10: ", 0
    format_zecimal db "%d ", 0
    
    mesaj_hexa db 10, 13, "Baza 16: ", 0
    format_hexa db "%x ", 0

segment code use32 class=code
    start:
        mov esi, sir
        mov edi, sir_numere
        mov ecx, n
        jecxz sfarsit
        
        ; apelez functia de transformare a numerelor din string in int
        ; si care stocheaza numerele transformate
        push edi
        push esi
        push ecx
        call stocare_numere
        add esp, 4 * 3
        
        ; apelez functia de afisare a numerelor in baza 10
        push sir_numere
        push n
        call afisare_zecimal
        add esp, 4 * 2
        
        ; apelez functia de afisare a numerelor in baza 16
        push sir_numere
        push n
        call afisare_hexazecimal
        add esp, 4 * 2
            
    sfarsit:
        push dword 0
        call [exit]