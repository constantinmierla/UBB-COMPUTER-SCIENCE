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
    ; a - dword
    a DD 10110101101001100001101001011011b ; 14-17: 1000b, cand shiftez la dreapta 
                                           ; ar trebui sa imi apara 8 pe prima poz in eax
                                           ; a = B5A61A5B
    b DD 0
    cc DB 0                                ; bitii 0-5 ai lui C coincid cu bitii 1-6 ai lui B
                                           ; bitii 6-7 ai lui C coincid cu bitii 17-18 ai lui B
segment code use32 class=code
start:
    ; nr intreg format din bitii 14-17 ai lui a
    mov EAX, [a]
    shr EAX, 14           
    and EAX, 0000000Fh    ; AL = n = 8
    
    ; b = rotirea la stanga a lui a cu n biti
    mov CL, AL
    mov EAX, [a]
    rol EAX, CL
    mov [b], EAX          ; b = A61A5BB5h = 10100100000110100101101110110101b 
    
    ; bitii 0-5 ai lui C coincid cu bitii 1-6 ai lui B
    mov BL, 0
    shr EAX, 1
    and EAX, 0000003Fh    
    mov BL, AL            ; bl = 00011010b = 1Ah
    
    ; bitii 6-7 ai lui C coincid cu bitii 17-18 ai lui B
    mov EAX, [b]                  
    shr EAX, 17           ; eax = 101001000001101b = 0000520Dh
    and EAX, 00000003h    ; eax = 00000001h
    shl AL, 6
    or BL, AL             ; bl = 01011010b = 5Ah
    mov [cc], BL          ; c = rezultat