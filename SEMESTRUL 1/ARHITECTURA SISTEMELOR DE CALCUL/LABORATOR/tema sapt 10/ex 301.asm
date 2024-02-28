bits 32 

global start        

extern exit, scanf, printf              
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 0
	format db "%d", 0
    ; ...

; our code starts here
segment code use32 class=code
    ;30/1. Se citesc de la tastatura numere (in baza 10) pana cand se introduce cifra 0. Determinaţi şi afişaţi cel mai mic număr dintre cele citite.
    start:
	push dword a
	push dword format
	call [scanf]
	add esp, 4 * 2
	mov ebx, dword[a]
	read_numbers:
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		mov eax, dword[a]
		cmp eax, 0
		jz final
		
		cmp ebx, eax
		jl read_numbers
		mov ebx, eax
		jmp read_numbers

	final:
		push ebx
		push dword format
		call [printf]
		add esp, 4 * 2
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program