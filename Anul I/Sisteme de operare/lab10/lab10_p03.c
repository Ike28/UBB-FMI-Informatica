#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

void replaceVowels(char* str) {
    int i, j;
    char vw[] = {'a', 'e', 'i', 'o', 'u'};
    char rep[] = {'1', '2', '3', '4', '5'};

    for(i = 0; str[i] != 0; i++) {
        for(j = 0; j < 5; j++) {
            if(str[i] == vw[j]) {
                str[i] = rep[j];
                break;
            }
        }
    }
}

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
    int c2p[2], p2c[2];
    int res = pipe(c2p);
    
    if(res == -1) {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    res = pipe(p2c);
    if(res == -1) {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    res = fork();
    if(res == -1) {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if(res == 0) {
        close(p2c[0]);
        close(p2c[1]);
        close(c2p[0]);
    
        char** text = (char**)malloc(MAX_LINES * sizeof(char*));
        int dim=0;
        printf("Introduceti textul\n(pentru a opri citirea, introduceti linia \"$\"):\n");
        while(dim < MAX_LINES) {
            text[dim] = (char*)malloc(MAX_LENGTH * sizeof(char));
            fgets(text[dim], MAX_LENGTH, stdin);
            if(strcmp(text[dim], "$\n") == 0) {
                free(text[dim]);
                break;
            }
            dim++;
        }

        write(c2p[1], &dim, sizeof(int));
        int i;
        for(i = 0; i < dim; i++) {
            write(c2p[1], text[i], MAX_LENGTH * sizeof(char));
            free(text[i]);
        }
        
        free(text);
        close(c2p[1]);
        exit(EXIT_SUCCESS);
    }
    else {
        int status;
        wait(&status);

        int lines;
        read(c2p[0], &lines, sizeof(int));
        write(p2c[1], &lines, sizeof(int));

        char* textLine = (char*)malloc(MAX_LENGTH * sizeof(char));

        int i;
        for(i = 0; i < lines; i++) {
            read(c2p[0], textLine, MAX_LENGTH * sizeof(char));
            write(p2c[1], textLine, MAX_LENGTH * sizeof(char));
        }
        free(textLine);

        res = fork();
        if(res == -1) {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }
        
        if(res == 0) {
            close(p2c[1]);
            close(c2p[0]);
            
            int dim;
            read(p2c[0], &dim, sizeof(int));

            textLine = (char*)malloc(MAX_LENGTH * sizeof(char));
            int i;
            for(i = 0; i < dim; i++) {
                read(p2c[0], textLine, MAX_LENGTH * sizeof(char));
                replaceVowels(textLine);
                write(c2p[1], textLine, MAX_LENGTH * sizeof(char));
            }
                
            free(textLine);
            close(p2c[0]);
            close(c2p[1]);
            exit(EXIT_SUCCESS);
        }
        else {
            textLine = (char*)malloc(MAX_LENGTH * sizeof(char));

            printf("\nRezultat:\n");
            for(i = 0; i < lines; i++) {
                read(c2p[0], textLine, MAX_LENGTH * sizeof(char));
                if(alphanumString(textLine))
                    printf("%s", textLine);
            }
            free(textLine);
            close(c2p[0]); close(c2p[1]);
            close(p2c[0]); close(p2c[1]);       
        }
    }
    return 0;
}
