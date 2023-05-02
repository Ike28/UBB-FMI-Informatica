#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILENAME "input.txt"

void filterMultiples(int n, int i) {
    FILE* fis = fopen(FILENAME, "r");
    if(fis == NULL) {
        perror("fopen() error: ");
        exit(EXIT_FAILURE);
    }

    int* filtered = (int*)malloc(n * sizeof(int));
    int num, dim=0;

    while(fscanf(fis, "%d\n", &num) != EOF) {
        if((num%i != 0 && num != 1) || num == i) {
            filtered[dim] = num;
            dim++;
        }
    }

    fclose(fis);
    
    fis = fopen(FILENAME, "w");

    int j;
    for(j = 0; j < dim; j++) {
        fprintf(fis, "%d\n", filtered[j]);
    }

    fclose(fis);
    free(filtered);
}

int main(int argc, char** argv) {
    int n;
    FILE* fis = fopen(FILENAME, "r");

    if(fis == NULL) {
        perror("fopen() error: ");
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fis, "%d\n", &n) != EOF);
    n++;
    fclose(fis);

    int pid = fork();
    if(pid == -1) {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        filterMultiples(n,2);
        exit(EXIT_SUCCESS);
    }
    else {
        int status;
        wait(&status);
        
        int i;
        for(i = 3; i < n; i += 2) {
            pid = fork();
            if(pid == -1) {
                perror("fork() error: ");
                exit(EXIT_FAILURE);
            }
            
            if(pid == 0) {
                filterMultiples(n, i);
                exit(EXIT_SUCCESS);
            }
            else {
                wait(&status);
            }
        }
    }

    return 0;
}
