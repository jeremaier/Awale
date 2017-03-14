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

    //error: 'for' loop initial declarations are only allowed in C99 or C11 mode|
    int i; int j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;

    // pour gerer les erreurs d'entree
    do {
        printf("Quel joueur commence en premier? [bas(0),haut(1)]\n"); // pk pas l'inverser ? cf. index matrix
        scanf("%hd", &player); // %hd used for a short int
    } while (player != 0 && player != 1);
}

int main(void) {
    //boardInit();
    // =========== TESTS ==========
    int matrice[NB_ROW][NB_HOLES];
    int i, j;
    int n=0;
    for (i=0; i<NB_ROW; i++) {
        for (j=0; j<NB_HOLES; j++) {
            matrice[i][j] = n;
            n++;
        }
    }
    testBoardInit(matrice);
    return 0;
}
