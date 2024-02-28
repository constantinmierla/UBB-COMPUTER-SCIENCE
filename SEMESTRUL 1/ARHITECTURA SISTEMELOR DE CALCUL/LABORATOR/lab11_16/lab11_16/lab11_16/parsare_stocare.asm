bits 32

global stocare_numere

extern printf
import printf msvcrt.dll

segment data use32 class=data

segment code use32 class=code   
    stocare_numere: 
        mov ecx, [esp + 4]
        mov esi, [esp + 8]
        mov edi, [esp + 12]
    
        cld
        
        cat_timp_numere:
            push ecx
            
            mov ecx, 8
            mov bl, 0
            
            parsare_numar:
                lodsb    ; al = 1 bit
                cmp al, '1'
                je .cifra
                
                cmp al, '0'
                je .cifra
                
                jmp terminare_parsare
                
                .cifra:
                    sub al, '0'   ; fac registrul al cifra
                                  ; ultima cifra = 1: al = 0000 0001b 
                                  ; ultima cifra = 0: al = 0000 0000b
                                  ; cand shiftez odata la stanga, iau practic valoarea bitului
                                  ; reprezentat de caracter
                    shl bl, 1     ; fac loc in bl
                    or bl, al     ; construiesc numarul in bl
            loop parsare_numar
            
            terminare_parsare:
                mov al, bl
                stosb             ; salvez numarul 
                
            pop ecx
        loop cat_timp_numere
        
        ret