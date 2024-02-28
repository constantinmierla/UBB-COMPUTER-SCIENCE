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
    
    mode_access db 'w', 0
    file_name db '14.txt', 0
    file_descriptor dd -1
    
    string db 'This is Such a NICE String @! - and OF course some special charS'
    string_len equ ($ - string)
    updated_string times (string_len + 1) db 0
    
    print_format db '%s', 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a text (defined in the data segment) are given. The text contains lowercase letters, uppercase letters, digits and special characters. Transform all the uppercase letters from the given text in lowercase. Create a file with the given name and write the generated text to file.
        
        ; open the file
        push dword mode_access 
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; chech if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; loop through the text char by char
        mov esi, string
        mov edi, updated_string
        mov ecx, string_len
        
        text_loop:
            lodsb ; al - the current character
            
            ; check if the character is an uppercase letter
            cmp al, 'A'
            jb not_uppercase
            cmp al, 'Z'
            ja not_uppercase
            
            ; if we reach this point, it means our character is an uppercase letter - we transform it
            sub al, 65
            add al, 97
            
            not_uppercase:
            stosb 
            loop text_loop
        
        ; we print the text
        push dword updated_string
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
