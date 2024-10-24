bits 32

global afisare_zecimal

extern printf
import printf msvcrt.dll

segment data use32 class=data
    mesaj_zecimal db "Baza 10: ", 0
    format_zecimal db "%d ", 0

segment code use32 class=code   
    afisare_zecimal:
        push dword mesaj_zecimal
        call [printf]
        add esp, 4 * 1
        
        mov esi, [esp + 8]
        mov ecx, [esp + 4]
        cld
        
        afisare_numere_zecimal:
            push ecx
            lodsb
            
            mov ebx, 0
            mov bl, al
            
            push dword ebx
            push dword format_zecimal
            call [printf]
            add esp, 4 * 2
            
            pop ecx
        loop afisare_numere_zecimal
        
        ret