bits 32 
global  _toHex 

extern 	_printf

segment  data use32 class=data
	specificator_hex_char db "%c",0
	hexa_digits db '0123456789ABCDEF'
segment  code use32 class=code

	; Procedura: toHex(numar)
	;
	; * parametri si locatia lor pe stiva:
	;		ESP + 8 - numar: numarul intreg fara semn pe 32 biti, care va fi transformat in reprezentarea hexa
	;
	; * rezultat: afiseaza, la iesirea standard, reprezentarea hexa a numarului

_toHex:
	
	; STRATEGIE
	; * Daca numarul este 0, afisam un singur 0
	; * Altfel, parcurgem de la dreapta la stanga bitii din reprezentarea binara pe 32 biti a numarului, in grupuri de cate 4
	; 	(1 grup de 4 cifre binare = o cifra hexa):
	;		1. Eliminam (ignoram in afisare) toate cifrele hexa din fata numarului
	;		2. Incepand cu prima cifra nenula gasita, obtinem codul ASCII si il afisam
	;	pana cand am parcurs 8 cifre hexa (32 biti) total

	push ebp ; creeare cadru de stiva
	mov ebp, esp
	mov edx, [ebp + 8] ; EDX = numar
	pushad ; salvam valoarea registrilor generali pe stiva

	cmp edx, 0 ; daca numarul e 0, afisam un singur 0 si iesim din functie
	je afisare_zero

	mov ecx, 8 ; setam numarul maxim de cifre pentru transformarea unui numar pe 32 biti in hexa
	eliminare_zero:
		mov ebx, ecx
		mov ecx, 4 ; setam numarul de pasi pentru calcularea cifrei hexa din binar
		mov eax, 0 ; in AL vom pune cate un grup de 4 cifre binare (= o cifra hexa)
		grupare_zero:
			shl al, 1 ; facem loc pentru un nou bit
			shl edx, 1 ; CF = bitul urmator (de la stanga la dreapta) din numar
			adc al,0 ; adaugam bitul la coada grupului
		loop grupare_zero
		mov ecx, ebx ; restauram contorul pentru cifrele numarului

		cmp eax, 0
	loope eliminare_zero ; ignoram toate cifrele hexa egale cu 0 de la inceputul numarului

	afisare_cifre:  ; incepand cu prima cifra hexa nenula, afisam pana cand am trecut, in total, prin 8 cifre hexa
		mov ebx, hexa_digits
		xlat ; AL = BX + AL (codul ASCII al cifrei AL din tabela de cifre hexa)
		push ecx
		push eax
		push specificator_hex_char
		call _printf

		add esp, 4 * 2 ; eliberam parametrii procedurii printf de pe stiva

		mov ecx, 4 ; setam numarul de pasi pentru calcularea cifrei hexa din binar
		mov eax, 0 ; in AL vom pune cate un grup de 4 cifre binare (= o cifra hexa)
		grupare:
			shl al, 1 ; facem loc pentru un nou bit
			shl edx, 1 ; CF = bitul urmator (de la stanga la dreapta) din numar
			adc al,0 ; adaugam bitul la coada grupului
		loop grupare
		pop ecx ; restauram contorul pentru cifrele numarului
	loop afisare_cifre
	jmp final

	afisare_zero:
		mov eax, 0
		add eax, '0' ; punem in EAX codul ASCII pentru 0
		push eax
		push specificator_hex_char
		call _printf

		add esp, 4 * 2 ; eliberam parametrii procedurii printf de pe stiva

	final:
	popad ; restauram valorile initiale ale registrilor
	mov esp, ebp
	pop ebp ; restauram cadrul stivei
	ret
