bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fprintf, printf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ten dd 10
    digits_string times 10 db 0
    
    mode_access db 'a', 0
    file_name db '20.txt', 0
    file_descriptor dd -1
    
    string db 'this is a really nice string'
    string_len equ ($ - string)
    updated_string times (3 * string_len + 1) db 0 
    
    print_format db '%s', 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a text (defined in the data segment) are given. The text contains lowercase letters and spaces. Replace all the letters on even positions with their position. Create a file with the given name and write the generated text to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        mov esi, string
        mov edi, updated_string
        mov ebx, 1
        
        loop_string:
            cmp ebx, string_len
            ja end_loop_string
            
            lodsb
            cmp al, ' '
            je not_a_letter
            
            test ebx, 1
            jnz not_even_pos
            
            mov eax, ebx
            mov ecx, 0
            
            while_eax:
                cmp eax, 0
                je end_while_eax
                
                mov edx, 0
                div dword [ten]
                
                add edx, 48
                mov byte [digits_string + ecx], dl
                inc ecx 
                
                jmp while_eax
            
            end_while_eax: 
            dec ecx
            
            while_chars:
                mov al, [digits_string + ecx]
                stosb
                
                cmp ecx, 0
                je finished_printing
                dec ecx
                jmp while_chars
            
            not_even_pos:
            not_a_letter:
            stosb
            
            finished_printing:
            inc ebx
            dec ecx
        jmp loop_string
        
        end_loop_string:
        mov al, 0
        stosb
        
        ; print the message
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
