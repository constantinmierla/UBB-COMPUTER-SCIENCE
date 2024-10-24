bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fprintf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    mode_access db 'a', 0
    file_name db '15.txt', 0
    file_descriptor dd -1
    
    char dd 0
    
    text db 'This#is#such#a123@@@!!nice00wo!-'
    text_len equ ($ - text)
    updated_text resb (text_len + 1)
    
    print_format db '%s', 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a text (defined in the data segment) are given. The text contains lowercase letters, uppercase letters, digits and special characters. Replace all the special characters from the given text with the character 'X'. Create a file with the given name and write the generated text to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        mov esi, text
        mov edi, updated_text
        mov ecx, text_len
        ; iterate through the text
        while_read:
            ; get the character
            lodsb
           
            cmp al, '0'
            jb not_a_digit
            cmp al, '9'
            ja not_a_digit
            ; if we reach here - it is a digit - we read again
            stosb
            jmp read_again
            
            not_a_digit:
            cmp al, 'a'
            jb not_a_lowercase_letter
            cmp al, 'z'
            ja not_a_lowercase_letter
            ; if we reach here - it is a lowercase letter - we read again
            stosb
            jmp read_again
            
            not_a_lowercase_letter:
            cmp al, 'A'
            jb not_an_uppercase_letter
            cmp al, 'Z'
            ja not_an_uppercase_letter
            ; if we reach here - it is an uppercase letter - we read again
            stosb
            jmp read_again
            
            not_an_uppercase_letter:
            ; if we reach here - it is a special character
            mov al, 'X'
            stosb
            
            read_again:
            loop while_read
            
        end_while_read:
        mov al, 0
        stosb
        
        ; print the text
        push dword updated_text
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
