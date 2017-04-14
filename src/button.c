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

void CreateNewButton(int posX, int posY, char* path, Clickable* clickableList, SDL_Renderer** renderer, int sizeDivide, int index) {
	Clickable newButton;

    CreateTexture(path, &(newButton.surface), &(newButton.texture), renderer);
    newButton.type = BUTTON_TYPE_OPTIONS;
	newButton.sizeX = (newButton.surface -> w) / sizeDivide;
	newButton.sizeY = (newButton.surface -> h) / sizeDivide;
	newButton.posX = posX - newButton.sizeX;
	newButton.posY = posY;
	clickableList[index] = newButton;
}

void Action(int data) {
	if(data == 0) {

	}
}

void Click(int xMouse, int yMouse, Clickable* clickableList) {
	int i;

	for(i = 0; i < BUTTON_NUMBER; i++) {
		int isInButtonZone = xMouse >= clickableList[i].posX && xMouse <= clickableList[i].posX + clickableList[i].sizeX
				&& yMouse >= clickableList[i].posY && yMouse <= clickableList[i].posY + clickableList[i].sizeY;

		if(isInButtonZone)
			clickableList[i].Action();
	}
}
