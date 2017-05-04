#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){

	int pf[2];
	int fp[2];

	if (pipe(pf) == -1){
		printf("An error occured during the creation of the pipe\n");
	}

	if (pipe(fp) == -1){
		printf("An error occured during the creation of the pipe\n");
	}

	if (fork() == 0) {
		char buffer[50];
		read(pf[0], buffer, sizeof(argv[1]));
		printf("%s\n", buffer);
	} else {
		write(pf[1], argv[1], sizeof(argv[1]));
	}

	return 0;

}
