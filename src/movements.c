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
	short seed_nbr = board[row][hole];
    board[row][hole] = 0;
    return seed_nbr;
}

void distributeSeeds(short board[][NB_HOLES], short row, short init) {
	short tmp_row = row;
	short seed_nbr = removeSeeds(board, tmp_row, init);
    int i = init;

    while(i < seed_nbr + init) {
    	if(row == 0 && NB_HOLES - i <= 1) {
    		i++;
    		board[tmp_row][i]++;
    	} else if(row == 0) {
    		tmp_row = 1;
    		board[tmp_row][i]++;
    	} else if(NB_HOLES - i <= 1) {
    		i--;
    		board[tmp_row][i]++;
    	} else {
    		tmp_row = 0;
    		board[tmp_row][i]++;
    	}
    }
}
