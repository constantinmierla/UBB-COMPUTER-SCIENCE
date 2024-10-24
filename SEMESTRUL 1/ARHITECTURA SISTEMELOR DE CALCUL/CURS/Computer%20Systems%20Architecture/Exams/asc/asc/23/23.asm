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
    
    mode_access db 'a', 0
    file_name db '23.txt', 0
    file_descriptor dd -1
    
    hexa_number dw 0xECC2
    nibble dd 0
    sixteen db 16
    
    print_format db '%d', 0
    print_new_line db 10, 0
    
; our code starts here
segment code use32 class=code
    convert:
        mov al, bl
        mov ah, 0
        mov dl, 8 ; dl = byte 8
        div dl ; al = bl / 8 and ah = bl % 8
        
        mov [nibble], al
        ; we print it now
        pushad
        push dword [nibble]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        popad
        
        ; (y / 4 % 2)
        mov al, bl
        mov ah, 0
        mov dl, 4 ; dl = byte 4
        div dl ; al = bl / 4 and ah = bl % 4
        mov ah, 0 ; ax = al = bl / 4
        mov dl, 2
        div dl ; al = bl / 4 / 2 and ah = bl / 4 % 2
        
        mov [nibble], ah
        ; we print it now
        pushad
        push dword [nibble]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        popad
        
        ; (y / 2 % 2)
        mov al, bl
        mov ah, 0
        mov dl, 2 ; dl = byte 2
        div dl ; al = bl / 2 and ah = bl % 2
        mov ah, 0 ; ax = al = bl / 2
        mov dl, 2
        div dl ; al = bl / 2 / 2 and ah = bl / 2 % 2
        
        mov [nibble], ah
        ; we print it now
        pushad
        push dword [nibble]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        popad
        
        ; (y % 2)
        mov al, bl
        mov ah, 0
        mov dl, 2 ; dl = byte 2
        div dl ; al = bl / 2 and ah = bl % 2
        
        mov [nibble], ah
        ; we print it now
        pushad
        push dword [nibble]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        popad
        
        ; print the new line
        pushad 
        push dword print_new_line
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 2
        popad 
        
        ret

    start:
        ; A file name and a hexadecimal number (on 16 bits) are given. Create a file with the given name and write each nibble composing the hexadecimal number on a different line to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file was opened
        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        ; the number itself consists of 2 bytes - each byte is composed of two nibbles
        ; because of the little endian representation - we need to get first time the second byte from the memory, and then the first byte
        
        mov ecx, 1
        loop_bytes:
            mov al, [hexa_number + ecx] ; get the corresponding byte - consisting of two nibbles
            ; how do we split those two nibbles? - if we look at it in a binary way, we can see that if we have a number as a byte - call it x, we can get the first nibble by performing (x // 16) and the second nibble by performing (n % 16); 16 = 2 ^ 4, 4 being the number of bits of a single nibble
            
            ; in order to perform this division (which is unsigned) we need to move al into ax
            mov ah, 0
            
            ; now we perform the divison
            div byte [sixteen] ; and now inside al = (x // 16) and inside ah = (x % 16)
            
            ; now we want to convert each nibble into a binary number
            ; a decimal number y on 4 bits has the corresponding binary number (y / 8) | (y / 4 % 2) | (y / 2 % 2) | (y % 2)
            
            ; and this is what are going to do - first with al, then with ax
            ; since we will perform division, we need to safe store those values inside ebx
            mov bl, al
            mov bh, ah
            
            call convert
            mov bl, bh ; bl gets the value of bh as well, since inside convert we work with bl
            call convert
            
            cmp ecx, 0
            je close_file
            
            dec ecx
            jmp loop_bytes
       
        ; close the file
        close_file:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
