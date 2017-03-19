/*
 * test.c
 *
 *  Created on: 14 mars 2017
 *      Author: Olivier
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // fct sleep
#include <time.h>
#include "const.h"
#include "tests.h"

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
    Game game = {1, "olive", "tom", 5, 3, {{4,4,4,4,4,4},{4,4,4,4,4,4}}, &creationGame, 0};

    // on fait une pause de 3000ms
    _sleep(3000);

    // on sauvergade les configurations de la partie dans le chemin specifie
    save(chemin, &game, &creationGame);
}

void testSaveGame() {

    char chemin[NAME_FILE_SIZE] = "listGames.txt";

    // on recupere la date et l'heure actuelle
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);

    // on cree un nouveau jeu (configurations)
    Game game = {1, "olive", "tom", 5, 3, {{4,4,4,4,4,4},{4,4,4,4,4,4}}, &creationGame, 0};

    // on fait une pause de 3000ms
    _sleep(3000);

    saveGame(chemin, &game, &creationGame);
}

void gameToString(Game* g) {
    printf("Game number %d: \n", g.gameNumber);
}
