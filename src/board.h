/*
 * main.h
 *
 *  Created on: 15 mars 2017
 *      Author: Olivier
 */

#ifndef SRC_BOARD_H
#define SRC_BOARD_H

#include "const.h"
#include "button.h"
#include "SDLwindow.h"

/**
 * Initialisation du plateau de jeu avec selection du joueur et le nombre de graines par trou
 */
void boardInit(short[][NB_HOLES]);

/**
 * Creation des zones cliquable du plateau de jeu
 */
void CreateClickableBoard(Clickable*);

#endif // SRC_BOARD
