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
#include <string.h>
#include <windows.h>

#include "write.h"
#include "read.h"
#include "tests.h"

void TestBoardInit(short matrice[][NB_HOLES]) {
	printf("=== testBoardInit begin ===\n");
	short i, j;

	for(i = 0; i < NB_ROW; i++) {
		for(j = 0; j < NB_HOLES; j++)
			printf("%hd ", matrice[i][j]);

		printf("\n");
	}

	printf("=== testBoardInit end ===\n");
}

void TestSave(char* path) {
    // on recupere la date et l'heure actuelle
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on cree un nouveau jeu (configurations)
    Game game = {1, "Olive", "Tom", {5, 3}, {{4, 4, 4, 4, 4, 4}, {4, 4, 4, 4, 4, 4}}, &creationGame, 0, {0, 1, 0}};

    // on fait une pause de 3s
    Sleep(3000);

    // on sauvegarde les configurations de la partie dans le chemin specifie
    Save(path, &game, &creationGame);
}

void GameToString(Game* game, struct tm* creation) {
    short i, j;

    printf(" === BEGIN AFFICHAGE GAME ===\n");
    printf(" game number: %d\n", game -> gameNumber);
    printf(" name player1: %s\n", game -> joueur1);
    printf(" name player2: %s\n", game -> joueur2);
    printf(" gain1: %d\n", game -> gains[0]);
    printf(" gain2: %d\n", game -> gains[1]);
    printf(" board configuration:\n");

    for (i = 0; i < NB_ROW; i++) {
        for (j = 0; j < NB_HOLES; j++)
            printf(" %d ", (game -> board_config)[i][j]);

        printf("\n");
    }

    printf(" current player: %d\n", game -> currentPlayer);
    //timeElapsedToString(creation);
    printf(" time spent : %d:%d:%d\n", (game -> timeSpent)[0], (game -> timeSpent)[1], (game -> timeSpent)[2]);
    printf(" === END DISPLAY GAME ===\n");
}

void PlayNewGame() {
    // on recupere les infos temporelles de sa creation
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on initialise la struct Game
    char file_list[NAME_FILE_SIZE] = "listGames.txt";
    LoadBlankGame(file_list, &creationGame);

    /** test1, affichage de Game game:*/
    GameToString(&game, &creationGame);

    /**test2, sauvegarde dans saved.txt*/
    char file_save[NAME_FILE_SIZE] = "saved.txt";
    Save(file_save, &game, &creationGame);

    /**test3, ecriture dans listGames.txt*/
    SaveInList(file_list, &creationGame);
}

void PlaySavedGame() {
    //on charge les donnees enregistree dans saved.txt
    LoadSavedGame(&game);

    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    /** test2, affichage de Game game:*/
    GameToString(&game, &creationGame);
}
