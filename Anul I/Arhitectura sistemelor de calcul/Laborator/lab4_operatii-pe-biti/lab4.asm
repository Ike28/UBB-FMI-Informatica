bits 32 
global  start 

extern  exit
import  exit msvcrt.dll

segment  data use32 class=data
    A dq 0FFFFFFFFFFC2F800h

    ; Fie A = 11111111 11111111 11111111 11111111 11111111 11000010 11111000 00000000
    ;                             ---            |                                   |
    ;                              N             |  rotire spre dreapta N poz------> |
    ;                                            |00000001 11111111 10000101 11110000|
    ;                                            |<-------------B------------------->|
    ;                                                          ----     ----
    ;                                                            C       C

    N resb 1
    B resd 1
    C resb 1
segment  code use32 class=code
start:
	; Se da quadwordul A.
	; a) Sa se obtina numarul intreg N reprezentat de bitii 35-37 ai lui A. 
	; b) Sa se obtina apoi in B dublucuvantul rezultat prin rotirea spre dreapta a dublucuvantului inferior al lui A cu N pozitii.
	; c) Sa se obtina octetul C astfel:
	; 	* bitii 0-3 ai lui C sunt bitii 8-11 ai lui B
	; 	* bitii 4-7 ai lui C sunt bitii 16-19 ai lui B

	mov eax, dword [A+0]
	mov edx, dword [A+4] ; EDX:EAX = A

	; a)
	mov ecx, 38h ; in ECX va fi masca pentru a lua prin izolare bitii 35-37 a lui A =  bitii 3-5 ai lui EDX
				 ; ECX = 0..0011 1000
	and edx, ecx ; izolam bitii doriti
	shr edx, 3h ; mutam acei biti la pozitiile low
	mov [N], dl ; rezultatul este format din 3 biti, deci cel mai low octet din EDX va fi N-ul dorit
				; N-ul dorit este in DL = 0000 0111 = 07h
    
    ; b)
    mov cl, [N] ; pregatim operandul pentru rotire
	ror eax, cl ; dwordul inferior al lui A este in EAX
	mov [B], eax ; B-ul dorit este in EAX = 00000001 11111111 10000101 11110000 = 01FF85F0h

	; c)
	mov edx, [B]
	mov ecx, 0F00h ; in ECX va fi masca binara pentru a lua bitii 8-11 ai lui EDX = B prin izolare
				   ; ECX = 0... 1111 0000 0000
	and edx, ecx ; izolam bitii doriti
	ror edx, 8h ; aducem acei biti la pozitiile 0-3 pentru a forma nibble-ul low din C
	mov eax, edx ; EAX contine nibble-ul low al lui C

	mov edx, [B]
	mov ecx, 0F0000h ; in ECX va fi masca binara pentru a lua bitii 16-19 ai lui EDX = B prin izolare
					 ; ECX = 0... 1111 0000 0000 0000
	and edx, ecx ; izolam bitii doriti
	ror edx, 0Ch ; aducem acei biti la pozitiile 4-7 pentru a forma nibble-ul high din C
				 ; incep de la pozitia 16, deci ii vom roti spre dreapta cu 12 pozitii
				 ; EDX contine nibble-ul high al lui C
	add eax, edx ; EDX si EAX fiecare contin cate un nibble, disjuncte intre ele ca pozitii, deci adunandu-i vom forma exact C
				 ; rezultatul este in EAX = 11110101 = F5h

	mov [C], eax
	
	push   dword 0
	call   [exit]