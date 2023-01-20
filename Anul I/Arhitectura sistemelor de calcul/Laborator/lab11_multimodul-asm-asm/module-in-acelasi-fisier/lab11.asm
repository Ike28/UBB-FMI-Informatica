bits 32 
global  start 

extern  exit
import  exit msvcrt.dll
extern 	scanf
import 	scanf msvcrt.dll
	; 2. Se cere sa se citeasca de la tastatura un sir de numere,
	; date in baza 10 ca numere cu semn
	; (se citeste de la tastatura un sir de caractere
	; si in memorie trebuie stocat un sir de numere).
	;
	; *	Numerele se considera reprezentate pe 32 biti fara semn,
	; iar sirurile de caractere de pana la 100 de caractere (sirul propriu-zis)
	; si incheiate cu caracterul '\n'

	; EXEMPLE
	; 
	; 1. 78 400 99\n
	;
	;	=> DS:sir_numere(0040106C):
	;	 0000004Eh, 00000190h, 00000063h
	;
	; 2. 78 -400 -99 -1\n
	;
	;	=> DS:sir_numere:
	;	 0000004Eh, FFFFFE70h, FFFFFF9Dh, FFFFFFFFh
	;
	; 3. -1 -1 -1 0 0 -0\n
	;
	;	=> DS:sir_numere:
	;	 FFFFFFFFh, FFFFFFFFh, FFFFFFFFh, 00000000h, 00000000h, 00000000h
segment  data use32 class=data
	format_sir db "%[^\n]",0
	sir_caract times 101 db 0
	sir_numere times 51 dd 0
	numar_curent resd 1
	coef resd 1
segment  code use32 class=code
	; STRATEGIE
	; 1. Citim octeti cu scanf pana la intalnirea caracterului newline '\n'
	; 2. Parcurgem octetii cititi unul cate unul si incepem formarea numerelor,
	;	 pornind cu un numar curent 0
	;	
	;	daca octetul curent este:
	; 	* caracter cifra: obtinem cifra si o alipim la numarul curent
	;	* minus: stabilim un coeficient -1 cu care vom inmulti numarul dupa formare
	;	* spatiu: am terminat formarea unui numar si il adaugam in sirul final
	;	* caracterul zero: incheiem parcurgerea si adaugam numarul curent in sirul final

	; Procedura: transform(destinatie, sursa)
	;
	; * parametri si locatia lor pe stiva:
	;		ESP + 4 - destinatie: adresa inceputului sirului unde vom plasa numerele
	;		ESP + 8 - sursa: adresa inceputului sirului octetilor cititi
	;
	; * rezultat: stocheaza in sirul de destinatie intregii dword cu semn cititi
transform:
	mov esi, [ESP + 8]
	mov edi, [ESP + 4]
	cld ; setam directia de parcurgere
	parcurgere:
		mov [numar_curent], dword 0 ; incepem formarea noului numar de la 0
		mov [coef], dword 1 ; cu coeficient pozitiv
		mov eax, 0

		formare_numar:
			lodsb ; incarcam octetul
			cmp al, '-'
			je minus ; modificam coeficientul in caz de numar negativ
			cmp al, ' '
			je sfformare_numar ; finalizam formarea numarului la intalnirea unui spatiu
			cmp al, 0
			je sf_parcurgere ; incheiem parcurgerea de octeti la intalnirea caracterului terminator

			sub al, '0' ; convertim la cifra
			mov bl, al
			mov ax, [numar_curent]
			mov dx, [numar_curent + 2]
			mov ecx, 0Ah
			imul ecx ; inmultim numarul format pana acum cu 10
			add al, bl ; si adaugam cifra curenta

			mov [numar_curent], eax
			jmp continuare

			minus:
				mov [coef], dword -1
			continuare:
		jmp formare_numar
		sfformare_numar:

		mov ax, [numar_curent]
		mov dx, [numar_curent + 2]
		mov ebx, [coef]
		imul ebx ; inmultim cu coeficientul de semn
		stosd ; stocam numarul nou format in sirul de destinatie
	jmp parcurgere

	sf_parcurgere:
	mov ax, [numar_curent]
	mov dx, [numar_curent + 2]
	mov ebx, [coef] ; stabilim semnul si pentru ultimul numar format pana la intalnirea caracterului 0
	imul ebx
	stosd ; stocam ultimul numar format

	ret ; returnam din procedura inapoi in cod

start: 
	push dword sir_caract
	push dword format_sir
	call [scanf] ; apelam scanf pentru a citi octetii de la intrarea standard

	push dword sir_caract
	push dword sir_numere
	call transform ; apelam procedura transform pentru a stoca numerele
	push   dword 0
	call   [exit]