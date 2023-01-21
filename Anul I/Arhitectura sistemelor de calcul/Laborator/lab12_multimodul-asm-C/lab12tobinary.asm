bits 32 
global  _toBinary 

extern 	_printf

segment  data use32 class=data
	specificator db "%c",0
segment  code use32 class=code

	; Procedura: toBinary(numar)
	;
	; * parametri si locatia lor pe stiva:
	;		ESP + 8 - numar: numarul intreg fara semn pe 32 biti, care va fi transformat in reprezentarea binara
	;
	; * rezultat: afiseaza, la iesirea standard, reprezentarea binara a numarului

_toBinary:

	; STRATEGIE
	; * Daca numarul este 0, afisam un singur 0
	; * Altfel, parcurgem de la dreapta la stanga bitii din reprezentarea binara pe 32 biti a numarului, unul cate unul:
	;		1. Eliminam (ignoram in afisare) toti bitii 0 din fata numarului
	;		2. Incepand cu primul bit egal cu 1 gasit, obtinem codul ASCII si il afisam
	;		3. Eliminam bitul afisat din numar
	;	pana cand numarul devine 0

	push ebp ; creeare cadru de stiva
	mov ebp, esp
	pushad ; salvam valoarea registrilor generali pe stiva

	mov eax, [ebp + 8] ; EAX = numar
	clc
	mov ebx, 0
	mov ecx, 0 ; daca numarul dat este 0, afisarea va avea un singur pas
	cmp eax, 0
	je afisare_cifre
	mov ecx, 32 ; setam numarul de cifre pentru reprezentarea unui numar pe 32 biti

	eliminare_zerouri:
		shl eax, 1
		mov ebx, 0
		adc ebx, 0 ; EBX va contine bitul high din EAX
		cmp ebx, 0
	loope eliminare_zerouri ; afisarea nu va avea loc pana cand identificam cel mai high bit 1

	afisare_cifre:
		add ebx, '0' ; pregatim valoarea ASCII a valorii din EBX
		push ecx
		push ebx
		push specificator
		call _printf

		add esp, 4 * 2 ; eliberam parametrii procedurii printf de pe stiva

		pop ecx
		mov ebx, 0
		shl eax, 1
		adc ebx, 0 ; EBX va contine urmatorul bit (de la stanga la dreapta) din reprezentarea binara
	loop afisare_cifre ; incheiem afisarea cand am parcurs toti cei 32 biti ai numarului

	final:

	popad ; restauram valorile initiale ale registrilor
	mov esp, ebp
	pop ebp ; restauram cadrul stivei
	ret
