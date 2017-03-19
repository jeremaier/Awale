/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "const.h"
#include "write.h"

void initialize(char* directory) { // vide le fichier directory
	FILE* file = NULL;
	file = fopen(directory, "w");

	if(file != NULL) {
		fseek(file, 0, SEEK_SET); // on place le curseur au debut
		fputs("", file); // on ecrit la chaine de caractere vide
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier");
}

void write_new_line(char* directory, char* chaine) {
	FILE* file = NULL;
	file = fopen(directory, "a"); // append, pour lire ou ecrire a la fin d'un fichier

	if(file != NULL) {
		fputs(chaine, file);
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier");
}

void time_elapsed(FILE* file, struct tm *tpsReference) { // remplace difftime(time_t t1, time_t t2)
	time_t secondes; // recupere le temps actuel
	struct tm instant;
	time(&secondes);
	instant = *localtime(&secondes);

	instant.tm_hour -= (*tpsReference).tm_hour; // calcul de la duree de jeu
	instant.tm_min -= instant.tm_min;
	instant.tm_sec -= (*tpsReference).tm_sec;

	fprintf(file, "TIME ELAPSED: %d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
}

void save(char* directory, Game* game, struct tm *tpsReference) {
	FILE* file = NULL;
	file = fopen(directory, "w"); // append, pour lire ou ecrire a la fin d'un fichier

	if(file != NULL) {
		time_t secondes; // recupere la date et heure de la sauvergarde (execution de save())
		struct tm instant;
		time(&secondes);
		instant = *localtime(&secondes);

		fprintf(file, "DATE: %d/%d/%d %d:%d:%d\n", instant.tm_mday + 1, instant.tm_mon + 1, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec);
		fprintf(file, "GAME NUMBER: %d\n", game -> gameNumber); // ecrit un int dans le fichier
		fprintf(file, "PLAYERS' NAME: %s %s\n", game -> joueur1, game -> joueur2);
		fprintf(file, "PLAYERS' PROFIT: %d %d\n", game -> gain1, game -> gain2);

		fprintf(file, "BOARD CONFIGURATION:\n");
		int i, j;

		for(i = 0; i < NB_ROW; i++) {
			for(j = 0; j < NB_HOLES; j++)
				fprintf(file, "%d\n", game -> board_config[i][j]);
		}

		time_elapsed(file, tpsReference);
		fprintf(file, "CURRENT PLAYER: %hd\n", game -> currentPlayer);
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier");
}
