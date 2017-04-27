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
#include "const.h"
#include "button.h"

Clickable CreateNewButton(int posX, int posY, const char* path, const char* pathOver, Clickable* clickableList, SDL_Renderer** renderer, void (*action)(SDL_Renderer**), short sizeDivide, short index) {
	Clickable newButton;

	if(strcmp(path, ""))
		CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);

	if(strcmp(pathOver, ""))
		CreateTexture(pathOver, &(newButton.surfaceOver), &(newButton.textureOver), renderer);

    newButton.type = BUTTON_TYPE_OPTIONS;
	newButton.sizeX = (newButton.surface -> w) / sizeDivide;
	newButton.sizeY = (newButton.surface -> h) / sizeDivide;
	newButton.posX = posX - newButton.sizeX;
	newButton.posY = posY;
	newButton.data = renderer;
	newButton.Action = action;
	clickableList[index] = newButton;

	return newButton;
}

Clickable Over(int xMouse, int yMouse, Clickable* clickableList) {
	short i;

	for(i = 0; i < BUTTON_NUMBER_BOARD; i++) {
		const int isInButtonZone = xMouse >= clickableList[i].posX && xMouse <= clickableList[i].posX + clickableList[i].sizeX
								&& yMouse >= clickableList[i].posY && yMouse <= clickableList[i].posY + clickableList[i].sizeY;

		if(isInButtonZone)
			return clickableList[i];
	}

	return clickableList[13];
}

void freeUpMemoryButton(Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		SDL_DestroyTexture(clickableList[i].texture);
		SDL_DestroyTexture(clickableList[i].textureOver);
		SDL_FreeSurface(clickableList[i].surface);
		SDL_FreeSurface(clickableList[i].surfaceOver);
	}
}
