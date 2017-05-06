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
#include "game.h"

short removeSeeds(const short row, const short hole) {
	const short seedsNbr = game.board_config[row][hole];

	if(game.currentPlayer != row)
		return -2;
	else if(seedsNbr == 0)
		return -1;

	game.board_config[row][hole] = 0;
	return seedsNbr;
}

short distributeSeeds(const short row, const short init) {
	short seedsNbr = removeSeeds(row, init);
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

	return seedsNbr;
}

void takeWonSeeds(const short hole) {
	short row = (game.currentPlayer + 1) % 2;

	short j = hole;

	// On regarde les cases à gauche de celle ou la derniere graine a ete posee

	while(j >=0 && (game.board_config[row][j] == 2 || game.board_config[row][j] == 3)){
		game.gain[game.currentPlayer] += game.board_config[row][j];
		game.board_config[row][j] = 0;
		j--;
	}

	j = hole + 1;

	// On regarde les cases à gauche de celle ou la derniere graine a ete posee

	while(j <NB_HOLES && (game.board_config[row][j] == 2 || game.board_config[row][j] == 3)){
		game.gain[game.currentPlayer] += game.board_config[row][j];
		game.board_config[row][j] = 0;
		j++;
	}
}

