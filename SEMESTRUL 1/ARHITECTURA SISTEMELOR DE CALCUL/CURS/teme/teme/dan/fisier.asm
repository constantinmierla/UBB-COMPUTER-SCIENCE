; Se da un fisier text care contine litere, spatii si puncte. 
; Sa se citeasca continutul fisierului, sa se determine numarul de 
; cuvinte si sa se afiseze pe ecran aceasta valoare. 
; (Se considera cuvant orice secventa de litere separate prin spatiu sau punct)

bits 32

global start

extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data
    file_name db "file.txt", 0 ; numele fisierului care va fi creat
    mode_access db "r", 0     ; modul de deschidere a fisierului - r pentru citire
    len equ 100                ; numarul maxim de elemente citite din fisier
    text times (len + 1) db 0  ; sirul in care se va citi textul din fisier
    descriptor dd -1           ; descriptorul fisierului - necesar pentru a putea face referire la fisier
    format db "Am citit %d cuvinte din fisier. Textul este: %s", 0
                               ; formatul - utilizat pentru afisarea textului citit din fisier

segment code use32 class = code
    start:
        ; apelam functia fopen pentru a deschide fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(file_name, mode_access)
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2 ; eliberam parametri de pe stiva

        mov [descriptor], eax ; salvam valoarea returnata de fopen in variabila descriptor

        ; verificam daca functia fopen a creat cu succes fisierul
        ; (daca EAX != 0)
        cmp eax, 0
        ;je final ; daca EAX == 0, atunci iesim din program

        ; apelam functia fread pentru a citi textul din fisier
        ; EAX = fread(text, 1, len, descriptor)
        push dword [descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4

        ; urmeaza sa aflam numarul de cuvinte din fisier
        ; pentru aceasta, vom parcurge sirul de caractere citit din fisier
        ; si vom numara cate cuvinte intalnim
        mov esi, text ; ESI = adresa de inceput a sirului de caractere
        mov ebx, 0    ; EBX = numarul de cuvinte intalnite
        
        ; parcurgem sirul de caractere
        while:
            ; verificam daca am ajuns la sfarsitul sirului
            cmp byte [esi], 0
            je check_last_char_not_space

            ; verificam daca caracterul curent este diferit de spatiu si punct
            ; daca da, atunci verificam daca urmatorul caracter este spatiu sau punct
            cmp byte [esi], ' '
            je check_not_dot
            jmp process_space_or_dot

            check_not_dot:
                cmp byte [esi], '.'
                jne process_space_or_dot

                ; daca am ajuns aici, inseamna ca caracterul curent este spatiu sau punct
                jmp next_char

            ; verificam daca urmatorul caracter este spatiu sau punct
            process_space_or_dot:
                cmp byte [esi + 1], ' '
                je word_found
                cmp byte [esi + 1], '.'
                je word_found

                ; daca am ajuns aici, inseamnca ca am gasit o litera
                jmp next_char

            word_found:
                inc ebx ; am gasit un cuvant, deci incrementam numarul de cuvinte

            next_char:
                inc esi ; trecem la urmatorul caracter
                jmp while ; ne intoarcem la inceputul buclei
        
        ; verificam daca am numarat ultimul cuvant
        check_last_char_not_space:
            cmp byte [esi - 1], ' '
            jne check_last_char_dot
            jmp end_while

        check_last_char_dot:
            cmp byte [esi - 1], '.'
            jne inc_ebx
            jmp end_while

        inc_ebx:
            inc ebx ; incrementam numarul de cuvinte pentru ultimul cuvant

        end_while:
            ; afisam numarul de cuvinte intalnite si textul citit din fisier
            push dword text
            push dword ebx
            push dword format
            call [printf]
            add esp, 4 * 3

            ; apelam functia fclose pentru a inchide fisierul
            ; fclose(descriptor)
            push dword [descriptor]
            call [fclose]
            add esp, 4 * 1

        ;final:   
        push dword 0
        call[exit]