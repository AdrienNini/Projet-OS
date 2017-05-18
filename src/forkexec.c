#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	// VARIABLES	

	int pf[2]; // Pipe Père -> Fils
	int vr; // Résultat du fork()

	// PROGRAM
	
	if (argc < 2) {

	 printf("missing argument");
	return 0;

	}

	if (pipe(pf) == -1){ // Crée et vérifie que la création du pipe n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n"; 
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	}

	if ((vr = fork()) == -1){ // Crée le Process enfant et vérifie qu'il n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	} else if (vr == 0) { // Process Fils
		char buffer [255]; 
		int nbWrite; // taille de la cahine de caractère envoyé dans le pipe
		nbWrite = write(pf[1], argv[1], strlen(argv[1])); // Envoie la cahine passée en argument dans le pipe PF 
	}
	else { // Process Père 

		char buffer[255];
		int nbRead; // Taille de la chaine de caractère passée dans le pipe

		if ((nbRead = read(pf[0], buffer, strlen(argv[1])))){ // Lecture du Pipe 
			write(1, buffer, nbRead); // Affiche la chaine du Buffer sur STDOUT
			
		} else {
			char error[] = "String length failure\n";
			write(2, error, strlen(error)); // Affiche une érreur sur SDTERR
		}

		exit(0);

	}

	return 0;

}
