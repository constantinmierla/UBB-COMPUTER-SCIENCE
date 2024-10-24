bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, scanf, fclose, fprintf
import fopen msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ; Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o cifra.
    
    file_name db '30.txt', 0
    mode_access db 'a', 0
    char_format db '%c', 0
    file_descriptor dd -1
    
    ok db 0
    
    print_word_format db '%s', 10, 0
    
    a_word resb 100 ; we keep 100 bytes for a single word
    read_word_format db '%s', 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ; open the file
        ; fopen(file_name, mode_access) 
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        read_word_loop:
            ; read the word from the console
            push dword a_word
            push dword read_word_format
            call [scanf]
            add esp, 4 * 2
            
            ; now we have the word inside a_word, which is a string of bytes of characters
            ; we start with the character on the position ecx = 0
            mov ecx, 0
            ; we suppose that our word doesn't contain any digit
            mov byte [ok], 0 
            
            go_through_word:
                mov al, byte [a_word + ecx]
                
                ; we check if we reached the end of the word
                cmp al, 0
                je end_go_through_word
                
                ; we check if we reached the end of the whole reading of words
                cmp al, '$'
                je end_read_word_loop
                
                ; otherwise, we have a valid word character
                ; we check if it's a digit inside this word
                cmp al, '0'
                
                inc ecx
                jb go_through_word ; it means al is not a digit, so we go through the loop again and read another character
                dec ecx 
                
                cmp al, '9'
                
                inc ecx 
                ja go_through_word ; it means al is not a digit, so we go through the loop again and read another character
                dec ecx 
                
                ; if we reached this point, it means we found a digit
                mov byte [ok], 1
                inc ecx
                jmp go_through_word
                
           
            end_go_through_word:
            ; we finished to check our word
            cmp byte [ok], 1
            jne not_a_good_word
            
            ; if we reached this point, a_word is a valid word - we append it to the file
            pushad

            ; fprintf(file_descriptor, a_word)
            push dword a_word
            push dword print_word_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            
            popad
            
            not_a_good_word:
            jmp read_word_loop
                
            
        end_read_word_loop: 
        
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
