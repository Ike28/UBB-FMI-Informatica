//  * Parent(the client) sends an octal value and a filename to the child (the server).
//  * The child/server will check if the file has different permissions than the value provided.
//      - if the permissions match, a message will be sent back containing "Everything is OK!"
//      - else, it will change the permissions of the file accordingly and send back the message "Permissions changed."

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/fifo10" // path to the fifo file

int main(int argc, char** argv) {
	// allocate the variables and read them from the user
    int drepturi = 0;
    printf("Input the permissions as an octal value: ");
    int rez = scanf("%o", &drepturi);
    if(rez != 1) {
        printf("Error: input value is not an octal number!\n");
        exit(1);
    }

    char* nume_fisier = (char*) malloc(20 * sizeof(char));
    printf("Input the filename: ");
    scanf("%s", nume_fisier);

    // create the fifo, 0666 = read-write permissions for all
    char* myfifo = FIFO_PATH;
    mkfifo(myfifo, 0666);

    // open the fifo for writing
    int fd = open(myfifo, O_WRONLY);
    // send the data
    write(fd, &drepturi, sizeof(int));
    write(fd, nume_fisier, 20 * sizeof(char));
    // close the fifo
    close(fd);
    free(nume_fisier);
    
    char* mesaj = (char*) malloc(35 * sizeof(char));
    // open the fifo for reading
    fd = open(myfifo, O_RDONLY);
    read(fd, mesaj, 35 * sizeof(char));
    printf("%s\n", mesaj);
    // close the fifo
    close(fd);
    free(mesaj);
       
    return 0;
}
