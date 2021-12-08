bits 32 
global  start 

extern  exit
import  exit msvcrt.dll
	; 9.
	; Se da un sir de octeti S de lungime l.
	; Sa se construiasca sirul D de lungime l-1 astfel incat
	; elementele din D sa reprezinte diferenta dintre fiecare 2 elemente consecutive din S
segment  data use32 class=data
	S db 1,2,5,10,15,20,40 ; DS:01|02|05|0A|0F|14|32 (hex)
	lenS equ $-S
	lenD equ lenS-1
	D times lenD db 0 ; DS:01|02|05|0A|0F|14|32|00|00|00|00|00|00 (hex)
					;	|<---------S-------->|<-------D------->|
segment  code use32 class=code
start:
	; Strategie:
	;
	; 	pentru esi = 0,lenS-1
	;	|	elementul curent din S este la adresa s+esi
	;	|	elementul urmator din S este la adresa s+esi+1
	;	|	elementul curent din D este la adresa d+esi
	;	|	fie dif = elementul urmator din S - elementul curent din S
	;	|	elementul curent din D devine dif
	;	|_[]
	;
	mov esi, 0 ; initializam esi cu offsetul primului element din S fata de adresa lui S
	repeta:
		mov al, [S + esi] ; AL <- elementul curent din S
		mov bl, [S + esi + 1] ; BL <- elementul urmator din S
		sub bl, al
		mov [D + esi], bl ; adaugam la D rezultatul diferentei
		inc esi ; trecem la offsetul urmatorului element din S
		cmp esi, lenD ; setam flagurile pentru utilizarea instructiunilor de salt conditionat,
					; prin efectuarea fictiva esi - (l-1)
	jb repeta ; daca rezultatul lui CMP a fost negativ (esi < l-1), repetam pasii
	;	rezultatul este in segmentul de date (in hex dump in debugger):
	;	[DS:D]: 01|03|05|05|05|14 (hex)
	
	push   dword 0
	call   [exit]