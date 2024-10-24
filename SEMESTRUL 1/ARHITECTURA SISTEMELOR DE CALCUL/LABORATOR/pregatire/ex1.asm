bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
extern fopen,fprintf,fclose
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    ; ...
    filename db "ex19.txt",0
    modacces db "w",0
    descriptor dd -1
    text db "12345",0
    len equ ($-text)
    sum dd 0
    printformat db "%d",0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;calculez suma
        mov esi, text
        mov ecx, len
        mov eax, 0
        calculeaza:
            lodsb
            cmp al,'0'
            jb nue
            cmp al,'9'
            ja nue
            sub al,48
            add dword [sum],eax
            nue:
                loop calculeaza
                
        push dword modacces
        push dword filename
        call [fopen]
        
        mov dword [descriptor],eax
        add esp, 4*2
        
        
        push dword [sum]
        push dword printformat
        push dword [descriptor]
        call [fprintf]
        add esp,4*3
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
