bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, scanf, fprintf, fclose
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

    mode_access db 'a', 0
    file_name db '26.txt', 0

    file_descriptor dd -1

    a_word resb 100 ; we assume a word has a maximum of 100 characters
    read_word_format db '%s', 0

    ok db 0
    print_word_format db '%s', 10, 0
; our code starts here
segment code use32 class=code
    start:
        ; Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o litera mare (uppercase).

        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file was created correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax

        ; read the words
        read_words:
            ; read a word
            push dword a_word
            push dword read_word_format
            call [scanf]
            add esp, 4 * 2

            ; iterate through the letters of the word
            mov ecx, 0 ; the counter to iterate over the letters inside the word
            mov byte [ok], 0 ; we assume we don't have a valid word
            through_word:
                ; save the letter
                mov al, byte [a_word + ecx]

                ; check if we reached the end of the word
                cmp al, 0
                je end_through_word

                ; check if we reached the '$' sign
                cmp al, '$'
                je end_through_word

                ; check if we have an uppercase letter
                inc ecx

                cmp al, 'A'
                jb through_word
                cmp al, 'Z'
                ja through_word

                ; if we reached this point, it means we have an uppercase letter - we mark the word as being correct
                mov byte [ok], 1
                jmp through_word

            end_through_word:

            cmp byte [ok], 1
            jne not_ok ; the word is not valid - we read another one

            ; if we reached this point - it means the word contains at least an uppercase letter - we append it to the file
            pushad
            push dword a_word
            push dword print_word_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            popad

            not_ok:
            ; we compare again if we reached the '$' character - since we didn't change eax, it means the value of that character is still inside al
            cmp al, '$'
            je end_read_words

            ; otherwise - we read another word
            jmp read_words

        end_read_words:
        ; we close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
