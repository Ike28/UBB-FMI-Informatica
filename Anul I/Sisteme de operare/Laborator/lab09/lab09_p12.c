//	Să se calculeze suma unui șir de numere folosind metoda divide et impera: 
//		- un proces împarte șirul în două subșiruri, pe care le dă altor două procese (fii) să le calculeze suma
//		- după care adună cele două rezultate obținute. 
//		- procesele fii aplică în continuare aceeași tehnică.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int suma_recursiva(int stanga, int dreapta, int* v){
	if(stanga == dreapta)
		return v[dreapta];
	int mijloc=(stanga+dreapta)/2;
	pid_t child_stanga, child_dreapta;
	child_stanga =  fork();

	if(child_stanga==-1){
		perror("fork() error: ");
		exit(EXIT_FAILURE);
	}
	if(child_stanga==0){
		//printf("*** Copil stanga: id=%d, parinte=%d, [%d,%d]\n ", getpid(),getppid(),stanga,mijloc);
		exit(suma_recursiva(stanga,mijloc,v));
	}
	else
	{
		child_dreapta=fork();
		if(child_dreapta==-1){
			perror("fork() error: ");
			exit(EXIT_FAILURE);
		}
		if(child_dreapta==0){
			//printf("*** Copil dreapta: id=%d, parinte=%d, [%d,%d]\n ", getpid(),getppid(),mijloc+1,dreapta);
			exit(suma_recursiva(mijloc+1,dreapta,v));
		}
		else
		{
			//printf("* Parinte : id=%d\n", getpid());
			int status_s, status_d;
			wait(&status_s);
			wait(&status_d);
			return WEXITSTATUS(status_s)+WEXITSTATUS(status_d);
		}
	}
}
int main(int argc, char** argv){
	int dim=0;
	printf("Introduceti dimensiunea : ");
	scanf("%d",&dim);
	if(dim<1)
	{
		printf("Eroare: Dimensiune nevalida!\n");
		exit(EXIT_FAILURE);
	}
	int* v=(int*)malloc(dim*sizeof(int));
	if (v == NULL){
		printf("Eroare la alocarea memoriei!\n");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i=0;i<dim;i++){
		printf("v[%d]= ",i);
		scanf("%d",&v[i]);
	}
	int suma = suma_recursiva(0,dim-1,v);
	printf("Suma vectorului este %d\n", suma);
	free(v);
	return 0;
}
