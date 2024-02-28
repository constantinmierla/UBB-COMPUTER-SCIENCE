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
    
    file_name db '28.txt', 0
    mode_access db 'a', 0
    file_descriptor dd -1
    
    read_format db '%s', 0
    a_word resb 100 ; we assume the word as a maximum of 100 characters
    
    ok db 0
    
    print_format db '%s', 10, 0
    
; our code starts here
segment code use32 class=code
    start:
        ; Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o litera mica (lowercase).
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; read word
        while_read_words:
            ; read a word
            push dword a_word
            push dword read_format
            call [scanf]
            add esp, 4 * 2
            
            ; check if the word contains a lowercase letter
            mov byte [ok], 0 ; we assume it doesn't
            mov ecx, 0 ; in ecx we keep the couter that helps us iterate through the word
            go_through_word:
                ; get the character
                mov al, byte [a_word + ecx]
                
                ; we check the stop condition
                cmp al, '$'
                je close_file
                
                ; we check if we reached the end of the word
                cmp al, 0
                je end_go_through_word
                
                ; we check if the letter is lowercase
                inc ecx ; in case we do an early jump back to go_through_word
                cmp al, 'a'
                jb go_through_word
                cmp al, 'z'
                ja go_through_word
                
                ; the character is a lowercase letter 
                mov byte [ok], 1
                
                
            end_go_through_word:
            
            cmp byte [ok], 1
            jne while_read_words ; the word is not valid - we read another one
            
            ; the word is valid - we append it to the file
            pushad 
            push dword a_word
            push dword print_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            popad
            
            jmp while_read_words
            
        close_file:
        
        push dword [file_descriptor]
        call dword [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
