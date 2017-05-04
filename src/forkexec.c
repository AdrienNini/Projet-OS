#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	int pf[2];
	int fp[2];
	int vr;

	if (pipe(pf) == -1){
		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error));
	}

	if (pipe(fp) == -1){
		char error[] = "An error occured during the creation of the pipe\n";	
		write(2, error, strlen(error));
	}

	if ((vr = fork()) == -1){
		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error));
	}

	 if (vr == 0) {
		char buffer[255];
		int nbRead;
		if ((nbRead = read(pf[0], buffer, strlen(argv[1]))) == strlen(argv[1])){
			printf("Child : %s\n", buffer);
			write(fp[1], buffer, nbRead);
		} else {
			char error[] = "Error";
			write(2, error, strlen(error));
		}

		exit(0);
	} else {
		char buffer[255];
		int nbRead, nbWrite;

		nbWrite = write(pf[1], argv[1], strlen(argv[1]));
		printf("Parent : %s\n", argv[1]);
		nbRead = read(fp[0], buffer, nbWrite);
		write(1, buffer, nbRead);

		exit(0); 
	}

	return 0;

}
