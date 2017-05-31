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

void BoardInit(short board[][NB_HOLES]) {
    short i, j;

    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;
}

void CreateClickableBoard(Clickable* clickableList, SDL_Renderer** renderer, TTF_Font** buttonFont, SDL_Color* color) {
	short i;
	short (*buttonFunction[NB_ROW * NB_HOLES])(SDL_Renderer** renderer) = {Button11, Button12, Button13, Button14, Button15, Button16, Button21, Button22, Button23, Button24, Button25, Button26};

	// Creation de tous les boutons pour les graines
	for(i = 0; i < NB_ROW * NB_HOLES; i++)
		CreateNewButton(HINIT + HSPACE * (i - (i / NB_HOLES) * NB_HOLES), VINIT + (i / NB_HOLES) * VSPACE, "sprites/hole.png", "", clickableList, renderer, buttonFunction[i], i + 1, BUTTON_TYPE_WITH_SURFACE, "0", 0);

	// Creation des boutons annexes
	CreateNewButton(SCREEN_WIDTH / 2, 68, "sprites/save.png", "sprites/saveOver.png", clickableList, renderer, OpenSaveMenu, 13, BUTTON_TYPE_WITH_OVER_AND_TEXT, "Sauver", 1);
	CreateNewButton(SCREEN_WIDTH / 2 + SCREEN_WIDTH, 68, "sprites/load.png", "sprites/loadOver.png", clickableList, renderer, OpenLoadMenu, 14, BUTTON_TYPE_WITH_OVER_AND_TEXT, "Charger", 1);
	CreateNewButton(SCREEN_WIDTH, 210, "sprites/restart.png", "sprites/restartOver.png", clickableList, renderer, Restart, 15, BUTTON_TYPE_WITH_OVER_AND_TEXT, "Recommencer", 1);

	// Choix des positions
	clickableList[13].textRect.x = clickableList[13].posX + 30;
	clickableList[14].textRect.x = clickableList[14].posX + 30;
	clickableList[13].textRect.y = clickableList[13].posY + 12;
	clickableList[14].textRect.y = clickableList[14].posY + 12;

	// Rafraichissement de l'ecriture des boutons
	RefreshText(renderer, buttonFont, &(clickableList[13].textRect), &(clickableList[13].textSurface), &(clickableList[13].textTexture), clickableList[13].text, *color, 0);
	RefreshText(renderer, buttonFont, &(clickableList[14].textRect), &(clickableList[14].textSurface), &(clickableList[14].textTexture), clickableList[14].text, *color, 0);
}

short Button11(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 0);
}

short Button12(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 1);
}

short Button13(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 2);
}

short Button14(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 3);
}

short Button15(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 4);
}

short Button16(SDL_Renderer** renderer) {
	return DistributeSeeds(0, 5);
}

short Button21(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 0);
}

short Button22(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 1);
}

short Button23(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 2);
}

short Button24(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 3);
}

short Button25(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 4);
}

short Button26(SDL_Renderer** renderer) {
	return DistributeSeeds(1, 5);
}
