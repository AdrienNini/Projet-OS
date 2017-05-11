#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	// VARIABLES	

	int fp[2]; // Pipe Fils -> Père
	int vr; // Résultat du fork()

	// PROGRAM

	if (pipe(fp) == -1){
		
		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR
	}

	if ((vr = fork()) == -1){ // Crée le Process enfant et vérifie qu'il n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	} else if (vr == 0) { // Process Fils

		char buffer[255];
		int nbWrite; // Taille de la chaine de caractère envoyée dans le pipe

			if ((nbWrite = write(fp[1], buffer, nbRead)) == nbRead) { // Envoie la chaine du Buffer dans le Pipe FP
				
			} else {
				char error[] = "String length failure\n";
				write(2, error, strlen(error)); // Affiche une érreur sur SDTERR
			}	

		exit(0);

	} else { // Process Père

		char buffer[255];
		int nbRead; //Taille de la chaine de caractère passée dans le pipe

			if ((nbRead = read(fp[0], buffer, nbWrite)) == nbWrite) {	
				write(1, buffer, nbRead); // Ecrit le buffer sur STDOUT
			} else {
				char error[] = "String length failure\n";
				write(2, error, strlen(error));
			}

		exit(0); 
	}

	return 0;

}
