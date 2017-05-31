/*
 * button.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "game.h"
#include "board.h"

Clickable CreateNewButton(int posX, int posY, const char* path, const char* pathOver, Clickable* clickableList, SDL_Renderer** renderer, short (*action)(SDL_Renderer**), short index, ButtonType buttonType, const char* text, const short center) {
	Clickable newButton;

	// Creation des surfaces de texture en fonction du type de bouton
	if(buttonType != BUTTON_TYPE_EMPTY) {
		CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);
		newButton.sizeX = (newButton.surface -> w);
		newButton.sizeY = (newButton.surface -> h);
	} else {
		newButton.sizeX = 0;
		newButton.sizeY = 0;
	}

	// Creation de la texture
	if(buttonType == BUTTON_TYPE_WITH_SURFACE_OVER || buttonType == BUTTON_TYPE_WITH_OVER_AND_TEXT)
		CreateTexture(pathOver, &(newButton.surfaceOver), &(newButton.textureOver), renderer);

	// On centre ou pas le bouton au milieu d'une certaine position
	if(center == 1)
		newButton.posX = posX / 2 - newButton.sizeX / 2;
	else newButton.posX = posX - newButton.sizeX;

	newButton.type = buttonType;
	newButton.posY = posY;
	newButton.data = renderer;
	newButton.Action = action;
	newButton.text = text;
	clickableList[index] = newButton;

	return newButton;
}

Clickable IsOverButton(int xMouse, int yMouse, Clickable* clickableList) {
	short i, first = 0, last = BUTTON_NUMBER;

	if(menuNumber == 0)
		last -= 1;
	else if(menuNumber == 1)
		first = 14;

	// On parcours les zones de chaque bouton pour savoir si on est au dessus avec sa souris
	for(i = first; i < last - 1; i++) {
		const Clickable button = clickableList[i + 1];
		const int isInButtonZone = xMouse >= button.posX && xMouse <= button.posX + button.sizeX && yMouse >= button.posY && yMouse <= button.posY + button.sizeY;

		if(isInButtonZone)
			return button;
	}

	return clickableList[0];
}

Clickable CreateBoardButtons(SDL_Renderer** renderer, TTF_Font** buttonFont, SDL_Color* color) {
	clickableList = (Clickable*) malloc(BUTTON_NUMBER * sizeof(Clickable));
	CreateClickableBoard(clickableList, renderer, buttonFont, color);

	return CreateNewButton(0, 0, "", "", clickableList, renderer, NULL, 0, BUTTON_TYPE_EMPTY, "", 0);
}

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		const Clickable button = clickableList[i + 1];

		if(button.type != BUTTON_TYPE_EMPTY)
			Display(*renderer, button.texture, button.posX, button.posY, button.sizeX, button.sizeY, 1);
	}
}

void FreeUpMemoryButton(Clickable* clickableList) {
	short i;

	for(i = 0; i < BUTTON_NUMBER; i++) {
		if(clickableList[i].type != BUTTON_TYPE_EMPTY) {
			SDL_DestroyTexture(clickableList[i].texture);
			SDL_FreeSurface(clickableList[i].surface);
		}

		if(clickableList[i].type == BUTTON_TYPE_WITH_SURFACE_OVER || clickableList[i].type == BUTTON_TYPE_WITH_OVER_AND_TEXT) {
			SDL_DestroyTexture(clickableList[i].textureOver);
			SDL_FreeSurface(clickableList[i].surfaceOver);
		}

		if(clickableList[i].type == BUTTON_TYPE_WITH_OVER_AND_TEXT && i != 15)
			SDL_DestroyTexture(clickableList[i].textTexture);
	}
}
