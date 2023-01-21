#include <stdio.h>
/*	; 4. Se da un sir de numere. Sa se afiseze valorile in baza 16 si in baza 2.
	;
	; *	Numerele se considera reprezentate pe 32 biti fara semn
	; * Se da inseamna ca acele date pot fi puse direct in segmentul de date
	; EXEMPLE
	; 
	; 1. v[] = {1, 2, 3, 4, 5};
	;
	;	=> 1: 1 1
	;	   2: 10 2
	;	   3: 11 3
	;	   4: 100 4
	;	   5: 101 5
*/
void toHex(int);
void toBinary(int);

int main() {
	int v[] = {1, 2, 3, 4, 5};

	for(int i=0; i<5; i++) {
		printf("%d: ", v[i]);
		toBinary(v[i]);
		printf("%s", " ");
		toHex(v[i]);
		printf("%s\n", "");
	}
}