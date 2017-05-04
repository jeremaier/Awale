/*
 * main.c
 *
 *  Created on: 15 mars 2017
 *      Author: Olivier
 *	Completed on : 
 *		by : Valentin
 */

#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "movements.h"
#include "menus.h"
#include "board.h"

void boardInit(short board[][NB_HOLES]) {
    short i, j;

    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;
}

void CreateClickableBoard(Clickable* clickableList, SDL_Renderer** renderer) {
	short i;
	short (*buttonFunction[NB_ROW * NB_HOLES])(SDL_Renderer** renderer) = {button11, button12, button13, button14, button15, button16, button21, button22, button23, button24, button25, button26};

	for(i = 0; i < NB_ROW * NB_HOLES; i++)
		CreateNewButton(HINIT + HSPACE * (i - (i / NB_HOLES) * NB_HOLES), VINIT + (i / NB_HOLES) * VSPACE, "sprites/hole3.png", "", clickableList, renderer, buttonFunction[i], i + 1, BUTTON_TYPE_WITH_SURFACE, "0");

	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/options.png", "sprites/optionsOver.png", clickableList, renderer, OpenOptionsMenu, 13, BUTTON_TYPE_WITH_SURFACE_OVER, "");
}

short button11(SDL_Renderer** renderer) {
	return distributeSeeds(0, 0);
}

short button12(SDL_Renderer** renderer) {
	return distributeSeeds(0, 1);
}

short button13(SDL_Renderer** renderer) {
	return distributeSeeds(0, 2);
}

short button14(SDL_Renderer** renderer) {
	return distributeSeeds(0, 3);
}

short button15(SDL_Renderer** renderer) {
	return distributeSeeds(0, 4);
}

short button16(SDL_Renderer** renderer) {
	return distributeSeeds(0, 5);
}

short button21(SDL_Renderer** renderer) {
	return distributeSeeds(1, 0);
}

short button22(SDL_Renderer** renderer) {
	return distributeSeeds(1, 1);
}

short button23(SDL_Renderer** renderer) {
	return distributeSeeds(1, 2);
}

short button24(SDL_Renderer** renderer) {
	return distributeSeeds(1, 3);
}

short button25(SDL_Renderer** renderer) {
	return distributeSeeds(1, 4);
}

short button26(SDL_Renderer** renderer) {
	return distributeSeeds(1, 5);
}
