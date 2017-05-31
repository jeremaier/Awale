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

short isFeeding(const short seedsNbr, const short row, const short init) {
	if(row == 0 && (init >= seedsNbr))
		return 1;
	else if (row == 1 && (NB_HOLES - init > seedsNbr))
		return 1;
	else return 0;
}

short RemoveSeeds(const short row, const short hole) {
	const short seedsNbr = game.board_config[row][hole];

	if(game.currentPlayer != row)
		return -3;
	else if(seedsNbr == 0)
		return -2;
	else if(isFeeding(seedsNbr, row, hole))
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
		inOpponentRow = 1;
	else inOpponentRow = 0;

	if(seedsNbr > 11)
		return seedsNbr--;

	return seedsNbr;
}

void TakeWonSeeds(const short initSeedsNbr) {
	const short opponentRow = (game.currentPlayer + 1) % 2;
	short j = endHole;

	if(inOpponentRow) {
		if (opponentRow) {
			// Joueur du haut : on regarde les cases a gauche de celle ou la derniere graine a ete posee
			while(j >= 0 && (game.board_config[opponentRow][j] == 2 || game.board_config[opponentRow][j] == 3)) {
				game.gains[game.currentPlayer] += game.board_config[opponentRow][j];
				game.board_config[opponentRow][j] = 0;
				j--;
			}
		} else {
			// Joueur du bas : on regarde les cases a droite de celle ou la derniere graine a ete posee
			while(j < NB_HOLES && (game.board_config[opponentRow][j] == 2 || game.board_config[opponentRow][j] == 3)) {
				game.gains[game.currentPlayer] += game.board_config[opponentRow][j];
				game.board_config[opponentRow][j] = 0;
				j++;
			}
		}
	}
}
