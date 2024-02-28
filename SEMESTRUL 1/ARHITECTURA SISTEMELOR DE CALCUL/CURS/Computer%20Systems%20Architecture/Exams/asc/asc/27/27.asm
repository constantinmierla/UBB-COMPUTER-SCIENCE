bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fread, fprintf, fclose
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    mode_access db 'a+', 0
    file_name db '27.txt', 0
    
    file_descriptor dd -1
    a_char dd 0
    
    ten dd 10
    minimum dd 2147483647 ; biggest number on signed dwords
    
    sign dd -1
    
    print_format db ' %d', 0
; our code starts here
segment code use32 class=code
    start:
        ; Se da un fisier text. Fisierul contine numere (in baza 10) separate prin spatii. Sa se citeasca continutul acestui fisier, sa se determine minimul numerelor citite si sa se scrie rezultatul la sfarsitul fisierului.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; read the file character by character
        while_read_char:
            
            ; read a character
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword a_char
            call [fread]
            add esp, 4 * 4
            
            ; check if we read at least something
            cmp eax, 0
            je end_while_read_char
            
            ; check if the character is a space - in this case we read another one
            cmp byte [a_char], ' '
            je while_read_char
            
            ; check if the character is a '-'
            cmp byte [a_char], '-'
            mov eax, 0
            mov dword [sign], -1
            je while_digit
            
            ; if it was not a space, nor a '-', it is a digit 
            mov eax, [a_char] ; in eax we build the number
            sub eax, 48 ; we convert it into decimal
            mov dword [sign], 1
            
            ; now we read digits as long as we can
            while_digit:
                pushad ; we have to keep the number in eax - so we don't want the registers to be changed
                
                ; we read another character
                push dword [file_descriptor]
                push dword 1
                push dword 1
                push dword a_char
                call [fread]
                add esp, 4 * 4
                
                ; check if something was at least read
                cmp eax, 0
                jne more_char ; if something was read we keep going
                
                ; if nothing was read at this point, we still need to pop back the value to eax and compare it to the minimum in case we find a better minimum
                popad
                jmp end_while_digit ; but of course, we end our while_digit loop
                
                more_char:
                popad ; give back the value to the registers
                        
                ; check if it's a space
                cmp byte [a_char], ' '
                je end_while_digit
                
                ; if it was not a space - it was another digit 
                mov ebx, [a_char]
                sub ebx, 48 ; we convert it into decimal
                
                ; now we want to compute the new number eax = eax * 10 + ebx
                mul dword [ten] ; we assume the result will fit into a doubleword - edx:eax = eax * 10 - but we don't really care about edx, since the actual result is still in eax
                add eax, ebx ; eax * 10 = eax * 10 + ebx
                
                jmp while_digit ; we read another one
             
            end_while_digit:
            
            ; we assign the sign :)
            mul dword [sign] ; the result is still inside eax
            
            ; here we have our number inside eax - we compare it with the minimum
            cmp eax, [minimum]
            jge while_read_char ; the number is irelevant - we proceed on reading another one
            
            ; if we reached here, it means that the number is lower - we update the minimum
            mov [minimum], eax
            jmp while_read_char
        
        end_while_read_char:
        
        ; append the minimum
        push dword [minimum]
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
