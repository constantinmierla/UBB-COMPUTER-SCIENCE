bits 32

global afisare_hexa

extern printf     
import printf msvcrt.dll    

segment data use32 class=data
    format_hexa db "%x ", 0

segment code use32 class=code    
    afisare_hexa:
        mov esi, [esp + 8]
        mov ecx, [esp + 4]
        
        .for_hexa:
            lodsd
            push ecx
            
            push dword eax
            push dword format_hexa
            call [printf]
            add esp, 4 * 2
            
            pop ecx
        loop .for_hexa
        
        ret