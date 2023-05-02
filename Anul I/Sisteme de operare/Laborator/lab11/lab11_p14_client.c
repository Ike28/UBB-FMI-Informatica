#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/fifopmc"

int main(int argc, char** argv) {
    int drepturi = 0;
    printf("Introduceti drepturile in octal: ");
    int rez = scanf("%o", &drepturi);
    if(rez != 1) {
        printf("Eroare: Numarul introdus nu este in baza 8!\n");
        exit(1);
    }
    
    char* nume_fisier = (char*)malloc(20 * sizeof(char));
    printf("Introduceti numele fisierului: ");
    scanf("%s", nume_fisier);
    
    char* myfifo = FIFO_PATH;
    mkfifo(myfifo, 0666);
    
    int fd = open(myfifo, O_WRONLY);
    if(fd == -1) {
        perror("open() error: ");
        exit(1);
    }
    write(fd, &drepturi, sizeof(int));
    write(fd, nume_fisier, 20 * sizeof(char));
    close(fd);
    free(nume_fisier);

    char* mesaj = (char*)malloc(35 * sizeof(char));
    fd = open(myfifo, O_RDONLY);
    if(fd == -1) {
        perror("open() error: ");
        exit(1);
    }
    read(fd, mesaj, 35 * sizeof(char));
    printf("%s\n", mesaj);
    close(fd);
    free(mesaj);
    
    return 0;
}
