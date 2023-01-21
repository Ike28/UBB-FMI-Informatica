bits 32 
global  transform 

extern  exit
import  exit msvcrt.dll

segment  data use32 class=data
	numar_curent resd 1
	coef resd 1
segment  code use32 class=code

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

	
	push   dword 0
	call   [exit]