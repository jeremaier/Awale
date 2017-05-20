/**
* Author : Olivier Benard
* Created on : March 17, 2017
**/

#include "ia.h"
#include "movements.h"

short joue_aleatoire () {
    short hole = 0;
    while(!(isFeeding(game.board_config[game.currentPlayer][hole], game.currentPlayer, hole))){
        hole = rand()%6;
    }
}
