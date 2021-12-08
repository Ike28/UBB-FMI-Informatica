bits 32 ;asamblare si compilare pentru arhitectura de 32 biti
; definim punctul de intrare in programul principal
global  start 

extern  exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import  exit msvcrt.dll; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante
segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
	a db 5
	b db 9
	c db 6
	d db 80

	A dw 5
	B dw 9
	C dw 6
	D dw 80

	e dw 300
	g dw 306
	h dw 6

segment  code use32 class=code ; segmentul de cod
start: 
	; ex simple 23: 256*1
	mov AX,100h ; 2^16 > 256 > 255 => ne trebuie word
	mov BX,1h
	mul BX ; rezultatul este in DX:AX = 0000:0100h

	; adunari/scaderi 1: c-(a+d)+(b+d)
	; a,b,c,d byte
	mov AL,[c]
	mov AH,[a]
	add AH,[d]
	sub AL,AH
	add AL,[b]
	add AL,[d] ; rezultatul este in AL = 10d = 0Ah

	; adunari/scaderi 24: (a-c)+(b-d)
	; A,B,C,D word
	mov AX,[A]
	sub AX,[C]
	mov BX,[B]
	sub BX,[D]
	add AX,BX ; rezultatul este in AX = -72 = 1111 1111 1011 1000b = FFB8h

	; inmultiri/impartiri 28 part 1: d+10*a-b*c
	; a,b,c - byte, d - word
	mov AL,10
	mul byte [a]
	add AX,[D]
	mov BX,AX
	mov AL,[b]
	mul byte [c]
	sub BX,AX
	mov AX,BX ; rezultatul este in AX = 004Ch

	; inmultiri/impartiri 28 part 2: (e+g-h)/3+b*c
	; a,b,c,d-byte, e,f,g,h-word
	mov AX,[e]
	add AX,[g]
	sub AX,[h]
	mov BL,3
    div BL
	mov AH,0
	mov BX,AX
	mov AL,[b]
	mul byte [c]
	add AX,BX ; rezultatul este in AX = 254d = 00FEh

	push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului