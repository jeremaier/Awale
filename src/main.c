/*
 * main.c
 *
 *  Created on: 1 mars 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include "const.h"

const short NB_HOLES;

void boardInit(short holes) {
    short player;
    printf("Quel joueur commence en premier? (bas(0), haut(1))");
    scanf("%i", &player);
    printf("Combien de trou par rangees?");
    scanf("%i", &NB_HOLES);
    short board[NB_ROW][NB_HOLES] = NB_SEED_INIT;
}

int main(void) {
	NB_HOLES = 5;

    boardInit(NB_HOLES);
    return 0;
}
