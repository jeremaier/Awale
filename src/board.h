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
int button11(SDL_Renderer**);

int button12(SDL_Renderer**);

int button13(SDL_Renderer**);

int button14(SDL_Renderer**);

int button15(SDL_Renderer**);

int button16(SDL_Renderer**);

int button21(SDL_Renderer**);

int button22(SDL_Renderer**);

int button23(SDL_Renderer**);

int button24(SDL_Renderer**);

int button25(SDL_Renderer**);

int button26(SDL_Renderer**);

#endif // SRC_BOARD
