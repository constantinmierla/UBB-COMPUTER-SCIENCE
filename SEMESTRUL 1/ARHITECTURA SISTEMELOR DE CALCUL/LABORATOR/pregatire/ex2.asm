bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern printf,fscanf,fopen,fclose
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    descriptor dd -1
    a db -1
    min dd 16
    filename db "input.txt",0
    modacces db "r",0
    read_format db "%c",0
    print_format db "%c%d",0
    spatiu dd ' '
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword modacces
        push dword filename
        call [fopen]
        mov [descriptor], eax
        add esp, 4*2
        cmp eax, 0
        je final
        citeste:
            push dword a
            push dword read_format
            push dword [descriptor]
            call [fscanf]
            add esp, 4*3
            cmp eax,-1
            je final_citeste
            cmp byte[a], ' '
            jne sari_1
            ;s a terminat numarul
            push dword[min]
            push dword[spatiu]
            push dword print_format
            call [printf]
            add esp,4*3
            
            mov dword[min],16
            sari_1:
            cmp byte[a],'9'
            jle sari_numar
            ja sari_caracter
            
            
            sari_numar:
            mov bl, byte[a]
            sub bl, '0'
            jmp actualizare
            
            sari_caracter:
            mov bl, byte[a]
            sub bl, 'A'
            add bl, 10
            
            actualizare:
            mov cl, bl
            mov ebx, 0
            mov bl,cl
            cmp dword[min], ebx
            ja mai_mic
            jle sari_repeta
            
            mai_mic:
            mov dword[min],ebx
            
            sari_repeta:
            jmp citeste
            
            final_citeste:
            push dword[min]
            push dword[spatiu]
            push dword print_format
            call [printf]
            add esp,4*3
            
        ; exit(0)
        final:
        push dword [descriptor]
        call [fclose]
        add esp, 4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
