/*
 * game.h
 *
 * Created on: 18 mars 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "game.h"
#include "ask.h"
#include "time.h"
#include "write.h"
#include "read.h"
//#include "../essaiPerso.h"

int whichNumber(char* directory) { // date | game_number | name_winner | gain winner | name_loser | gain_loser | time_elapsed

    FILE* file = NULL;
    file = fopen(directory, "r");

    int line;
    int cpt = 1; // si le fichier est vide, aucune partie n'a ete instanciee, on ecrit donc la numero 1

    if(file != NULL) {

        line = fgetc(file);

        while(line != EOF) {
            if (line == '\n') {
                cpt++;
            } line = fgetc(file);
        }

        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");

    return cpt;
}

void boardInit(short board[][NB_HOLES]) {

    int i, j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;
}

void loard_blank_game(FILE* file_list, Game *game, struct tm *timer) {

    // on recupere quel devrait etre le numero de cette partie (i+1 si i parties deja jouees)
    //int number = whichNumber(file_list);

    // on demande le nom des joueurs et on complete la struct Game:
    askName(game -> joueur1, 1);
    askName(game -> joueur2, 2);

    game -> gameNumber = whichNumber(file_list);
    game -> gain1 = 0;
    game -> gain2 = 0;
    game -> currentPlayer = askCurrent(); // renvoit 0 ou 1 pour savoir a qui de jouer en premier
    game -> creationGame = timer;

    (game -> timeSpent)[0] = 0;
    (game -> timeSpent)[1] = 0;
    (game -> timeSpent)[2] = 0;

    // initialisation du tableau
    int i,j;
    for (i=0; i<NB_ROW; i++)
        for (j=0; j<NB_HOLES; j++)
            (game -> board_config)[i][j] = NB_SEED_INIT;
}

int hasWinner(Game* game) {

    int s1 = 0;
    int s2 = 0;

    int j;
    for (j=0; j<NB_HOLES; j++) {
        s1 += (game -> board_config)[0][j];
        s2 += (game -> board_config)[1][j];
    }

    return (s1 == 0 || s2 == 0);
}

int quit(char* file_save, char* file_list, Game* game, struct tm *dateCreation) {

    //char file_save[NAME_FILE_SIZE] = "saved.txt";
    //char file_list[NAME_FILE_SIZE] = "listGames.txt";

    char ans = ' ';

    do {
        printf("\n Do you want to save the game ? (y/n)\n");
        scanf("\n%c", &ans);
    } while (ans != 'y' && ans != 'n');

    if (ans == 'y') {

        save(file_save, game, dateCreation);
        printf(" The game has been saved with success\n");
    }

    char ans2 = ' ';

    do {
        printf("\n Do you want to quit? (y/n)\n");
        scanf("\n%c", &ans2);
    } while (ans2 != 'y' && ans2 != 'n');

    if (ans2 == 'y') {

        // on retourne le gagnant :
        if (game -> gain1 > game -> gain2)
            printf("\n CONGRATULATION ! %s has won with a total score of: %d\n", game -> joueur1, game -> gain1);

        else {

            if (game -> gain1 < game -> gain2)
                printf("\n CONGRATULATION ! %s has won with a total score of: %d\n", game -> joueur2, game -> gain2);
            else printf("\n No winner for this game \n");
        }

        /*
        time_t secondes;
        struct tm timeExit;
        time(&secondes);
        timeExit = *localtime(&secondes);
        */

        saveInList(file_list, game, dateCreation);
        printf(" listGames.txt has been completed\n");

        return 1;
    }
    return 0;
}

