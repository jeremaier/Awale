/*
 * movements.c
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "movements.h"

short removeSeeds(short board[][NB_HOLES], short row, short hole) {
	short const seed_nbr = board[row][hole];
    board[row][hole] = 0;
    return seed_nbr;
}

void distributeSeeds(short board[][NB_HOLES], short row, short init) {
    short const seedsNbr = removeSeeds(board, row, init);
	short tmpRow = row;
    short i = init;
    short cpt;

    for(cpt = 0; cpt < seedsNbr; cpt++) {
    	int endLine = NB_HOLES - i;

    	if(tmpRow == 0) {
    		if(endLine >= 6)
    			tmpRow = 1;
    		else i--;
    	} else {
    		if(endLine <= 1)
        		tmpRow = 0;
			else i++;
    	}

    	board[tmpRow][i]++;
    }
}
