#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINES 100
#define MAX_LENGTH 100
#define FIFOPATH1 "/tmp/fifoleft"
#define FIFOPATH2 "/tmp/fiforight"

bool alphanumString(char* str) {
    int i;
    if(str[0] == '\n')
        return false;
    
    for(i = 0; str[i] != 0; i++) {
        if(str[i] != '\n' && !isalnum(str[i]))
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    char* fifoleft = FIFOPATH1;    
    mkfifo(fifoleft, 0666);
    char* fiforight = FIFOPATH2;
    mkfifo(fiforight, 0666);
    
    printf("\nSe asteapta datele...\n");
    int lines;
    int fdleft = open(fifoleft, O_RDONLY);
    if(fdleft == -1) {
        perror("open() left branch error: ");   
        exit(1);
    }
    int fdright = open(fiforight, O_WRONLY);
    if(fdright == -1) {
        perror("open() right branch error: ");
        exit(1);
    }
    
    read(fdleft, &lines, sizeof(int));
    write(fdright, &lines, sizeof(int));
    
    char* textLine = (char*)malloc(MAX_LENGTH * sizeof(char));
    int i;
    for(i = 0; i < lines; i++) {
        read(fdleft, textLine, MAX_LENGTH * sizeof(char));
        write(fdright, textLine, MAX_LENGTH * sizeof(char));
    }
    close(fdleft);
    close(fdright);
    printf("Date trimise spre procesare...\n");
    
    fdright = open(fiforight, O_RDONLY);
    printf("\nRezultat:\n");
    for(i = 0; i < lines; i++) {
        read(fdright, textLine, MAX_LENGTH * sizeof(char));
        if(alphanumString(textLine))
            printf("%s", textLine);
    }
    free(textLine);
    close(fdright);

    return 0;
}
