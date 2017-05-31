/*
 * ia.c
 *
 * Created on: 16 mai 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "movements.h"
#include "ia.h"

short PlayIA() {
    short hole;

    do hole = rand() % 6;
    while(isFeeding(game.board_config[1][hole], 1, hole));

    return hole;
}
