bits 32 
global  start 

extern  exit
import  exit msvcrt.dll
extern	fopen
import	fopen msvcrt.dll
extern  fread
import 	fread msvcrt.dll
extern 	fprintf
import 	fprintf msvcrt.dll
extern 	printf
import	printf msvcrt.dll
extern 	fclose
import	fclose msvcrt.dll
	; 29.
	; Se da un fisier text.
	; Fisierul contine numere (in baza 10) separate prin spatii.
	; Sa se citeasca continutul acestui fisier,
	; sa se determine maximul numerelor citite
	; si sa se scrie rezultatul la sfarsitul fisierului.

	; EXEMPLE:
	;	! fisierul trebuie incheiat cu inca un caracter precum spatiu, deoarece fread nu va citi ultimul caracter
	;	! rezolvarea se aplica numerelor intregi fara semn ce incap pe 32 biti (intervalul [0, 4294967295]),
	;	  si separate in fisier prin spatiu
	;	! in cazul in care nu exista numere in fisier, va rezulta scrierea valorii 0
	;
	; 1. 50 29 63 
	;	 => 63
	;
	; 2. 817530917 580320933 903540007 832752132 654861577 731412330 742337256 
	;	 => 903540007
segment  data use32 class=data
	; mesaje in caz de eroare la utilizarea functiilor sistem
	eroare_deschidere db "Eroare la deschiderea fisierului",0
	eroare_citire db "Eroare la citirea din fisier",0
	eroare_scriere db "Eroare la scrierea in fisier",0

	; descriptori pentru scrierea in fisier cu fprintf
	format_scriere_caracter db "%c",0
	format_scriere_numar db "%u",0

	; locul unde vom salva identificatorul fisierului
	identificator resd 1

	; numele fisierului inclusiv terminatorul de extensie
	nume_fisier db "lab8ex29.txt",0

	; descriptor pentru modul de deschidere a fisierului cu fopen
	mod_citire_adaugare db "a+",0

	; datele problemei
	continut_fisier times 41h db 0
	nr_curent resd 1
	nr_maxim dd 0h

segment  code use32 class=code
start:
	; STRATEGIE
	; 1. Deschidem fisierul pentru citire si scriere cu adaugare la final
	;
	; 2. Citim cate maxim 64 octeti pana cand am ajuns la finalul fisierului
	;
	; 3. Parcurgem de fiecare data octetii cititi si formam pe rand numerele din cifrele citite,
	;	 memorand in permanenta valoarea maxima pana in prezent si actualizand-o, daca este necesar,
	;	 la intalnirea unui spatiu (cand am terminat de format un numar)
	;
	; 4. Scriem (implicit la finalul fisierului) maximul, si inca un spatiu pentru consecventa in formatul datelor
	;
	; 5. Inchidem fisierul

	push mod_citire_adaugare
	push nume_fisier
	call [fopen] ; deschidem fisierul pentru citire si adaugare
	add esp, 4*2 ; eliberam parametrii procedurii fopen de pe stiva
	cmp eax, 0
	je eroare_file
	mov [identificator], eax ; salvam identificatorul fisierului in caz ca nu a intervenit o eroare
	mov [nr_curent], dword 0


	citire_octeti:
		mov eax, [identificator]
		push eax
		push dword 40h
		push dword 1h
		push continut_fisier
		call [fread] ; apelam fread, citind in continut_fisier octet cu octet, cu limita maxima de 64
		add esp, 4*4

		cmp eax, byte 0h ; verificam daca am ajuns la finalul fisierului,
						 ; acesta fiind punctul de iesire din blocul repetitiv de parcurgere citire_octeti
		je final_fisier

		mov ecx, eax ; in eax avem numarul de octeti cititi
		mov esi, continut_fisier
		cld
		calcul_max_numere:
			lodsb ; parcurgem octetii cititi
			cmp al, ' ' ; daca octetul e spatiu, avem un numar format complet
			je final_numar
			sub al, '0'
			mov ebx, 0
			mov bl, al
			mov eax, [nr_curent]
			mov edx, 0Ah
			mul edx
			add eax, ebx ; altfel daca e caracter cifra, obtinem cifra
						 ; si lipim cifra la numarul format
			mov [nr_curent], eax ; actualizam numarul format
			jmp continuare

			final_numar:
			mov eax, [nr_maxim]
			cmp [nr_curent], eax
			ja nou_maxim ; comparam numarul format cu maximul si actualizam maximul daca este nevoie
			mov [nr_curent], dword 0 ; resetam pentru a forma urmatorul numar
			jmp continuare

			nou_maxim:
			mov eax, [nr_curent]
			mov [nr_maxim], eax
			mov [nr_curent], dword 0 ; resetam pentru a forma urmatorul numar

			continuare:
		loop calcul_max_numere
	jmp citire_octeti

	final_fisier:
	mov eax, [nr_maxim]
	push eax
	mov eax, format_scriere_numar
	push eax
	mov eax, [identificator]
	push eax
	call [fprintf] ; scriem, cu fprintf, valoarea maxima la finalul fisierului,
				   ; specificand format %u pentru intreg fara semn
	add esp, 4*3
	cmp eax, 0
	jl eroare_write ; fprintf va returna in eax o valoare negativa daca a intervenit o eroare

	mov eax, ' '
	push eax
	mov eax, format_scriere_caracter
	push eax
	mov eax, [identificator]
	push eax
	call [fprintf] ; scriem si un spatiu la finalul fisierului,
				   ; specificand format %c pentru caracter
	add esp, 4*3 ; eliberam parametrii procedurii fprintf de pe stiva
	cmp eax, 0
	jl eroare_write

	mov eax, [identificator]
	push eax
	call [fclose] ; inchidem fisierul cu fclose folosind identificatorul
	add esp, 4
	jmp final

	; scriem mesaje de eroare corespunzatoare la iesirea standard (consola) daca este nevoie
	eroare_file:
	push eroare_deschidere
	call [printf]
	add esp, 4
	jmp final

	eroare_read:
	push eroare_citire
	call [printf]
	add esp, 4
	jmp final

	eroare_write:
	push eroare_scriere
	call [printf]
	add esp, 4

	final:
	push   dword 0
	call   [exit]