bits 32 
global  start 

extern  exit
import  exit msvcrt.dll
extern 	printf
import	printf msvcrt.dll
	; 3.
	; Se dau doua numere naturale a si b
	; (a, b: dword, definite in segmentul de date).
	; Sa se calculeze suma lor si sa se afiseze in urmatorul format:
	; "<a> + <b> = <result>"
	; Exemplu: "1 + 2 = 3"
	; Valorile vor fi afisate in format decimal (baza 10) cu semn.

	; EXEMPLE:
	; 1. a dw 0FFFEh b dw 60h
	;	 => -2 + 96 = 94
	;
	; 2. a dw 30h b dw 60h
	;	 => 48 + 96 = 144
	;
	; 3. a dw 0FFF2h b dw 0h
	;	 => -14 + 0 = -14

segment  data use32 class=data
	; datele problemei si un loc unde se va stoca rezultatul sumei
	a dw 0FFFEh
	b dw 60h
	rez resd 1

	; date auxiliare necesare la convertire si afisare
	plus db " + ", 0
	egal db " = ", 0
	nr resd 1
	rev resd 1
	sign resb 1
	aux times 8 db 0

	; siruri in care se vor converti cele trei numere la string
	a_str times 10 db 0
	b_str times 10 db 0
	r_str times 10 db 0

segment  code use32 class=code
	; STRATEGIE
	; 1. Calculul sumei
	; 2. Convertim a, b si rezultatul la string-uri (siruri de caractere)
	;		etapele conversiei:
	;		i)	impartim succesiv numarul la 10 si convertim resturile la caracterele corespunzatoare
	;		ii)	pe acest sir de caractere, il inversam si il prefixam cu semnul corespunzator
	; 3. Afisam a, b, rezultatul si delimitatori intre ei (+, =)

	; Procedura: numar_to_str(revenire, destination, number)
	;
	; * parametri si locatia lor pe stiva:
	;		ESP		- revenire: adresa de revenire
	;		ESP + 4 - destination: adresa inceputului sirului de destinatie
	;		ESP + 8 - number: numarul de convertit
	;
	; * rezultat: transpune number intr-un sir de caractere la adresa destination
	numar_to_str:
		; luam parametrii de pe stiva
		mov eax, [ESP]
		mov [rev], eax ; rev = adresa de revenire in program

		mov edi, aux ; convertirea initiala in ordine inversa a cifrelor se va face intr-un sir auxiliar,
					 ; pe care il vom inversa ulterior in cel de destinatie
		mov eax, [ESP + 8]
		mov [nr], eax ; nr = numarul de convertit

		cmp [nr], dword 0
		jl semn_negativ

		semn_pozitiv:
			mov [sign], byte ' ' ; in cazul unui numar pozitiv, nu este necesar sa afisam semnul +
			jmp convertire
		semn_negativ:
			mov [sign], byte '-'
			mov eax, [nr] ; in cazul unui numar negativ, salvam semnul - si calculam modulul numarului
						  ; metoda utilizata aici pentru calcularea modulului implica operatii pe biti si
						  ; este cea utilizata de catre procedura abs( ) din C:
						  ; 	abs(x) = (x XOR y) - y, unde y = x >>> 31 (pe 31 biti) (>>> = shiftare la dreapta pe biti)
			mov ebx, eax
			sar ebx, 1Fh
			xor eax, ebx
			sub eax, ebx
			mov [nr], eax ; salvam modulul calculat

		convertire:
			mov eax, [nr]
			push eax
			pop ax
			pop dx ; punem deimpartitul in DX:AX
			mov cx, 0Ah
			idiv cx ; impartim la 10
			mov cl, dl ; DL = nr%10, AL = nr/10
			cwde
			mov [nr], eax ; salvam catul pentru urmatorul pas
			mov al, cl
			add al, '0' ; traducem cifra in caracter si il punem in sirul auxiliar
			stosb
			cmp [nr], dword 0 ; pana cand am epuizat cifrele
		jne convertire

		mov ecx, edi
		sub ecx, aux ; calculam cate cifre are numarul

		mov edi, [ESP + 4] ; pregatim inversarea sirului auxiliar in cel de destinatie
		mov esi, aux
		dec esi ; ECX va juca rol dublu ca numar de cifre ramase si ca pozitie ulterioara cifrei curente in auxiliar
		cld ; vom parcurge sirul destinatie de la stanga la dreapta, iar pe cel auxiliar in ordine inversa

		cmp [sign], byte '-'
		jne finalizare ; dorim sa afisam semnul unui numar doar daca acesta este negativ
		mov al, [sign]
		stosb
		finalizare:
			mov al, [esi + ecx]
			stosb
		loop finalizare
	jmp [rev]

start: 
	; Calculam suma
	mov ax, [b]
	cwde
	mov ebx, eax
	mov ax, [a]
	cwde
	add eax, ebx
	mov [rez], eax ; calculam la nivel de dword pentru a evita o eventuala depasire

	; Convertim a la string
	mov ax, [a]
	cwde
	push eax ; punem, conform conventiei CDECL, parametrii procedurii numar_to_str pe stiva
	mov edi, a_str
	push edi
	push revenire_a_str
	jmp numar_to_str

	revenire_a_str:
	add esp, 4*3 ; resetam stiva

	; Convertim b la string
	mov ax, [b]
	cwde
	push eax
	mov edi, b_str
	push edi
	push revenire_b_str
	jmp numar_to_str

	revenire_b_str:
	add esp, 4*3

	; Convertim rezultatul la string
	mov eax, [rez]
	push eax
	mov edi, r_str
	push edi
	push final_conv
	jmp numar_to_str

	final_conv:
	add esp, 4*3

	; Afisam
	push a_str ; punem pe stiva parametrul procedurii printf, adresa sirului de afisat
	call [printf]
	add esp, 4 ; resetam stiva

	push plus ; afisam "+" intre numere
	call [printf]
	add esp, 4

	push b_str
	call [printf]
	add esp, 4

	push egal ; afisam "=" inaintea rezultatului
	call [printf]
	add esp, 4

	push r_str
	call [printf]
	add esp, 4

	push   dword 0
	call   [exit]