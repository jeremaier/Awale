/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "write.h"

void Initialize(char* directory) { // vide le fichier directory
	FILE* file = NULL;

	file = fopen(directory, "w");

	if(file != NULL) {
		fseek(file, 0, SEEK_SET); // on place le curseur au debut
		fputs("", file); // on ecrit la chaine de caractere vide
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier\n");
}

void WriteNewLine(char* directory, char* chaine) {
	FILE* file = NULL;

	file = fopen(directory, "a"); // append, pour lire ou ecrire a la fin d'un fichier

	if(file != NULL) {
		fputs(strcat(chaine, "\n"), file);
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier\n");
}

void TimeElapsed(FILE* file, struct tm *tpsReference, int additionnal[3]) { // remplace difftime(time_t t1, time_t t2)
	struct tm instant = CurrentTime();

	instant.tm_hour -= (*tpsReference).tm_hour - additionnal[0]; // calcul de la duree de jeu
	instant.tm_min -= (*tpsReference).tm_min - additionnal[1];
	instant.tm_sec -= (*tpsReference).tm_sec - additionnal[2];

	fprintf(file, "%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
}

void TimeElapsedToString(struct tm *tpsReference) { // remplace difftime(time_t t1, time_t t2)
	struct tm instant = CurrentTime();

	instant.tm_hour -= (*tpsReference).tm_hour; // calcul de la duree de jeu
	instant.tm_min -= (*tpsReference).tm_min;
	instant.tm_sec -= (*tpsReference).tm_sec;

	printf(" time elapsed: %d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
}

void Save(const char* directory, struct tm* tpsReference) {
	FILE* file = NULL;

	file = fopen(directory, "w");

	if(file != NULL) {
		short i, j;
		struct tm instant = CurrentTime();

		fprintf(file,
				"%d/%d/%d %d:%d:%d\n",
				instant.tm_mday + 1,
				instant.tm_mon + 1,
				instant.tm_year + 1900,
				instant.tm_hour,
				instant.tm_min,
				instant.tm_sec);
		fprintf(file,
				"%d\n",
				game.gameNumber); // ecrit un int dans le fichier
		fprintf(file,
				"%s %s\n",
				game.joueur1,
				game.joueur2);
		fprintf(file,
				"%d %d\n",
				game.gains[0], game.gains[1]);

		for(i = 0; i < NB_ROW; i++)
			for(j = 0; j < NB_HOLES; j++)
				fprintf(file, "%d\n", game.board_config[i][j]);

		TimeElapsed(file, tpsReference, game.timeSpent); // ecrit le temps ecoule
		fprintf(file, "%hd\n", game.currentPlayer);
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier\n");
}

void SaveInList(const char* directory, struct tm *tpsReference) {
	FILE* file = NULL;

	file = fopen(directory, "a"); // append, pour lire ou ecrire a la fin d'un fichier

	if(file != NULL) {
		// recupere la date et heure de la sauvergarde (execution de saveInList())
		struct tm instant = CurrentTime();

		fprintf(file,
				"%d/%d/%d %d:%d:%d | %d | %s | %d | %s | %d | ",
				instant.tm_mday + 1,
				instant.tm_mon + 1,
				instant.tm_year + 1900,
				instant.tm_hour, instant.tm_min,
				instant.tm_sec, game.gameNumber,
				game.joueur1,
				game.gains[0],
				game.joueur2,
				game.gains[1]);

		TimeElapsed(file, tpsReference, game.timeSpent);
		fclose(file);
	}
	else printf("Impossible d'ecrire dans le fichier\n");
}

void DisplayConsole(Game *game) {
	int i, j;

	for(i = 0; i < NB_ROW; i++) {
		for(j = 0; j < NB_HOLES; j++)
			printf(" %d ", (game -> board_config)[i][j]);

		if(i == 0) {
			if (game -> currentPlayer == 0)
				printf("      |      current player: %s (row %d)\n", game -> joueur1, game -> currentPlayer + 1);
			else printf("      |      current player: %s (row %d)\n", game -> joueur2, game -> currentPlayer + 1);
		}
		else printf("      |      %s's profit: %d,    %s's profit: %d\n", game -> joueur1, game -> gains[0], game -> joueur2, game -> gains[1]);
	}
}
