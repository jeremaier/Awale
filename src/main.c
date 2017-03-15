/*
 * main.c
 *
 *  Created on: 1 mars 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "main.h"

#include "tests.h"

// short au lieu de int car faibles unitees
short board[NB_ROW][NB_HOLES];

// initialisation de la matrice
void boardInit() {
    short player;

    //error: 'for' loop initial declarations are only allowed in C99 or C11 mode
    int i; int j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;

    // on ne gere pas les erreurs d'entrees car ce sera des boutons
    printf("Quel joueur commence en premier ? (0/1)\n");
    scanf("%hd", &player); // %hd used for a short int
}

int main(void) {
    boardInit();
    // =========== TESTS ==========
    testBoardInit(board);
    return 0;
}
