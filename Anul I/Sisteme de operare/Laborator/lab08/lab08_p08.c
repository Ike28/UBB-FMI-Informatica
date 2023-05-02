//	Se cere sa se elimine numerele pare dintr-un fisier. 
//	Numele fisierului se va transmite programului ca si parametru in linia de comanda. 
//	Programul va modifca acel fisier si nu va afisa nimic la iesirea standard.

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	if(argc < 2) {
		printf("Parametrii insuficienti.\n");
		return 1;
	}
	
	char filename[100];
	strcpy(filename, argv[1]);

	FILE* fisier = fopen(filename, "r");

	if(fisier == NULL){
		printf("Fisierul nu a putut fi deschis.\n");
		return 1;
	}

	int numere[100], dim=0, nrCurent;
	while(fscanf(fisier, "%d", &nrCurent) != EOF){
		if(nrCurent%2 == 1){
			numere[dim] = nrCurent;
			dim++;
		}
	}
	fclose(fisier);

	fisier = fopen(filename, "w");

	int i;
	for(i=0; i < dim; i++)
		fprintf(fisier, "%d\n", numere[i]);
	return 0;
}
