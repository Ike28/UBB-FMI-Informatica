#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_LENGTH 100
#define MAX_LINES 100
#define FIFOPATH "/tmp/fifoleft"

int main() {
    char* fifoleft = FIFOPATH;
    mkfifo(fifoleft, 0666);
    
    char** text = (char**)malloc(MAX_LINES * sizeof(char));
    int dim = 0;
    printf("\nIntroduceti textul\n(pentru a opri citirea, introduceti linia \"$\"):\n");
    while(dim < MAX_LINES) {
        text[dim] = (char*)malloc(MAX_LENGTH * sizeof(char));
        fgets(text[dim], MAX_LENGTH, stdin);
        if(strcmp(text[dim], "$\n") == 0) {
            free(text[dim]);
            break;
        }
        dim++;
    }
    
    int fd = open(fifoleft, O_WRONLY);
    if(fd == -1) {
        perror("open() error: ");
        exit(1);
    }
    write(fd, &dim, sizeof(int));
    int i;
    for(i = 0; i < dim; i++) {
        write(fd, text[i], MAX_LENGTH * sizeof(char));
        free(text[i]);
    }
    
    free(text);
    close(fd);
    printf("\n* * * SUCCES!\n");
    
    return 0;
}
