bits 32 
global  start 

extern  exit
import  exit msvcrt.dll
	; 15.
	; Se da un sir S de dublucuvinte.
	; Sa se obtina sirul D format din octetii dublucuvintelor din sirul D, 
	; sortati in ordine descrescatoare in interpretarea fara semn.
	;
	; EXEMPLE:
	; 1. S dd 12345607h, 1A2B3C15h
	; 07 56 34 12 15 3C 2B 1A => 56 3C 34 2B 1A 15 12 07
	;
	; 2. S dd 0D5F3E077h, 3FFAF7F2h
	; 77 E0 F3 D5 F2 F7 FA 3F => FA F7 F3 F2 E0 D5 77 3F
	;
	; 3. S dd C8081101h, 0FE45h, 6DAF4EE2h
	; 01 11 08 C8 45 FE 00 00 E2 4E AF 6D => FE E2 C8 AF 6D 4E 45 11 08 01 00 00
segment  data use32 class=data
	S dd 0C8081101h, 0FE45h, 6DAF4EE2h
	lenSoct equ $-S
	D times lenSoct db 0
	st resd 1
segment  code use32 class=code
start: 
	; STRATEGIE:
	; Implementam algoritmul BubbleSort
	;
	;	i=0
	;	executa
	;	|	sortat = true
	;	|	pentru j = 0,lenSoct - i - 1
	;	|	|	elementul curent este la adresa S+j
	;	|	|	elementul urmator este la adresa S+j+1
	;	|	|	daca elemCurent <= elemUrmator
	;	|	|	|	interschimba elemCurent cu elemUrmator
	;	|	|	|	sortat = false
	;	|	|	|_[]
	;	|	|_[]
	;	|	i=i+1
	;	|__cat timp i < lenSoct-1 si sortat = false
	;
	mov edi, D ; setam offsetul sirului destinatie pentru instructiunile de transfer
	mov esi, S ; setam offsetul sirului sursa
	mov ecx, lenSoct ; setam numarul de pasi pentru ciclare
	copiere:
		movsb ; mutam octetul de la DS:ESI la ES:EDI
	loop copiere ; copiem sirul S in D pentru a lucra pe el

	mov ecx, lenSoct
	dec ecx ; setam numarul de pasi pentru ciclare (lenS -1 deoarece vom compara mereu cu elementul urmator)
	clc ; setam directia de parcurgere a sirurilor

	jecxz sfSortare ; nu avem nimic de sortat la un sir gol
	executaSortare:
		mov [st], byte 1 ; st va juca rol de marker boolean:
						 ; daca sirul a fost sortat sau a fost nevoie de interschimbari
		mov ebx, 0 ; in ebx vom tine numarul de elemente parcurse
		mov esi, D     ; --/
		mov edi, D + 1 ; -/ setam pozitiile consecutive in sirul D pentru a folosi la fiecare pas
					   ; instructiunile de comparare a datelor pe elementul curent si cel urmator, 
					   ; si de transfer a datelor in cazul interschimbarii
		cicluSortare:
			cmpsb ; comparam elementul curent cu cel urmator
			jbe interschimbare ; interschimbam in caz de nerespectare a ordinii descrescatoare
			jmp sfInterschimbare ; altfel trecem la urmatorul pas
			interschimbare:
				dec esi ;--/recuperam pozitiile elementelor de interschimbat modificate anterior automat de CMPSB
				dec edi ;-/ 
				lodsb ; AL <- elemCurent
				dec esi ; LODSB incrementeaza automat ESI, ceea ce ar perturba interschimbarea
				mov ah, [es:edi] ; AH <- elemUrmator
				stosb ; elemUrmator <- elemCurent
				dec edi ; STOSB incrementeaza automat EDI, ceea ce ar perturba interschimbarea
				mov [ds:esi], ah ; elemCurent <- elemUrmator
				mov [st], byte 0 ; marcam efectuarea a cel putin unei interschimbari
				inc esi ;--/ trecem la urmatoarea pereche de elemente
				inc edi ;-/
			sfInterschimbare:
			inc ebx ; actualizam numarul de elemente parcurse
			cmp ebx, ecx ; parcurgem elementele de la primul pana la pozitia lenS - pas - 1 din D 
						 ; (restul elementelor pana la capatul lui D sunt sortate)
		jb cicluSortare
		cmp byte [st], 1  ;--/
	loopne executaSortare ;-/ executam parcurgeri pana cand sirul e sortat sau avem lenS parcurgeri
	sfSortare:

	push   dword 0
	call   [exit]