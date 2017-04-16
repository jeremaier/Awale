/*
 * button.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>

#include "SDLwindow.h"
#include "const.h"
#include "button.h"

Clickable CreateNewButton(int posX, int posY, char* path, Clickable* clickableList, SDL_Renderer** renderer, void (*action)(SDL_Renderer**), short sizeDivide, short index) {
	Clickable newButton;

    CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);
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

void Click(int xMouse, int yMouse, Clickable* clickableList) {
	int i;

	for(i = 0; i < BUTTON_NUMBER_BOARD; i++) {
		const int isInButtonZone = xMouse >= clickableList[i].posX && xMouse <= clickableList[i].posX + clickableList[i].sizeX
				&& yMouse >= clickableList[i].posY && yMouse <= clickableList[i].posY + clickableList[i].sizeY;

		if(isInButtonZone)
			clickableList[i].Action(clickableList[i].data);
	}
}
