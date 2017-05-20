/*
 * ia.c
 *
 * Created on: 16 mai 2017
 *     Author: Olivier
 */

#include "ia.h"
#include "movements.h"

short PlayIA() {
    short hole = 0;

    while(!(isFeeding(game.board_config[game.currentPlayer][hole], game.currentPlayer, hole)))
        hole = rand() % 6;
}
