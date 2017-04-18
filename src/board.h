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
void button11(SDL_Renderer**);

void button12(SDL_Renderer**);

void button13(SDL_Renderer**);

void button14(SDL_Renderer**);

void button15(SDL_Renderer**);

void button16(SDL_Renderer**);

void button21(SDL_Renderer**);

void button22(SDL_Renderer**);

void button23(SDL_Renderer**);

void button24(SDL_Renderer**);

void button25(SDL_Renderer**);

void button26(SDL_Renderer**);

#endif // SRC_BOARD
