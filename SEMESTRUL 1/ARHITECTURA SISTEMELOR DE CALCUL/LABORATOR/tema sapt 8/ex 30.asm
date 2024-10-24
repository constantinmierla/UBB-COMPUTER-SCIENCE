bits 32 
global start

extern exit
import exit msvcrt.dll

; 30.
; Se da un sir de cuvinte. Sa se construiasca doua siruri de octeti, s1 si s2, astfel: pentru fiecare cuvant,
; daca numarul de biti 1 din octetul high al cuvantului este mai mare decat numarul de biti 1 din octetul low, atunci s1 va contine octetul high, iar ; s2 octetul low al cuvantului
; daca numarul de biti 1 din cei doi octeti ai cuvantului sunt egali, atunci s1 va contine numarul de biti 1 din octet, iar s2 valoarea 0
; altfel, s1 va contine octetul low, iar s2 octetul high al cuvantului.


; segmentul de date in care se vor defini variabilele 
segment data use32 class=data
    s dw 82A5h, 4344h, 0F6F6h, 0A102h
    len equ ($-s) / 2
    s1 times len db 0
    s2 times len db 0
    var dw 0
    ;s1 : A5h, 43h, 06h, A1h
    ;s2 : 82h, 44h, 00h, 02h
segment code use32 class=code
    start:
        mov ecx, len
        ; jecxz sfarsit
        
        mov esi, s
        
        ; edi -> s1
        mov edi, s1
        ; edx -> s2
        mov edx, s2
        
        ; setez DF pe 0
        cld
        
        repeta:
            lodsw ; ax = s[i]
            mov [var], ax  ; var = ax
            
            push ecx ; pun valoarea lui ecx in stiva pentru a face un nou loop
            
            ; in BH retin nr de unari din AH
            mov bh, 0
            mov ecx, 8
            repeta_2:
                shr ah, 1 ; cf = ultimul bit al lui ah (inainte de shiftare)
                
                jnb continue ; daca bitul = cf = 0, merg la eticheta continue
                inc bh ; daca bitul = cf = 1, incrementez bh
                
                continue:
            loop repeta_2
            
            ; in BL retin nr de unari din AL, acelasi principiu ca cel de mai sus
            mov bl, 0
            mov ecx, 8
            repeta_3:
                shr al, 1                        
                
                jnb continue_2
                inc bl
                
                continue_2:
            loop repeta_3
            
            cmp bl, bh ; compar bh cu bl
            jbe bl_mai_mic_sau_egal_decat_bh ; jump bl <= bh
            
            ; aici bl este mai mai mare decat bh   (bl > bh)
            ; s1 = al
            ; s2 = ah
            mov ax, [var]
            stosb ; s1[i] = al
            
            ; fac swap intre adresele sirurilor ot a accesa s2
            mov eax, edi  ; eax -> s1
            mov edi, edx  ; edi -> s2
            mov edx, eax  ; edx -> s1
            
            mov ax, [var]
            mov al, ah
            stosb ; s2[i] = ah
            
            ; fac iar swap intre adresele sirurilor pentru a reveni la conventia initiala
            mov eax, edi  ; eax -> s2
            mov edi, edx  ; edi -> s1
            mov edx, eax  ; edx -> s2
            
            jmp continue_next
            
            bl_mai_mic_sau_egal_decat_bh:
                cmp bl, bh        ; testez daca sunt egale
                je bl_egal_cu_bh  ; jump bl = bh
                
                ; aici bl este mai mic decat bh    (bl < bh)
                ; s1 = ah
                ; s2 = al
                mov ax, [var] ; ax = var
                mov al, ah    ; al = ah
                stosb         ; s1[i] = ah
                
                ; swap intre adresele sirurilor pt a accesa s2
                mov eax, edi ; eax -> s1
                mov edi, edx ; edi -> s2
                mov edx, eax ; edx -> s1
                
                mov ax, [var] ; ax = [var]
                stosb  ; s2[i] = al

                ; revin la conventia initiala de adrese a sirurilor
                mov eax, edi  ; eax -> s2
                mov edi, edx  ; edi -> s1
                mov edx, eax  ; edx -> s2
                
                jmp continue_next
                
                bl_egal_cu_bh:
                    ; aici bh = bl
                    ; s1 = bh sau bl
                    ; s2 = 0
                    mov al, bl
                    stosb  ; s1[i] = bl
                    
                    ; swap intre adrese pt a accesa s2
                    mov eax, edi ; eax -> s1
                    mov edi, edx ; edi -> s2
                    mov edx, eax ; edx -> s1
                    
                    mov al, 0
                    stosb    ; s2[i] = 0
                    
                    ; revin la conventia initiala
                    mov eax, edi ; eax -> s2
                    mov edi, edx ; edi -> s1
                    mov edx, eax ; edx -> s2
                    
            continue_next:
        
            pop ecx ; iau in ecx valoarea pe care am pus o in stiva pentru a merge
                    ; la urmatorul element din s
        loop repeta
        
    sfarsit:
        push dword 0          
        call [exit]           