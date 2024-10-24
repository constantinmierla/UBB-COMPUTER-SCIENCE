bits 32

global start

extern exit, fopen, fprintf, fclose, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll     

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "30.txt", 0       
    access_mode db "w", 0           
                                    
    file_descriptor dd -1           
    stringformat db "%s", 0
	newline db "%s", 10, 0
	text resb 100  

; our code starts here
segment code use32 class=code
    ;30/2. Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o cifra.
    start:
        
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                

        mov [file_descriptor], eax  

        
        cmp eax, 0
        je final

        
		read_value:
			push dword text
			push dword stringformat
			call [scanf]       
			add esp, 4 * 2
			
			
			mov AL, [text]
			mov BL, '$'
			cmp AL, BL
			
			jz close
			mov esi, text
			check:
				LODSB
				cmp AL, 0
				jz read_value
				cmp AL, '0'
				jb check
				cmp AL, '9'
				ja check
				push dword text
				push dword newline
				push dword [file_descriptor]
				call [fprintf]
				add esp, 4 * 3
				jmp read_value
	
        
		close:
			push dword [file_descriptor]
			call [fclose]
			add esp, 4

      final:

        ; exit(0)
        push dword 0
        call [exit]