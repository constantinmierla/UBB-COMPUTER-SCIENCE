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
    file_name db '13.txt', 0
    file_descriptor dd -1
    
    text db 'This is such a nice text -@! - togheter with some special characters!'
    text_len equ ($ - text)
    updated_text times (text_len + 1) resb 0
    
    print_format db '%s', 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a text (defined in the data segment) are given. The text contains lowercase letters, uppercase letters, digits and special characters. Transform all the lowercase letters from the given text in uppercase. Create a file with the given name and write the generated text to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; iterate through the text
        mov ecx, text_len
        mov esi, text
        mov edi, updated_text
        loop_text:
            lodsb
            
            cmp al, 'a'
            jb not_lowercase
            cmp al, 'z'
            ja not_lowercase
            
            sub al, 97
            add al, 65
            
            not_lowercase:
            stosb
            
            loop loop_text
        
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
