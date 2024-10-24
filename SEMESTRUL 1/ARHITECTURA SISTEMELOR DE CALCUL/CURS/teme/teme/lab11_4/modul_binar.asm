bits 32

global afisare_binar

extern printf  
import printf msvcrt.dll  

segment data use32 class=data
    format_binar db "%d", 0
    space db " ", 0

segment code use32 class=code
    afisare_bit:
        mov ecx, 32
        mov eax, [esp + 4]
        
        .loop_bit:
            shl eax, 1
            
            mov ebx, 0
            adc ebx, 0
                
            pushad
                
            push dword ebx
            push dword format_binar
            call [printf]
            add esp, 4 * 2
                
            popad
        loop .loop_bit
        
        ret
        
    afisare_binar:
        mov ecx, [esp + 4]
        mov esi, [esp + 8]
        
        .for_binar:
            lodsd
            pushad
            
            ; iau fiecare bit si il afisez, de la stanga la dreapta
            push dword eax
            call afisare_bit
            add esp, 4 * 1
            
            push dword space
            call [printf]
            add esp, 4 * 1
            
            popad
         loop .for_binar
         
         ret