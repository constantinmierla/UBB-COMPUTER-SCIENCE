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
    file_name db '25.txt', 0
    mode_access db 'w', 0
    file_descriptor dd -1
    
    string db 'this is a wonderful string 32312dw sow wow!@'
    string_len equ ($ - string)
    
    updated_string times (string_len + 1) db -1
    
    print_format db '%s', 0
; our code starts here
segment code use32 class=code
    start:
        ; Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. Sa se inlocuiasca toate spatiile din textul dat cu caracterul 'S'. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut prin inlocuire in fisier.
        
        ; open file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; iterate through the string
        cld
        mov esi, string
        mov edi, updated_string
        mov ecx, string_len
        string_loop:
            lodsb ; al = the current character
           
            cmp al, ' '
            jne not_space
                
            ; if we reach this point, the character is a space - we need to replace it    
            mov al, 'S' 
            
            not_space: 
            stosb ; move it into edi 
        loop string_loop
        
        ; our string is inside edi - but since we want to pass it to a C function, we need to append 0 as well
        mov al, 0
        stosb
        
        ; now we print the new string
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
