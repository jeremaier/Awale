/*
 * button.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDLwindow.h"
#include "menus.h"
#include "const.h"
#include "button.h"

Clickable CreateNewButton(int posX, int posY, const char* path, const char* pathOver, Clickable* clickableList, SDL_Renderer** renderer, short (*action)(SDL_Renderer**), short index, ButtonType buttonType, char* text) {
	Clickable newButton;

	if(buttonType != BUTTON_TYPE_EMPTY) {
		CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);
		newButton.sizeX = (newButton.surface -> w);
		newButton.sizeY = (newButton.surface -> h);
	} else {
		newButton.sizeX = 0;
		newButton.sizeY = 0;
	}

	if(buttonType == BUTTON_TYPE_WITH_SURFACE_OVER || buttonType == BUTTON_TYPE_WITH_OVER_AND_TEXT)
		CreateTexture(pathOver, &(newButton.surfaceOver), &(newButton.textureOver), renderer);

    newButton.type = buttonType;
	newButton.posX = posX - newButton.sizeX;
	newButton.posY = posY;
	newButton.data = renderer;
	newButton.Action = action;
	newButton.text = text;
	clickableList[index] = newButton;

	return newButton;
}

Clickable IsOverButton(int xMouse, int yMouse, Clickable* clickableList) {
	short i, first = 0, last;

	if(menuNumber == 1)
		last = buttonNumber - 1;
	else if(menuNumber == 0)
		last = buttonNumber - 2;

	for(i = first; i < last; i++) {
		const Clickable button = clickableList[i + 1];
		const int isInButtonZone = xMouse >= button.posX && xMouse <= button.posX + button.sizeX && yMouse >= button.posY && yMouse <= button.posY + button.sizeY;

		if(isInButtonZone)
			return button;
	}

	return clickableList[0];
}

void AllocationClickableList() {
	if (clickableList != 0)
		clickableList = (Clickable*) realloc(clickableList, buttonNumber * sizeof(Clickable));
	else clickableList = (Clickable*) malloc(buttonNumber * sizeof(Clickable));
}

void FreeUpMemoryButton(Clickable* clickableList) {
	short i;

	for(i = 0; i < BUTTON_NUMBER_BOARD; i++) {
		if(clickableList[i].type != BUTTON_TYPE_EMPTY) {
			SDL_DestroyTexture(clickableList[i].texture);
			SDL_FreeSurface(clickableList[i].surface);
		}

		if(clickableList[i].type == BUTTON_TYPE_WITH_SURFACE_OVER || clickableList[i].type == BUTTON_TYPE_WITH_OVER_AND_TEXT) {
			SDL_DestroyTexture(clickableList[i].textureOver);
			SDL_FreeSurface(clickableList[i].surfaceOver);
		}

		if(clickableList[i].type == BUTTON_TYPE_WITH_OVER_AND_TEXT)
			SDL_DestroyTexture(clickableList[i].textTexture);
	}
}
