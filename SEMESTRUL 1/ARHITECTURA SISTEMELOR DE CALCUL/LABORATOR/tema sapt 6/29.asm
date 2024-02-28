bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; ... 
    ; a = dword, b = dword
    ; c = qword
    a DD 10111001011010011011100101101001b  ; a = B969B969h
    b DD 01101001110100110110100111010011b  ; b = 69D369D3h
    cc DQ 0
segment code use32 class=code
start:
    ; se construieste c in edx:eax
    mov edx, 0
    mov eax, 0
    
    ; bitii 56-63 ai lui C sunt bitii 24-31 ai rezultatului A XOR 0ABh
    mov EBX, [a]               ; ebx = 1011100101101001 1011100101101001b
    shr EBX, 24                ; ebx = 000000B9h
    xor BL, 0ABh               ; bl = 12h    
    mov DL, BL                 ; dl = 12h
    
    ; bitii 43-55 ai lui C sunt bitii 1-13 ai lui A
    mov EBX, [a]             
    shr EBX, 1
    and EBX, 00001FFFh
    shl EDX, 13
    or EDX, EBX    
    
    ; bitii 32-42 ai lui C sunt bitii 21-31 ai lui B
    mov EBX, [b]
    shr EBX, 21
    shl EDX, 11
    or EDX, EBX                ; e corect construit, l am facut pe hartie
    
    ; bitii 22-31 ai lui C au valoarea 0
    ; sunt deja, eax a fost initializat cu 0
    
    ; bitii 16-21 ai lui C sunt 101010
    shl EAX, 6
    or AL, 00101010b           ; eax = 0000002Ah
    
    ; bitii 8-15 ai lui C sunt bitii 23-30 ai lui B complementati
    mov EBX, [b]               ; ebx = 69D369D3h
    shr EBX, 23                ; bl = D3h
    not EBX                    ; bl = 2Ch
    shl EAX, 8                 ; eax = 00002A00h
    mov AL, BL                 ; eax = 00002A2Ch
    
    ; bitii 0-7 ai lui C sunt bitii 21-28 ai lui A
    mov EBX, [a]               ; ebx = B969B969h
    shr EBX, 21                ; bl = 11001011b = CBh
    shl EAX, 8                 ; eax = 002A2C00h
    mov AL, BL                 ; eax = 002A2CCBh
    
    ; rezultatul se regaseste in edx:eax, se muta in variabila c
    push EDX
    pop dword[cc + 4]
    push EAX
    pop dword[cc]