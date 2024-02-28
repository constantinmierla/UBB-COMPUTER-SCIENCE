bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fprintf, fclose
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    mode_access db 'w', 0
    file_name db '19.txt', 0
    file_descriptor dd -1
    
    string db 'This is a 34@SADD@!!DSA--0023521-125 string'
    string_len equ ($ - string)
    sum dd 0
    
    print_format db '%d', 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a text (which can contain any type of character) are given in data segment. Calculate the sum of digits in the text. Create a file with the given name and write the result to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax 
        
        ; iterate through the string
        mov esi, string
        mov ecx, string_len
        mov eax, 0
        loop_string:
            lodsb
            
            cmp al, '0'
            jb not_a_digit
            cmp al, '9'
            ja not_a_digit
            
            sub al, 48
            add dword [sum], eax
            
            not_a_digit:
            loop loop_string
        
        ; print the result
        push dword [sum]
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
