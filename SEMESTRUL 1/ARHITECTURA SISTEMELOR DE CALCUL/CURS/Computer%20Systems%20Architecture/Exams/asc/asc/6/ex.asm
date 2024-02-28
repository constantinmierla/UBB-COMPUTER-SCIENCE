bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf, fopen, fclose, fread
import printf msvcrt.dll  
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file_name db 'ex6file.txt', 0
    mod_access db 'r', 0
    descriptor_file dd  -1
    
    len equ 1 ; we want to read character by character
    buffer resb len ; we store here the digit everytime we read one
    
    max_freq dd 0 ; this is the max 
    answer_digit dd 0 ; this is the digit with the maximum frequency
    
    frequency times 10 db 0 ; we initalize the frequency vector
    
    ; format db '%d', 0
    answer_format db 'The digit with the maximum frequency is %d, appearing %d times'
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ; deschidere fisier
        push dword mod_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        mov [descriptor_file], eax
        
        ; check if everything worked
        cmp eax, 0
        je final
        
        ; read the digits
        read_loop:
            push dword [descriptor_file]
            push dword len
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            ; eax = number of charcaters / bytes read
            cmp eax, 0 ; if it's 0, it means we reached the end of the file
            je close_file
            
            ; we check if the character read is a digit
            mov eax, 0 ; clear the digit "container"
            mov al, byte [buffer] ; we move the byte from buffer into al
            
            cmp al, '0'
            jb read_loop ; it means the character is below '0', meaning it's not a digit - so we want to read another one
            
            cmp al, '9'
            ja read_loop ; it means the character is above '9', meaning it's not a digit - so we want to read another one
            
            ; if we reach this point it means the character is a digit
            sub al, 48 ; we convert from the ascii code of the digit to the actual digit value (the ascii code of '0' is 48)
            
            ; now we want to increase the frequency
            ; for digit 0 -> we increase the byte from [frequency + 0]
            ; for digit 1 -> we increase the byte from [frequency + 1]
            ; for digit x -> we increase the byte from [frequency + x]
            inc byte [frequency + eax]
            
            ; in case you want to output everytime each digit you read
            ; push dword eax
            ; push dword format
            ; call [printf]
            ; add esp, 4 * 2
            
            ; we read another one
            jmp read_loop
            
        
        close_file:
        ; close the opened file
        push dword [descriptor_file]
        call [fclose]
        add esp, 4
        
        ; we closed the file, we read everything we need, now we go through the loop and find the maximum
        mov dword [max_freq], 0
        mov ecx, 10 ; the counter for the loop
        
        frequency_loop:
            
            ; we are on digit with the value (ecx - 1) and the frequency [frequency + (ecx - 1)]
            mov ebx, ecx
            sub ebx, 1 ; we computed ecx - 1 = ebx = our digit
            
            mov al, byte [frequency + ebx] ; we move into al the frequency of the current digit
            
            ; we compare with the maximum 
            cmp al, byte [max_freq]
            jl not_a_better_max
            
            ; if we reach this point, it means we found a better maximum, so we update the solution
            mov byte [max_freq], al
            mov byte [answer_digit], bl ; our digit is inside ebx, but in reality, since the digit is on a byte, it means it is contained in bl
                
            not_a_better_max:
            
        loop frequency_loop
        
        final:
        
        ; now we print what we have
        push dword [max_freq]
        push dword [answer_digit]
        push dword answer_format
        call [printf]
        add esp, 4 * 3
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
