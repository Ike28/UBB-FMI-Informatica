//	* Clientul ii transmite serverului un nume de fisier si un numar octal.
//	* Serverul va verifica daca fisierul respectiv are drepturi de acces diferite de numarul indicat.
//		- daca drepturile coincid, va transmite mesajul "Totul e OK!"
//		- altfel, va seta drepturile conform numarului indicat si va transmite mesajul "Drepturile au fost modificate."

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/fifo10"

int main(int argc, char** argv) {
    char* myfifo = FIFO_PATH;
    mkfifo(myfifo, 0666);
    
    int rights = 0;
    char* filename = (char*)malloc(20 * sizeof(char));
    int fd = open(myfifo, O_RDONLY);
    read(fd, &rights, sizeof(int));
    read(fd, filename, 20 * sizeof(char));
    close(fd);

    char* mesaj = (char*)malloc(35 * sizeof(char));
    fd = open(myfifo, O_WRONLY);
    
    struct stat buffer;
    int res = stat(filename, &buffer);
    if(res == -1) {
        strcpy(mesaj, "Eroare : Fisierul dat nu exista!\n");
        write(fd, mesaj, 35 * sizeof(char));
        close(fd);
        free(mesaj);
        free(filename);
        exit(1);
    }

    int statchmod = buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    if(statchmod == rights) {
        strcpy(mesaj, "Totul e OK!");
    }
    else {
        res = chmod(filename, rights);
        if(res == -1) {
            strcpy(mesaj, "Eroare la modificarea drepturilor!\n");
            write(fd, mesaj, 35 * sizeof(char));
            close(fd);
            free(mesaj);
            free(filename);
            exit(1);
        }
        strcpy(mesaj, "Drepturile au fost modificate.");
    }
    
    write(fd, mesaj, 35 * sizeof(char));
    close(fd);
    free(filename);
    free(mesaj);

    return 0;
}