void nextStep(Game* game) {

    int caseSelected = NULL; // on recupere le numero de la case a jouer

    int current = (game -> currentPlayer); // on recupere le joueur qui a la main (0 ou 1)

    do {
        if (game -> currentPlayer == 0)
            printf("\n %s, which square have I to select? (0 < nber < 7)\n", (game -> joueur1));
        else printf("\n %s, which square have I to select? (0 < nber < 7)\n", game -> joueur2);
        scanf("%d", &caseSelected);
    } while (caseSelected < 1 || caseSelected > 6 || (game -> board_config)[current][caseSelected-1] == 0 ); // on n'autorise pas a jouer une case vide

    int nbSeeds =  (game -> board_config)[current][caseSelected-1]; // on retient le nombre de graines dans la case selected

    (game -> board_config)[current][caseSelected-1] = 0; // on vide la case que l'on a jouee

    int j = caseSelected-1;

    // maj du plateau
    if ((game -> currentPlayer) == 1) {

        while (nbSeeds != 0) {

            while (j < NB_HOLES-1 && nbSeeds != 0 && current == 1) {
                j++;
                // si on retombe sur la case de depart, on la saute sans mettre de graines
                if (!(current == (game->currentPlayer) &&  j == caseSelected-1)) {
                    (game -> board_config)[current][j] += 1;
                    //printf("current = %d, j = %d, nbSeeds = %d\n", current, j, nbSeeds);
                    nbSeeds--;
                }
             }
             current++;
             current %= 2;
             while (j >= 0 && nbSeeds != 0 && current == 0) {

                if (!(current == (game->currentPlayer) &&  j == caseSelected-1)) {
                    (game -> board_config)[current][j] += 1;
                    nbSeeds--;
                    //printf("current = %d, j = %d, nbSeeds = %d\n", current, j, nbSeeds);
                }
                j--;
             }
        }

        // on gere les gains :

        j++; // pour compenser le j-- precedent
        // si on s'arrete sur un case adverse avec 2 ou 3 graines avec la notre
        if (current == 0 && ((game -> board_config)[current][j] == 2 || (game -> board_config)[current][j] == 3)) {

                // on affiche le plateau de jeu
                printf("\n                        |      status before collecting \n");
                int u, v;
                for (u=0; u<NB_ROW; u++) {
                    for (v=0; v<NB_HOLES; v++) {
                        printf(" %d ", (game -> board_config)[u][v]);
                    } printf("\n");
                }

                // on ramasse les grains jusqu'a rencontrer une case avec nbSeeds > 3 ou sortir de la zone adverse
                while (((game -> board_config)[current][j] == 2 || (game -> board_config)[current][j] == 3 ) && j < NB_HOLES) {
                    (game -> gain2) += (game -> board_config)[current][j];
                    (game -> board_config)[current][j] = 0;
                    j++;
                }
        }

    } else {

        while (nbSeeds != 0) {

            while (j > 0 && nbSeeds != 0 && current == 0) {
                j--;
                if (!(current == (game->currentPlayer) &&  j == caseSelected-1)) {
                    (game -> board_config)[current][j] += 1;
                    nbSeeds--;
                    //printf("current = %d, j = %d, nbSeeds = %d\n", current, j, nbSeeds);
                }
             }
            current++;
            current %= 2;
            while (j < NB_HOLES && nbSeeds != 0 && current == 1) {
                 if (!(current == (game->currentPlayer) &&  j == caseSelected-1)) {
                    (game -> board_config)[current][j] += 1;
                    nbSeeds--;
                    //printf("current = %d, j = %d, nbSeeds = %d\n", current, j, nbSeeds);
                 }
                j++;
             }
        }

        j--;
        if (current == 1 && ((game -> board_config)[current][j] == 2 || (game -> board_config)[current][j] == 3)) {

                // on affiche le plateau de jeu
                printf("\n                        |      status before collecting \n");
                int u, v;
                for (u=0; u<NB_ROW; u++) {
                    for (v=0; v<NB_HOLES; v++) {
                        printf(" %d ", (game -> board_config)[u][v]);
                    } printf("\n");
                }

                // on ramasse les grains jusqu'a rencontrer une case avec nbSeeds > 3 ou sortir de la zone adverse
                while (((game -> board_config)[current][j] == 2 || (game -> board_config)[current][j] == 3 ) && j > 0) {
                    (game -> gain1) += (game -> board_config)[current][j];
                    (game -> board_config)[current][j] = 0;
                    j--;
                }
        }
    }

    // on change la main pour le prochain tour
    (game -> currentPlayer)++;
    (game -> currentPlayer) %= 2;

    printf("\n");
    affichage(game);
}

void play_console() {

    int launchAgain = ' ';

    do {

        Game game;
        char file_save[NAME_FILE_SIZE] = "saved.txt";
        char file_list[NAME_FILE_SIZE] = "listGames.txt";

        char loard = ' ';
        printf("Do you want to loard from saved.txt ? (y/n)\n");
        scanf("%c", &loard);

        if (loard == 'y') {

            // si le fichier de sauvegarde est vide, on ne peut que creer une nouvelle partie car pas en memoire
            if (isEmpty(file_save)) {

                printf("No data has been found, I'm launching a new game:\n");

                // on recupere les infos temporelles de sa creation
                time_t secondes;
                struct tm dateCreation;
                time(&secondes);
                dateCreation = *localtime(&secondes);

                loard_blank_game(file_list, &game, &dateCreation); // on initialise la struct game vide

                printf("\n ========================== THE GAME BEGINS =========================\n\n");

                do {
                    affichage(&game);
                    nextStep(&game);
                } while (!quit(file_save, file_list, &game, &dateCreation));
            }

            else {

                // on recupere les infos temporelles de sa creation
                time_t secondes;
                struct tm dateCreation;
                time(&secondes);
                dateCreation = *localtime(&secondes);

                loard_saved_game(&game); // on initialise la struct game vide

                printf("\n ========================== THE GAME BEGINS =========================\n\n");

                do {
                    affichage(&game);
                    nextStep(&game);
                } while (!quit(file_save, file_list, &game, &dateCreation));
            }
        }

        else {

            // on recupere les infos temporelles de sa creation
            time_t secondes;
            struct tm dateCreation;
            time(&secondes);
            dateCreation = *localtime(&secondes);

            loard_blank_game(file_list, &game, &dateCreation); // on initialise la struct game vide

            printf("\n ========================== THE GAME BEGINS =========================\n\n");

            do {
                affichage(&game);
                nextStep(&game);
            } while (!quit(file_save, file_list, &game, &dateCreation));
        }

        printf("\n Do you want to launch again ? (y/n)\n");
        scanf("%c\n", &launchAgain);
    } while (launchAgain == 'y');
}


