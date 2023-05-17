#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/fifo10" // path to the fifo file

int main(int argc, char** argv) {
    // create the fifo
    char* myfifo = FIFO_PATH;
    mkfifo(myfifo, 0666);
    
    // allocate and read the data sent by the client
    int rights = 0;
    char* filename = (char*) malloc(20 * sizeof(char));
    // open the fifo for reading
    int fd = open(myfifo, O_RDONLY);
    read(fd, &rights, sizeof(int));
    read(fd, filename, 20 * sizeof(char));
    // close the fifo
    close(fd);

    // open the fifo for writing the message
    char* mesaj = (char*) malloc(35 * sizeof(char));
    fd = open(myfifo, O_WRONLY);
    
    struct stat buffer;
    int res = stat(filename, &buffer);
    if(res == -1) {
        strcpy(mesaj, "Error: file not found!\n");
        // write the error message
        write(fd, mesaj, 35 * sizeof(char));
        close(fd); // !! close the fifo !!
        free(mesaj);
        free(filename);
        exit(1); // end execution with error code
    }

    int statchmod = buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    if(statchmod == rights) {
        strcpy(mesaj, "Everything is OK!");
    }
    else {
        res = chmod(filename, rights);
        if(res == -1) {
            strcpy(mesaj, "Error while changing permissions!\n");
            write(fd, mesaj, 35 * sizeof(char));
            close(fd); // !! close the fifo !!
            free(mesaj);
            free(filename);
            exit(1);
        }
        strcpy(mesaj, "Permissions changed.");
    }
    
    // write back the message
    write(fd, mesaj, 35 * sizeof(char));
    // close the fifo
    close(fd);
    free(filename);
    free(mesaj);

    return 0;
}
