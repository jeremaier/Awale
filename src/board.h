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
void BoardInit(short[][NB_HOLES]);

/**
 * Creation des zones cliquable du plateau de jeu
 */
void CreateClickableBoard(Clickable*, SDL_Renderer**);

/**
 * Boutons du plateau de jeu
 */
short Button11(SDL_Renderer**);

short Button12(SDL_Renderer**);

short Button13(SDL_Renderer**);

short Button14(SDL_Renderer**);

short Button15(SDL_Renderer**);

short Button16(SDL_Renderer**);

short Button21(SDL_Renderer**);

short Button22(SDL_Renderer**);

short Button23(SDL_Renderer**);

short Button24(SDL_Renderer**);

short Button25(SDL_Renderer**);

short Button26(SDL_Renderer**);

#endif // SRC_BOARD
