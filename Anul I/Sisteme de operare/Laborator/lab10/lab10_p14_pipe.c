//	* Clientul ii transmite serverului un nume de fisier si un numar octal.
//	* Serverul va verifica daca fisierul respectiv are drepturi de acces diferite de numarul indicat.
//		- daca drepturile coincid, va transmite mesajul "Totul e OK!"
//		- altfel, va seta drepturile conform numarului indicat si va transmite mesajul "Drepturile au fost modificate."

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int c2s[2];
	int s2c[2];
	int rez = pipe(c2s);
	if(rez == -1)
	{
		perror("pipe() error: ");
		exit(1);
	}
	rez = pipe(s2c);
	if(rez == -1)
	{
		perror("pipe() error: ");
		exit(1);
	}
	int drepturi = 0;
	printf("Introduceti drepturile in octal: ");
	rez = scanf("%o",&drepturi);
	if(rez != 1)
	{
		printf("Eroare : Numarul introdus nu este in baza 8!\n");
		exit(1);
	}
	char* nume_fisier=(char*)malloc(20*sizeof(char));
	printf("Introduceti numele fisierului: ");
	scanf("%s",nume_fisier);
	
	pid_t pid= fork();
	if(pid == -1)
	{
		perror("fork() error: ");
		exit(1);
	}
	if(pid == 0)
	{
		close(c2s[1]);
		close(s2c[0]);
		int rights = 0;
		char* filename=(char*)malloc(20*sizeof(char));
		read(c2s[0],&rights,sizeof(int));
		read(c2s[0],filename,20*sizeof(char));
		
		char* mesaj=(char*)malloc(35*sizeof(char));
		struct stat buffer;
		int res = stat(filename, &buffer);
		if(res == -1)
		{
			printf("Eroare: Fisierul dat nu exista!\n");
			exit(1);
		}
		int statchmod = buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
		if(statchmod == rights)
		{
			strcpy(mesaj,"Totul e OK!");
		}
		else
		{
			int res = chmod(filename,rights);
			if(res == -1)
			{
				printf("Eroare la modificarea drepturilor!\n");
				exit(1);
			}
			strcpy(mesaj,"Drepturile au fost modificate.");
		}
		
		write(s2c[1],mesaj,35*sizeof(char));
		close(c2s[0]);
		close(s2c[1]);
		free(filename);
		free(mesaj);
		exit(0);
	}
	else
	{
		close(s2c[1]);
		close(c2s[0]);
		write(c2s[1],&drepturi,sizeof(int));
		write(c2s[1],nume_fisier,20*sizeof(char));
		int status;
		wait(&status);
		
		if(WEXITSTATUS(status) == 1)
		{
			exit(1);
		}
		
		char* mesaj=(char*)malloc(35*sizeof(char));
		read(s2c[0],mesaj,35*sizeof(char));
		printf("%s\n",mesaj);
		close(c2s[1]);
		close(s2c[0]);
		free(mesaj);
		free(nume_fisier);
	}
	return 0;
}
