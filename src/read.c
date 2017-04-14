/*
 * read.c
 *
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

void readlines(char* directory) {
    char line[LINE_SIZE] = "";
    FILE* file = NULL;

    file = fopen(directory, "r"); // lecture seule pour plus de securite

    if (file != NULL) {
        while (fgets(line, LINE_SIZE, file) != NULL)
            printf("%s", line); // le \n devra etre contenu dans la ligne a ajouter

        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");
}

void read_specific(char* directory, int i) {
    char line[LINE_SIZE] = "";
    FILE* file = NULL;

    file = fopen(directory, "r");

    if(file != NULL) {
        int k;

        for(k = 0; k < i; k++)
            fgets(line, LINE_SIZE, file);

        printf("%s", line);
        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");
}

int isEmpty(char chemin[NAME_FILE_SIZE]) {
    char line = ' ';
    FILE* file = NULL;

    file = fopen(chemin, "r");

    if (file != NULL) {
        line = fgetc(file);
        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");

    return line == EOF;
}

void readNames(FILE* file, char joueur1[NAME_PLAYER_SIZE], char joueur2[NAME_PLAYER_SIZE]) {
    char names[2][NAME_FILE_SIZE];
    int i;

    fscanf(file, "%s %s", names[0], names[1]);

    // on copie la valeur recuperee dans joueur 1 puis 2 :
    for (i = 0; i < strlen(names[0]); i++)
        joueur1[i] = names[0][i];

    for (i = 0; i < strlen(names[1]); i++)
        joueur2[i] = names[1][i];

    // pour eviter de garder des traces de nom precedent s'ils sont plus long que les nouveaux
    joueur1[strlen(names[0])] = '\0';
    joueur2[strlen(names[1])] = '\0';
}

void loadSavedGame(Game *game) {
    char file_saved[NAME_FILE_SIZE] = "saved.txt";
    FILE* file = NULL;

    file = fopen(file_saved, "r");

    if (file != NULL) {
        //game -> creationGame = ? on recupere la date de la sauvegarde
        char line[LINE_SIZE] = "";
        int profits[2] = {0};

        fgets(line, LINE_SIZE, file); // on passe la premiere ligne

        // atoi -> string to int
        game -> gameNumber = atoi(fgets(line, LINE_SIZE, file)); // on recupere le numero de jeu

        // on recupere les noms et on modifie directement la valeur game.joueur1/2
        readNames(file, game -> joueur1, game -> joueur2);

        // on recupere les gains de chaques joueurs
        fscanf(file, "%d %d", &profits[0], &profits[1]);

        // et on les stocks dans la structure game
        game -> gain1 = profits[0];
        game -> gain2 = profits[1];

        // on recupere le tableau
        int i, j;
        for (i = 0; i < NB_ROW; i++) {
            for (j = 0; j < NB_HOLES; j++) {

                // on recupere le contenu d'une cellule (board[i][j])
                int ceil[1] = {0};
                fscanf(file, "%d", &ceil[0]);

                // on la stocke dans la structure game
                (game -> board_config)[i][j] = ceil[0];
            }
        }

        // on recupere le temps ecoule
        int times[3] = {0}; // va stocker hrs, min, sec ecoulees dans times[0], [1] et [2]
        fscanf(file, "%d:%d:%d", &times[0], &times[1], &times[2]); // ":" comme delimiteurs

        // maj de timeSpent a jouer
        (game -> timeSpent)[0] = times[0];
        (game -> timeSpent)[1] = times[1];
        (game -> timeSpent)[2] = times[2];

        // on recupere le current player
        fseek(file, -1, SEEK_END); // on place le curseur 1 caractere avant la fin du fichier
        game -> currentPlayer = atoi(fgets(line, LINE_SIZE, file)); // str to int

        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");
}
