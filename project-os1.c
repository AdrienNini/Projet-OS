/*----------------------------------------------------------------------------------*/
/*																					*/
/*	CREE PAR:																		*/ 
/*	ADRIEN NINI PEREIRA | AURELIEN KOTAJI | FRANCOIS CHANTOU | KEVIN COLLART		*/
/*																					*/
/*  CLASSE: 1TL2		ECOLE: EPHEC		ANNEE: 2016-2017		LIEU: LL-N		*/
/*																					*/
/*	DERNIERE MISE A JOUR: 22/05/2017	A 	14H04		PAR: KEVIN					*/
/*																					*/
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){

	// VARIABLES	

	int fp[2]; // Pipe Père -> Fils
	int vr; // Résultat du fork()

	// PROGRAM
	
	if (argc < 2) {

	 	printf("missing argument");
		
		return 0;

	}

	// CREATION DU PIPE

	if (pipe(fp) == -1){ // Crée et vérifie que la création du pipe n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n"; 
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	}

	// CREATION PROCESS FILS

	if ((vr = fork()) == -1){ // Crée le Process fils et vérifie qu'il n'a pas créé d'érreur

		char error[] = "An error occured during the creation of the pipe\n";
		write(2, error, strlen(error)); // Affiche l'érreur sur STDERR

	}

	// PROCESS FILS

	else if (vr == 0) { 

		char *args[] = { argv[1], NULL}; //reprend les arguments du process
		
		// stdout
		
		dup2(fp[1], 1); // connect la lecture avec stdout
		
		// execute le process
		execvp(argv[1], args);
	
	}

	// PROCESS PERE
	
	else {  

		char buffer[255]; // retourne la valeur contenue dans le buffer
		int nbRead; // Taille de la chaine de caractère passée dans le pipe

		// stdout
		
		do{
			nbRead = read(fp[0], buffer, sizeof(buffer));
			write(1, buffer, nbRead); //ecrit dans stdout
		}while(nbRead == sizeof(buffer));
		
		exit(0); // total final process

	}

	return 0;

}

/*------------------------ THE POINT OF THE END ! -------------------------*/
/*------------- SOURCES ----------------*/
/*

	http://www.zeitoun.net/articles/communication-par-tuyau/start
	http://www.gidforums.com/t-3369.html
	cours Ephec init OS
	notre bon vouloir

*/
