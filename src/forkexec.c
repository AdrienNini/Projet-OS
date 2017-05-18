#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	// VARIABLES	

	int fp[2]; // Pipe Père -> Fils
	int vr; // Résultat du fork()

	// PROGRAM
	
	if (argc < 2) {

	 printf("missing argument");
	return 0;

	}

	if (pipe(fp) == -1){ // Crée et vérifie que la création du pipe n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n"; 
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	}

	if ((vr = fork()) == -1){ // Crée le Process enfant et vérifie qu'il n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	} else if (vr == 0) { // Process Fils
		char *args[] = { argv[1], argv[2], argv[3], NULL};
		execvp(argv[1], args);
	}
	else { // Process Père 

		char buffer[255];
		int nbRead; // Taille de la chaine de caractère passée dans le pipe

		exit(0);

	}

	return 0;

}
