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
    two dd 2
    
    mode_access db 'r', 0
    file_name db '9.txt', 0
    file_descriptor dd -1
    
    a_char db 0
    
    frequency_array resw 200 ; the n(th) word from this array has as a value the number of times the character with the ascii code of n appears
    maximum dd 0
    answer_char dd 0
    
    print_format db '%d %c', 0
; our code starts here
segment code use32 class=code
    start:
        ; A text file is given. Read the content of the file, determine the special character with the highest frequency and display the character along with its frequency on the screen. The name of text file is defined in the data segment.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; read character by character from the file
        read_characters:
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword a_char
            call [fread]
            add esp, 4 * 4
            
            ; we check if we read something
            cmp eax, 0
            je end_read_characters
            
            ; move the character inside al
            mov al, byte [a_char]
            
            ; check if the character is a digit
            cmp al, '0'
            jb not_a_digit
            cmp al, '9'
            ja not_a_digit
            ; if we reach this point, it means it is a digit, so we read another character
            jmp read_characters
            
            not_a_digit:
            
            ; check if the character is a lowercase letter
            cmp al, 'a'
            jb not_a_lowercase
            cmp al, 'z'
            ja not_a_lowercase
            ; if we reach this point, it means it is a lowercase letter, so we read another character
            jmp read_characters
            
            not_a_lowercase:
            
            ; chech if the character is an uppercase letter
            cmp al, 'A'
            jb not_an_uppercase
            cmp al, 'Z'
            ja not_an_uppercase
            ; if we reach this point, it means it is an uppercase letter, so we read another character
            jmp read_characters
            
            not_an_uppercase:
            
            ; if it is a space, we read another character
            cmp al, ' '
            je read_characters
            
            ; if it is a "new line", we read another character
            cmp al, 10
            je read_characters
            
            ; if we reach this point, it means that it is a special character -> we increment the frequency
            mov ah, 0 ; ax = al 
            ; we also multiply it with 2, since our frequency array is made up of words
            mul word [two] ; eax = 2 * al
            ; now we increment the frequency
            inc word [frequency_array + eax]
           
            ; and of course ... we read again
            jmp read_characters
            
        end_read_characters:
        ; we loop through the array and find the maximum, while also keeping the ascii code of the character
        ; for that we need a counter
       
        mov esi, frequency_array
        mov ecx, 200 ; we have 200 words
        mov ebx, 0 ; 
        loop_array:
            mov eax, 0
            lodsw            
            ; we compare it with the maximum
            cmp eax, [maximum]
            jbe not_a_better_maximum
            ; if we reach this point, we have a better maximum
            mov [maximum], eax 
            mov [answer_char], ebx 
            
            not_a_better_maximum: 
            inc ebx
            loop loop_array 
        
        ; we print the result
        push dword [answer_char]
        push dword [maximum]
        push dword print_format
        call [printf]
        add esp, 4 * 3
        
        ; close the file 
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
