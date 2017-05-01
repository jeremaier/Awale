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

Clickable CreateNewButton(int posX, int posY, const char* path, const char* pathOver, Clickable* clickableList, SDL_Renderer** renderer, void (*action)(SDL_Renderer**), short sizeDivide, short index, ButtonType buttonType, char* text) {
	Clickable newButton;

	if(buttonType != BUTTON_TYPE_EMPTY) {
		CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);
		newButton.sizeX = (newButton.surface -> w) / sizeDivide;
		newButton.sizeY = (newButton.surface -> h) / sizeDivide;
	}

	if(buttonType == BUTTON_TYPE_WITH_SURFACE_OVER)
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

Clickable Over(int xMouse, int yMouse, Clickable* clickableList) {
	short i;

	for(i = 0; i < buttonNumber; i++) {
		const Clickable button = clickableList[i + 1];
		const int isInButtonZone = xMouse >= button.posX && xMouse <= button.posX + button.sizeX && yMouse >= button.posY && yMouse <= button.posY + button.sizeY;

		if(isInButtonZone)
			return button;
	}

	return clickableList[0];
}

void freeUpMemoryButton(Clickable* clickableList) {
	short i;

	for(i = 0; i < BUTTON_NUMBER_BOARD; i++) {
		if(clickableList[i].type != BUTTON_TYPE_EMPTY) {
			SDL_DestroyTexture(clickableList[i].texture);
			SDL_FreeSurface(clickableList[i].surface);
		}

		if(clickableList[i].type == BUTTON_TYPE_WITH_SURFACE_OVER) {
			SDL_DestroyTexture(clickableList[i].textureOver);
			SDL_FreeSurface(clickableList[i].surfaceOver);
		}
	}
}
