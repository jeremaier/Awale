/*
 * main.c
 *
 *  Created on: 15 mars 2017
 *      Author: Olivier
 *	Completed on : 
 *		by : Valentin
 */
#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "ask.h"
#include "time.h"
#include "write.h"
#include "read.h"
#include "board.h"

void boardInit(short board[][NB_HOLES]) {

    int i, j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;
}