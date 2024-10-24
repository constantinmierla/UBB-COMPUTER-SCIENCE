bits 32

global parsare_cuvant

segment data use32 class=data

segment code use32 class=code
    parsare_cuvant:
        mov esi, [esp + 4]
        cld 
        
        mov ebx, 0   ; retin numarul de litere
        .repeta_cuv:
            lodsb      ; al = litera
                
            ; verific daca e litera mare
            cmp al, 'A'
            jb .nu_e_litera
            cmp al, 'Z'
            jb .litera
            
            ; verific daca e litera mica
            cmp al, 'a'
            jb .nu_e_litera
            cmp al, 'z'
            ja .nu_e_litera
                
            ; daca e litera, inc ebx
            .litera:
                add ebx, 1
        jmp .repeta_cuv
            
        ; daca nu e litera, am terminat de parsat cuvantul
        .nu_e_litera:
            ; in ebx avem numarul de litere
            mov eax, ebx 
            stosd
        
        ret