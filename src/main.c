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

short board[NB_ROW][NB_HOLES];

void boardInit() {
    short player;

    for(int i = 0; i < NB_ROW; i++)
    	for(int j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;

    printf("Quel joueur commence en premier? (bas(0), haut(1))");
    scanf("%hd", &player);
}

int main(void) {
    boardInit();
    return 0;
}
