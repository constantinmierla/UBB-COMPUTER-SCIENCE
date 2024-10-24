bits 32 
global start 

extern exit
import exit msvcrt.dll
	; 15.
	; Se da un sir S de dublucuvinte.
	; Sa se obtina sirul D format din octetii dublucuvintelor din sirul D, 
	; sortati in ordine descrescatoare in interpretarea fara semn.
	; 01 11 08 C8 45 FE 00 00 E2 4E AF 6D => FE E2 C8 AF 6D 4E 45 11 08 01 00 00
segment  data use32 class=data
	S dd 0C8081101h, 0FE45h, 6DAF4EE2h
	lenSoct equ $-S
	D times lenSoct db 0
	st resd 1
segment  code use32 class=code
start: 
	; BubbleSort
	mov edi, D ;
	mov esi, S ;
	mov ecx, lenSoct ; setam numarul de pasi pentru ciclare
	copiere:
		movsb ; mutam octetul de la DS:ESI la ES:EDI
	loop copiere ; copiem sirul S in D pentru a lucra pe el

	mov ecx, lenSoct
	dec ecx 
	clc

	jecxz sfSortare
	executaSortare:
		mov [st], byte 1 
						 
		mov ebx, 0 ; in ebx vom tine numarul de elemente parcurse
		mov esi, D 
		mov edi, D + 1 
					   
		cicluSortare:
			cmpsb ; comparam elementul curent cu cel urmator
			jbe interschimbare ; interschimbam in caz de nerespectare a ordinii descrescatoare
			jmp sfInterschimbare ; altfel trecem la urmatorul pas
			interschimbare:
				dec esi ; recuperam pozitiile elementelor de interschimbat modificate anterior automat de CMPSB
				dec edi
				lodsb ; AL = elemCurent
				dec esi ; LODSB incrementeaza automat ESI, ceea ce ar perturba interschimbarea
				mov ah, [es:edi] ; AH = elemUrmator
				stosb ; elemUrmator = elemCurent
				dec edi ; STOSB incrementeaza automat EDI, ceea ce ar perturba interschimbarea
				mov [ds:esi], ah ; elemCurent = elemUrmator
				mov [st], byte 0 ; marcam efectuarea a cel putin unei interschimbari
				inc esi
				inc edi
			sfInterschimbare:
			inc ebx
			cmp ebx, ecx ; parcurgem elementele de la primul pana la pozitia lenS - pas - 1 din D 
						 
		jb cicluSortare
		cmp byte [st], 1
	loopne executaSortare ; executam parcurgeri pana cand sirul e sortat sau avem lenS parcurgeri
	sfSortare:

	push   dword 0
	call   [exit]