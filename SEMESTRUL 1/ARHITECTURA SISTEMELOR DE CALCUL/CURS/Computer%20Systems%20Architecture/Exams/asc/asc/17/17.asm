bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, scanf, fprintf
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    seven dd 7
    answer dd 0
    
    mode_access db 'w', 0
    file_name db '17.txt', 0
    file_descriptor dd -1
    
    number dd 0
    read_format db '%d', 0
    print_format db '%d', 0
    
; our code starts here
segment code use32 class=code
    start:
        ; A file name is given (defined in the data segment). Create a file with the given name, then read numbers from the keyboard and write only the numbers divisible by 7 to file, until the value '0' is read from the keyboard.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final 
        mov [file_descriptor], eax
        
        ; read numbers
        while_read_numbers:
            push dword number
            push dword read_format
            call [scanf]
            add esp, 4 * 2
            
            mov eax, dword [number]
            cmp eax, 0
            je end_while_read_numbers
            
            mov edx, 0
            div dword [seven]
            
            cmp edx, 0
            jne not_divisible
            
            inc dword [answer]
            
            not_divisible:
            jmp while_read_numbers
            
        end_while_read_numbers:
        
        ; print the result
        push dword [answer]
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
