#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LENGTH 100
#define FIFOPATH "/tmp/fiforight"

void replaceVowels(char* str) {
    int i, j;
    char vw[] = {'a', 'e', 'i', 'o', 'u'};
    char rep[] = {'1', '2', '3', '4', '5'};
    
    for(i = 0; str[i] != 0; i++) {
        for(j = 0; j < 5; j++) {
            if(tolower(str[i]) == vw[j]) {
                str[i] = rep[j];
                break;
            }
        }
    }
}

int main(int argc, char** argv) {
    char* fiforight = FIFOPATH;
    mkfifo(fiforight, 0666);
    
    printf("\nSe asteapta datele...\n");
    int dim;
    int fd = open(fiforight, O_RDONLY);
    if(fd == -1) {
        perror("open() right branch error: ");
        exit(1);
    }
    read(fd, &dim, sizeof(int));
    
    char** text = (char**)malloc(MAX_LINES * sizeof(char*));
    int i;
    for(i = 0; i < dim; i++) {
        text[i] = (char*)malloc(MAX_LENGTH * sizeof(char));
        read(fd, text[i], MAX_LENGTH * sizeof(char));
        replaceVowels(text[i]);
    }
    close(fd);
    
    fd = open(fiforight, O_WRONLY);
    if(fd == -1) {
        perror("open() right branch error: ");
        exit(1);
    }
    for(i = 0; i < dim; i++) {
        write(fd, text[i], MAX_LENGTH * sizeof(char));
        free(text[i]);
    }
    close(fd);
    
    printf("\n* * * SUCCES!\n");
    free(text);
    
    return 0;
}
