bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, printf, fread
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    mode_access db 'r', 0
    file_name db '18.txt', 0
    file_descriptor dd -1
    
    char dd 0
    words dd 0
    print_format db '%d', 0
    
; our code starts here
segment code use32 class=code
    start:
        ; A text file is given. The text contains letters, spaces and points. Read the content of the file, determine the number of words and display the result on the screen. (A word is a sequence of characters separated by space or point
    
        ; open the file 
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax 
        
        ; read char by char from file
        while_read:
            ; read the char
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword char
            call [fread]
            add esp, 4 * 4
            
            ; check if anything was read
            cmp eax, 0
            je end_while_read
            
            ; check if it's a space or a point
            cmp byte [char], ' '
            je while_read
            cmp byte [char], '.'
            je while_read
            
            ; if it's not a space, nor a point - it's a letter
            ; we increment the number of words
            ; we read the letters from the word as long as we can
            inc dword [words]
            while_read_letters:
                ; read the char
                push dword [file_descriptor]
                push dword 1
                push dword 1
                push dword char
                call [fread]
                add esp, 4 * 4
                
                ; check if anything was read
                cmp eax, 0
                je end_while_read
                
                ; check if it's a space or a point
                cmp byte [char], ' '
                je while_read
                cmp byte [char], '.'
                je while_read
                
                jmp while_read_letters
            
        end_while_read: 
        ; print the result
        push dword [words]
        push dword print_format
        call [printf]
        add esp, 4 * 2
        
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
