#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/fifopmc"

int main(int argc, char** argv) {
    char* myfifo = FIFO_PATH;
    int res = mkfifo(myfifo, 0666);
    
    int rights = 0;
    char* filename = (char*)malloc(20 * sizeof(char));
    
    printf("Se asteapta datele de la client...\n");
    int fd = open(myfifo, O_RDONLY);
    if(fd == -1) {
        perror("open() error: ");
        exit(1);
    }
    read(fd, &rights, sizeof(int));
    read(fd, filename, 20 * sizeof(char));
    close(fd);
    
    char* mesaj = (char*)malloc(35 * sizeof(char));
    fd = open(myfifo, O_WRONLY);
    if(fd == -1) {
        perror("open() error: ");
        exit(1);
    }
    
    struct stat buffer;
    res = stat(filename, &buffer);
    if(res == -1) {
        strcpy(mesaj, "Eroare: Fisierul dat nu exista!\n");
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
    printf("SUCCES!\n");
    close(fd);
    free(filename);
    free(mesaj);

    return 0;
}
