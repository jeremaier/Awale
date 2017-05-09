/*
 * movements.c
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "game.h"
#include "movements.h"

short RemoveSeeds(const short row, const short hole) {
	const short seedsNbr = game.board_config[row][hole];

	if(game.currentPlayer != row)
		return -2;
	else if(seedsNbr == 0)
		return -1;

	game.board_config[row][hole] = 0;
	return seedsNbr;
}

short DistributeSeeds(const short row, const short init) {
	short seedsNbr = RemoveSeeds(row, init);
	short tmpRow = row;
	short i = init;
	short cpt;

	for(cpt = 0; cpt < seedsNbr; cpt++) {
		short endLine = NB_HOLES - i;

		if(tmpRow == 0) {
			if(endLine >= 6)
				tmpRow = 1;
			else i--;
		} else {
			if(endLine <= 1)
				tmpRow = 0;
			else i++;
		}

		if(cpt != 11)
			game.board_config[tmpRow][i]++;
		else seedsNbr++;


	}

	endHole = i;

	if(game.currentPlayer != tmpRow)
		inOpponentRow = 0;
	else inOpponentRow = 1;

	if(seedsNbr > 11)
		return seedsNbr--;

	return seedsNbr;
}

void TakeWonSeeds(const short initSeedsNbr) {
	const short row = (game.currentPlayer + 1) % 2;
	short j = initHole;

	// On regarde les cases a gauche de celle ou la derniere graine a ete posee
	while(j >= 0 && (game.board_config[row][j] == 2 || game.board_config[row][j] == 3)){
		game.gains[game.currentPlayer] += game.board_config[row][j];
		game.board_config[row][j] = 0;
		j--;
	}

	j = initHole + 1;

	// On regarde les cases a gauche de celle ou la derniere graine a ete posee
	while(j < NB_HOLES && (game.board_config[row][j] == 2 || game.board_config[row][j] == 3)){
		game.gains[game.currentPlayer] += game.board_config[row][j];
		game.board_config[row][j] = 0;
		j++;
	}
}

