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
void CreateClickableBoard(Clickable*, SDL_Renderer**);

/**
 * Boutons du plateau de jeu
 */
short button11(SDL_Renderer**);

short button12(SDL_Renderer**);

short button13(SDL_Renderer**);

short button14(SDL_Renderer**);

short button15(SDL_Renderer**);

short button16(SDL_Renderer**);

short button21(SDL_Renderer**);

short button22(SDL_Renderer**);

short button23(SDL_Renderer**);

short button24(SDL_Renderer**);

short button25(SDL_Renderer**);

short button26(SDL_Renderer**);

#endif // SRC_BOARD
