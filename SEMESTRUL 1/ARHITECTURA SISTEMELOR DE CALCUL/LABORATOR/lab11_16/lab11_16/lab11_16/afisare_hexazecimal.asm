bits 32

global afisare_hexazecimal

extern printf
import printf msvcrt.dll

segment data use32 class=data
    mesaj_hexa db 10, 13, "Baza 16: ", 0
    format_hexa db "%x ", 0

segment code use32 class=code   
    afisare_hexazecimal:
        push dword mesaj_hexa
        call [printf]
        add esp, 4 * 1
        
        mov esi, [esp + 8]
        mov ecx, [esp + 4]
        cld
        
        afisare_numere_hexa:
            push ecx
            lodsb
            
            mov ebx, 0
            mov bl, al
            
            push dword ebx
            push dword format_hexa
            call [printf]
            add esp, 4 * 2
            
            pop ecx
        loop afisare_numere_hexa
        
        ret