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
    file_name db '22.txt', 0
    file_descriptor dd -1
    
    decimal_number dw 23
    ten_power dw 10000
    ten dw 10
    digit dd 0
    
    print_format db '%d', 10, 0
; our code starts here
segment code use32 class=code
    start:
        ; A file name and a decimal number (on 16 bits) are given (the decimal number is in the unsigned interpretation). Create a file with the given name and write each digit composing the number on a different line to file.
        
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ; check if the file opened correctly
        cmp eax, 0
        je final 
        mov [file_descriptor], eax
        
        ; iterate through the number's digits from left to right
        ; since the number is an unsigned on 16 bits - it is maximum 65.535 - 5 digits
        
        ; first of all, we need to find the first digit that is different from 0 starting from left (i.e. - if we have the number 43 we won't display 00043)
        
        ; to get the digit from the position 5 - we divide the number to 10^4 => then, the number is updated with the remainder of this divison
        ; to get the digit from the position 4 - we divide the number to 10^3 => then, the number is updated with the remainder of this divison
        ; and so on
        
        mov ax, [decimal_number] ; we keep the number inside ax
        
        find_first_digit_not_0:
            mov cx, ax ; keep an old copy of the number
            
            ; move ax into dx:ax to perform division
            mov dx, 0
            
            ; make the divison
            div word [ten_power] ; now in ax we have the current digit, and in dx the updated number (the reminder)
            mov bx, dx ; since we need dx later on, we keep the reminder (aka the updated number) in bx
            
            cmp ax, 0
            jne print_digits ; we found the first non-zero digit
           
            ; otherwise - the number is not that big - we just update the ten_power and we assign the updated number
            
            mov ax, [ten_power] ; ax = ten_power
            mov dx, 0 ; dx:ax = ax = ten_power
            div word [ten] ; ax = dx:ax / 10 = the new ten_power
            mov [ten_power], ax ; update the new ten_power
            
            mov ax, bx ; ax = bx = the new updated number
            
            ; if the number becomes 0 - it means the number is itself 0
            cmp ax, 0
            je number_is_0
            
            jmp find_first_digit_not_0
            
        print_digits: 
            ; we get each digit and we print it - we do almost the same as above
            ; we also need our old number before we checked if the first digit was different from 0 (that's why we made that "old copy")
            mov ax, cx
            
            ; move ax into dx:ax to perform division
            mov dx, 0
            
            ; make the divison
            div word [ten_power] ; now in ax we have the current digit, and in dx the updated number
            mov bx, dx ; since we need dx later on, we keep the reminder (aka the updated number) in bx
            
            ; print the digit - since we push a doubleword we update the variable digit in two steps
            mov word [digit], ax
            mov word [digit + 2], 0
            
            pushad
            push dword [digit]
            push dword print_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            popad
           
            ; update the ten_power and assign the updated number
            mov eax, 0 ; eax = 0
            mov ax, [ten_power] ; eax = ax = ten_power
            mov dx, 0 ; dx:ax = ax = ten_power
            div word [ten] ; ax = dx:ax / 10 = the new ten_power
            mov [ten_power], ax ; update the new ten_power
            
            mov eax, 0 ; eax = 0
            mov ax, bx ; ax = eax = the new updated number
            
            ; if the number becomes 0 - we end the loop
            cmp ax, 0
            je close_file
            
            ; otherwise, we need to compute new digits to print
            jmp find_first_digit_not_0
        
        number_is_0:
        ; if we didn't enter the print_digits loop, it means the number is itself 0 - we need to print only 0
        mov dword [digit], 0
        push dword [digit]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        close_file:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
