bits 32

global start

extern exit, printf, scanf              
import exit msvcrt.dll
import printf msvcrt.dll  
import scanf msvcrt.dll

; pb 18
; Sa se citeasca de la tastatura un numar in baza 10 si un numar in baza 16. 
; Sa se afiseze in baza 10 numarul de biti 1 ai sumei celor doua numere citite. Exemplu:
; a = 32 = 0010 0000b
; b = 1Ah = 0001 1010b
; 32 + 1Ah = 0011 1010b
; Se va afisa pe ecran valoarea 4.

; segmentul de date in care se vor defini variabilele 
segment data use32 class=data
    a dd 0
    b dd 0
    format_intreg db "%d", 0
    format_hexa db "%x", 0
segment code use32 class=code
    start:
        ; citesc nr a
        push dword a
        push dword format_intreg
        call [scanf]
        add esp, 4 * 2
        mov dword[a], 32
        
        ; citesc nr b
        push dword b
        push dword format_hexa
        call [scanf]
        add esp, 4 * 2
        
        ; a + b
        mov eax, [a]
        add eax, [b]          ; eax = a + b
        
        ; aflu nr de biti a lui a + b
        mov ebx, 0            ; ebx = nr de 1
        mov ecx, 32
        repeta:
            shr eax, 1        ; CF = bitul 0 a lui eax
            
            jnb continue      ; daca bitul e 0, merg la eticheta continua
            inc ebx
            
            continue:
                nop
        loop repeta
        
        ; afisez nr de biti 1
        push ebx
        push format_intreg
        call [printf]
        add esp, 4 * 2
        
    sfarsit:
        ; exit(0)
        push dword 0          ; se pune pe stiva parametrul functiei exit
        call [exit]           ; apelul functiei exit pentru terminarea executiei programului