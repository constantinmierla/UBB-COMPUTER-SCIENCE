bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fprintf, scanf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

    mode_access db 'w', 0
    file_name db '11.txt', 0
    file_descriptor dd -1

    a_word resb 100 ; we assume a word has a maximum of 100 characters
    read_format db '%s', 0
    print_format db '%s', 10, 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name is given (defined in the data segment). Create a file with the given name, then read words from the keyboard and write those words in the file, until character '$' is read from the keyboard.

        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax

        ; read word from the keyboard
        while_read_words:
            push dword a_word
            push dword read_format
            call [scanf]
            add esp, 4 * 2

            ; check if we reach '$'
            cmp byte [a_word], '$'
            je end_while_read_words

            ; we append it to the file
            push dword a_word
            push dword print_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3

            jmp while_read_words ; read another word

        end_while_read_words:
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
