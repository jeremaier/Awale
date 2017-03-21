/*
 * test.c
 *
 *  Created on: 14 mars 2017
 *      Author: Olivier
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pour utiliser la fonction _sleep(temps en ms)
#include <time.h>
#include "const.h"
#include "tests.h"
#include <string.h>

void testBoardInit(short matrice[][NB_HOLES]) {
	printf("=== testBoardInit begin ===\n");
	int i, j;

	for(i = 0; i < NB_ROW; i++) {
		for(j = 0; j < NB_HOLES; j++)
			printf("%hd ", matrice[i][j]);

		printf("\n");
	}

	printf("=== testBoardInit end ===\n");
}

void testSave() {
    // on va travailler avec le fichier saved.txt
    char chemin[NAME_FILE_SIZE] = "saved.txt";

    // on recupere la date et l'heure actuelle
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on cree un nouveau jeu (configurations)
    Game game = {1, "Olive", "Tom", 5, 3, {{4,4,4,4,4,4},{4,4,4,4,4,4}}, &creationGame, 0, {0,1,0}};

    // on fait une pause de 3000ms
    _sleep(3000);

    // on sauvergade les configurations de la partie dans le chemin specifie
    save(chemin, &game, &creationGame);
}

void testSaveInList() {

    char chemin[NAME_FILE_SIZE] = "listGames.txt";

    // on recupere la date et l'heure actuelle
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on cree un nouveau jeu (configurations)
    Game game = {1, "olive", "tom", 5, 3, {{4,4,4,4,4,4},{4,4,4,4,4,4}}, &creationGame, 0, {1,16,7}};

    // on fait une pause de 3000ms
    _sleep(3000);

    saveInList(chemin, &game, &creationGame);
}

void gameToString(Game* game, struct tm* creation) {

    printf(" === BEGIN AFFICHAGE GAME ===\n");
    printf(" game number: %d\n", game -> gameNumber);
    printf(" name player1: %s\n", game -> joueur1);
    printf(" name player2: %s\n", game -> joueur2);
    printf(" gain1: %d\n", game -> gain1);
    printf(" gain2: %d\n", game -> gain2);
    printf(" board configuration:\n");
    int i,j;
    for (i=0;i<NB_ROW; i++) {
        for (j=0; j<NB_HOLES; j++) {
            printf(" %d ", (game->board_config)[i][j]);
        } printf("\n");
    }
    printf(" current player: %d\n", game -> currentPlayer);
    //timeElapsedToString(creation);
    printf(" time spent : %d:%d:%d\n", (game -> timeSpent)[0], (game -> timeSpent)[1], (game -> timeSpent)[2]);
    printf(" === END AFFICHAGE GAME ===\n");
}

void playNewGame_c() {

    // on cree la struct game
    Game game;

    // on demande le nom des joueurs et on complete la struct Game:
    //askName(game.joueur1);
    //askName(game.joueur2);

    // on recupere les infos temporelles de sa creation
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on initialise la struct Game
    char file_list[NAME_FILE_SIZE] = "listGames.txt";
    loard_blank_game(file_list, &game, &creationGame);

    /** test1, affichage de Game game:*/
    gameToString(&game, &creationGame);

    /**test2, sauvegarde dans saved.txt*/
    char file_save[NAME_FILE_SIZE] = "saved.txt";
    save(file_save, &game, &creationGame);

    /**test3, ecriture dans listGames.txt*/
    saveInList(file_list, &game, &creationGame);
}

void playSavedGame_c() {

    // on cree une struct game
    Game game;

    //on charge les donnees enregistree dans saved.txt
    loard_saved_game(&game);

    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    /** test2, affichage de Game game:*/
    gameToString(&game, &creationGame);
}
