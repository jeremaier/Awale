/*
 * game.h
 *
 * Created on: 18 mars 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>

#include "ask.h"
#include "time.h"
#include "write.h"
#include "read.h"
#include "movements.h"
#include "board.h"
#include "game.h"


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

void loadBlankGame(FILE* file_list, Game *game, struct tm *timer) {

    // on recupere quel devrait etre le numero de cette partie (i+1 si i parties deja jouees)
    //int number = whichNumber(file_list);

    // on demande le nom des joueurs et on complete la struct Game:
    askName(game -> joueur1, 1);
    askName(game -> joueur2, 2);

    game -> gameNumber = whichNumber(file_list);
    game -> gain1 = 0;
    game -> gain2 = 0;
    game -> currentPlayer = askCurrent(); // renvoie 0 ou 1 pour savoir a qui de jouer
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

int gameOver(Game* game) {

    // on verifie que le joueur actuel peut jouer son tour
    int i = 0;
    // on verifie que le joueur peut "nourrir" son adversaire (si il n'a plus de graine il ne pourra pas : inutile de verifier)
    if(game -> currentPlayer == 0){
        while(i < 6){
            if(game -> board_config[0][i] > i + 1) return 0; // Le joueur peut jouer : la partie n'est pas finie
            i++;
        }        
    } else {
        while(i < 6){
            if(game -> board_config[1][i] > 5 - i) return 0; // Le joueur peut jouer : la partie n'est pas finie
            i++;
        }
    }

    // La partie est terminee : il faut trouver le vainqueur
    int a = game -> gain1 - game -> gain2;
    switch (a) {
        case a < 0 :
            return 2; // le joueur 2 gagne
        break;
        case a == 0 :
            return 3; // aucun joueur ne gagne : match nul
        break;
        case a > 0 :
            return 1; // le joueur 1 gagne
        break; 
    }
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

/*    char ans2 = ' ';

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

        
        time_t secondes;
        struct tm timeExit;
        time(&secondes);
        timeExit = *localtime(&secondes);
        

        saveInList(file_list, game, dateCreation);
        printf(" listGames.txt has been completed\n");

        return 1;
    } */ //Si la partie est quittee avant d'etre finie, pas de gagnant
    return 0;
}

void nextStep(Game* game, int* caseSelected) {

    int current = (game -> currentPlayer); // on recupere le joueur qui a la main (0 ou 1)

    if (current == 0)
        printf("\n %s has choosen to play square %d \n", game -> joueur1, *caseSelected);
    else printf("\n %s has choosen to play square %d \n", game -> joueur2, *caseSelected);

    int j = *caseSelected-1;
    distributeSeeds(game -> board_config, current, j) 

    
    // on change la main pour le prochain tour
    (game -> currentPlayer)++;
    (game -> currentPlayer) %= 2;

    printf("\n");
    affichage(game);
}

void play_console() {

    printf(" ================ COMMANDS ================\n");
    printf(" To launch a new game, press n\n");
    printf(" To load form an existing game, press l\n");
    printf(" To save, press s\n");
    printf(" To quit, press q\n");
    printf(" To select a square, choose between 1 and 6\n");
    printf(" ==========================================\n\n");

    char file_save[NAME_FILE_SIZE] = "saved.txt";
    char file_list[NAME_FILE_SIZE] = "listGames.txt";

    fflush(stdin);

    char answer = ' ';
    int flag = 1; // pour quitter le jeu

    do {

        Game game;

        // on recupere les infos temporelles de sa creation
        time_t secondes;
        struct tm dateCreation;
        time(&secondes);
        dateCreation = *localtime(&secondes);

        // a remplacer par un switch et case break

        answer = getc(stdin); // on recupere une entree

        // on lance a new game
        if (answer == 'n') {

            loard_blank_game(file_list, &game, &dateCreation); // on initialise la struct game vide
            printf("\n ========================== THE GAME BEGINS =========================\n\n");
            affichage(&game); // on affiche le plateau
        }

        // on charge via une partie existante si elle existe
        if (answer == 'l') {

            // si le fichier de sauvergarde est vide, il faut creer une nouvelle partie
            if (isEmpty(file_save)) {

                printf("No data has been found, I'm launching a new game:\n");
                loard_blank_game(file_list, &game, &dateCreation); // on initialise la struct game vide
                printf("\n ========================== THE GAME BEGINS =========================\n\n");
                affichage(&game); // on affiche le plateau
            }

            // sinon on charge la partie enregistree
            else {

                // on recupere les infos temporelles de sa creation
                time_t secondes;
                struct tm dateCreation;
                time(&secondes);
                dateCreation = *localtime(&secondes);

                loard_saved_game(&game); // on initialise la struct game vide
                printf("\n ========================== THE GAME BEGINS =========================\n\n");
                affichage(&game);
            }
        }

        if (answer == '1' || answer == '2' || answer == '3' || answer == '4' || answer == '5' || answer == '6') {

            int caseSelected = answer - '0'; // char to int

            // on n'autorise pas a jouer une case vide
            if ((game.board_config)[game.currentPlayer][caseSelected-1] != 0) {
                nextStep(&game, &caseSelected);
            }
        }

        if (answer == 'q') {

            fflush(stdin); // pour vider le buffer de getc answer et pouvoir en faire un autre a la suite
            printf("Do you want to quit ? (y/n)\n");
            char confirm; // on recupere la confirmation
            confirm = getc(stdin);

            if (confirm == 'y') {

                // ajout de la partie dans listGames.txt
                saveInList(file_list, &game, &dateCreation);
                printf(" listGames.txt has been completed\n");

                // on affiche le vainqueur
                // ...

                flag = 0;
            }
            //fflush(stdin); // on vide le buffer confirm
        }

        if (answer == 's') {

            fflush(stdin);
            save(file_save, &game, &dateCreation);
            printf(" The game has been saved with success\n");
        }

        fflush(stdin); // on vide le buffer de answer (ou de confirm pour le cas 'q')

    } while (flag);
}


