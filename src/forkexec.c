/*-------------------------------------------------	*/
/*                                                  */
/*	CREE PAR:                                       */
/*	ADRIEN NINI PEREIRA | AURELIEN KOTAJI           */
/*  FRANCOIS SHANTOU | KEVIN COLLART                */
/*													*/
/*	CLASSE: 1TL2                ECOLE: EPHEC        */
/* 	ANNEE: 2016-2017                LIEU: LL-N      */
/*													*/
/*	DERNIERE MISE A JOUR: 23/05/17    A    23h38 	*/
/*	PAR: ADRIEN                           			*/
/*													*/
/*------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){

	// VARIABLES	

	int fp[2]; // Pipe Fils -> Père
	int vr; // Résultat du fork()

	// PROGRAM

	if (argc < 2) { // Si il n'y a pas d'arguments passés, quitter le programme et renvoyer une erreur 

		char error[] = "Missing Argument\n";
		write(2, error, sizeof(error)); // Affiche l'erreur sur STDERR
		exit(-1);

	}

	if (pipe(fp) == -1){ // Crée et vérifie que la création du pipe n'a pas créé d'erreur

		write(2, sys_errlist[errno], sizeof(sys_errlist[errno])); // Affiche l'erreur sur STDERR
		exit(-1);

	}

	if ((vr = fork()) == -1){ // Crée le Process enfant et vérifie qu'il n'a pas créé d'erreur

		write(2, sys_errlist[errno], sizeof(sys_errlist[errno]));  // Affiche l'erreur sur STDERR
		exit(-1);

	} else if (vr == 0) { // Process Fils

		if (dup2(fp[1], 1) == -1) { // Redirige STDOUT vers le pipe FP

			write(2, sys_errlist[errno], sizeof(sys_errlist[errno])); // Affiche l'erreur sur STDERR
			exit(-1);

		}

		char **args; // Tableau de chaine de caractères pour la commande et arguments passés en argument
		args = malloc((argc-1) * sizeof(char*)); // Allocation dynamique du tableau de chaine de caractères

		int i;
		for (i=0; i < argc; i++){ // Remplissage dynamique du tableau de la commande et arguments

			args[i] = argv[i+1];

		} 
		args[argc-1] = NULL; // Dernier élément du tableau est NULL

		if (execvp(argv[1], args) == -1){ // Exécute la commande passée en argument au programme

			write(2, sys_errlist[errno], sizeof(sys_errlist[errno])); // Affiche l'erreur sur STDERR
			exit(-1);

		}

	}
	else { // Process Père 

		char buffer[255]; // Buffer de taille max de 255 caractères
		int nbRead; // Taille de la chaine de caractère passée dans le pipe
		
		do {

			nbRead = read(fp[0], buffer, sizeof(buffer)); // Lis dans le Pipe FP et enregistre dans le Buffer (max 255 caracs. à la foix)
			write(1, buffer, nbRead); // Ecrit le buffer sur STDOUT

		} while (nbRead == sizeof(buffer)); // Si la taille de la chaine lue dans le pipe est égale à la taille du buffer, réexécuter le code pour lire le reste

		exit(0);

	}

	return 0;

}


/*------------- SOURCES ----------------*/
/*

	http://www.zeitoun.net/articles/communication-par-tuyau/start
	http://www.gidforums.com/t-3369.html
	https://linux.die.net/man/3/execvp
	http://man7.org/linux/man-pages/man3/errno.3.html
	https://openclassrooms.com/courses/la-programmation-systeme-en-c-sous-unix/les-processus-1
	http://www.minek.com/files/unix_examples/execill.html
	cours Ephec init OS
    Kit de survie C

*/
