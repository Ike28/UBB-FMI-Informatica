//	* Parent(the client) sends an octal value and a filename to the child (the server).
//	* The child/server will check if the file has different permissions than the value provided.
//		- if the permissions match, a message will be sent back containing "Everything is OK!"
//		- else, it will change the permissions of the file accordingly and send back the message "Permissions changed."

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
	// create and open pipes before fork
	int parent_to_child[2]; // parent will write on channel 1, child will read from channel 0
	int child_to_parent[2]; // child will write on channel 1, parent will read from channel 0
	int rez = pipe(parent_to_child);
	if(rez == -1)
	{
		perror("pipe() error: ");
		exit(1);
	}
	rez = pipe(child_to_parent);
	if(rez == -1)
	{
		perror("pipe() error: ");
		exit(1);
	}

	// read permissions from the user
	int perms = 0;
	printf("Input the permissions as an octal value: ");
	rez = scanf("%o",&perms);
	if(rez != 1)
	{
		printf("Error: input value is not an octal number!\n");
		exit(1);
	}

	// read filename from the user
	char* file_name = (char*)malloc(20 * sizeof(char)); // allocate memory
	printf("Input the filename: ");
	scanf("%s",file_name);
	
	// create the processes using fork
	pid_t pid= fork();
	if(pid == -1) // fork failed
	{
		perror("fork() error: ");
		exit(1);
	}
	if(pid == 0) // child code
	{
		// close the pipe channels we do not need
		close(parent_to_child[1]);
		close(child_to_parent[0]);

		int rights = 0;
		char* filename = (char*) malloc(20 * sizeof(char));
		// read data send by the parent
		read(parent_to_child[0], &rights, sizeof(int));
		read(parent_to_child[0], filename, 20 * sizeof(char));
		
		char* mesaj = (char*) malloc(35 * sizeof(char)); // message that will be sent back

		// get the system information about the file
		struct stat buffer;
		int res = stat(filename, &buffer);
		if(res == -1)
		{
			printf("Error: file not found!\n");
			// finish the child execution with code 1 (error)
			exit(1);
		}

		int statchmod = buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO); // st_mode contains permissions of file, perform a bit operation to get octal value
		if(statchmod == rights)
		{
			strcpy(mesaj,"Everything is OK!");
		}
		else
		{
			int res = chmod(filename,rights); // change permissions if they do not match
			if(res == -1)
			{
				printf("Error while changing permissions!\n");
				exit(1);
			}
			strcpy(mesaj,"Permissions changed.");
		}
		
		// send a message back to the parent
		write(child_to_parent[1], mesaj, 35 * sizeof(char));

		// close remaining pipe channels
		close(parent_to_child[0]);
		close(child_to_parent[1]);

		// free the allocated memory
		free(filename);
		free(mesaj);

		// finish the child execution with code 0 (successful)
		exit(0);
	}
	else // parent code
	{
		// close the pipe channels we do not need
		close(child_to_parent[1]);
		close(parent_to_child[0]);

		// write the read data to the child
		write(parent_to_child[1], &drepturi, sizeof(int));
		write(parent_to_child[1], nume_fisier, 20 * sizeof(char));

		// wait for the child to finish execution
		int status;
		wait(&status);
		
		// check if the child process finished with an error
		if(WEXITSTATUS(status) == 1)
		{
			exit(1);
		}
		
		// otherwise, read the message
		char* mesaj = (char*) malloc(35 * sizeof(char));
		read(child_to_parent[0], mesaj, 35 * sizeof(char));
		printf("%s\n",mesaj);

		// close the remaining pipe channels
		close(parent_to_child[1]);
		close(child_to_parent[0]);

		// free allocated memory
		free(mesaj);
		free(nume_fisier);
	}
	return 0;
}
