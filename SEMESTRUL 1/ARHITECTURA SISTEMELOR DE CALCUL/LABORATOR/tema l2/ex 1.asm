bits 32 ;asamblare si compilare pentru arhitectura de 32 biti
; definim punctul de intrare in programul principal
global  start 

extern  exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import  exit msvcrt.dll; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 

segment  code use32 class=code ; segmentul de cod
start: 
	;ex 15 : 6*3
    MOV AL, 6
    MOV DH, 3
    MUL DH
    MOV EAX, 0
    ;ex 30 : 11+5
    MOV AL, 11
    ADD AL, 5
	
	push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului	