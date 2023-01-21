bits 32 
global  start 
	; EXAMEN PRACTIC 12.01.2022
	;
	; Se citeste de la tastatura numele unui fisier si un sir de caractere care contine
	; litere mari si mici, spatii si cifre. Sa se scrie in fisierul cu numele citit de la
	; tastatura sirul de caractere modificat astfel:
	; *	cifrele incrementate cu o unitate
extern  exit
import  exit msvcrt.dll
extern 	fopen
import  fopen msvcrt.dll
extern  fprintf
import 	fprintf msvcrt.dll
extern  fclose
import  fclose msvcrt.dll
extern  printf
import  printf msvcrt.dll
extern  scanf
import  scanf msvcrt.dll

segment  data use32 class=data
	format_citire db "%s",0
	nume_fisier resb 20
	mod_acces_fisier db "a",0
	descriptor resd 1
	linie_noua db 13,10,0
	eroare db "Eroare la deschiderea fisierului",0
	sir resb 30
segment  code use32 class=code
start: 
	; citim numele fisierului
	push nume_fisier
	push format_citire
	call [scanf]
	add esp, 4 * 2

	; citim sirul de caractere
	push sir
	push format_citire
	call [scanf]
	add esp, 4 * 2

	; parcurgem sirul si suprascriem cifrele cu succesoarele lor
	mov esi, sir
	mov edi, sir
	cld
	modif_sir:
		lodsb
		; in caz de final al sirului, oprim ciclarea
		cmp al, 0
		je final_modif
		cmp al, '0'
		jb continuare
		cmp al, '9'
		ja continuare
		inc al

		continuare:
		stosb
	jmp modif_sir
	final_modif:

	; deschidem fisierul pentru append
	push mod_acces_fisier
	push nume_fisier
	call [fopen]
	add esp, 4 * 2

	; verificam deschiderea cu succes
	cmp eax, 0
	je eroare_deschidere
	mov [descriptor], eax

	; adaugam o linie noua in fisier
	push linie_noua
	push format_citire
	push dword [descriptor]
	call [fprintf]
	add esp, 4 * 3

	; scriem sirul la finalul fisierului
	push sir
	push format_citire
	push dword [descriptor]
	call [fprintf]
	add esp, 4 * 3

	; inchidem fisierul deschis
	push descriptor
	call [fclose]
	add esp, 4
	jmp final

	; in caz de eroare la deschidere, afisam un mesaj in iesirea standard
	eroare_deschidere:
	push eroare
	push format_citire
	call [printf]
	add esp, 4 * 2

	final:
	push   dword 0
	call   [exit]
