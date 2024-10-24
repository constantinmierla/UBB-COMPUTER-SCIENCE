bits 32

global functie_afisare

extern printf
import printf msvcrt.dll

segment data use32 class=data
    format_nr db "%d ", 0

segment code use32 class=code
    functie_afisare:
        mov esi, [esp + 8]
        mov ecx, [esp + 4]
        cld
            
        .afisare_numere:
            lodsd    ; eax = numar
                
            pushad
                
            push dword eax
            push dword format_nr
            call [printf]
            add esp, 4 * 2
                
            popad
        loop .afisare_numere
        
        ret