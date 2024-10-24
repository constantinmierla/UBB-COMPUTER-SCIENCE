bits 32

global start        

extern exit, scanf, printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 0
	b dd 0
	format_d db "%d%d", 0
	format_hexa db "%X", 0
    ; ...

; our code starts here
segment code use32 class=code
    ;15/1. Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a+b. Sa se afiseze rezultatul adunarii in baza 16.

    start:
		push dword a
		push dword b
		push dword format_d
		call [scanf]
		add esp, 4 * 3

		mov eax, [a]
		add eax, [b]
		
		push eax
		push dword format_hexa
		call [printf]
		add esp, 4 * 2
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program