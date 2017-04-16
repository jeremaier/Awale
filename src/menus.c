/*
 * menus.c
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "SDLwindow.h"
#include "menus.h"

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len, int verticalSpace, int horizontalSpace, int xFirstPos, int yFirstPos) {
	short i;

	for(i = 0; i < len; i++)
	    Display(*renderer, clickableList[i].texture, clickableList[i].surface, 0, 0, 0, 0);
}

void eventLoop(Clickable* clickableList) {
	short close = 0;
	SDL_Event event;
	int xMouse = 0, yMouse = 0;

    while(!close) {
    	while(SDL_PollEvent(&event)) {
    		xMouse = event.motion.x;
    		yMouse = event.motion.y;
    	}

        if(event.type == SDL_MOUSEBUTTONDOWN)
            Click(xMouse, yMouse, clickableList);
    }
}

void freeUpMemory(Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		SDL_DestroyTexture(clickableList[i].texture);
		SDL_FreeSurface(clickableList[i].surface);
	}
}

void OpenOptionsMenu(SDL_Renderer** renderer) {
	Clickable clickableList[BUTTON_NUMBER_OPTIONS];

	const short sizeDivideButtons = 4;
	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/save.png", clickableList, renderer, OpenSaveMenu, sizeDivideButtons, 0);
	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/load.png", clickableList, renderer, OpenLoadMenu, sizeDivideButtons, 1);
	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/score.png", clickableList, renderer, OpenScoreMenu, sizeDivideButtons, 2);

	DisplayButtons(renderer, clickableList, BUTTON_NUMBER_OPTIONS, 0, 0, 0, 0);
    eventLoop(clickableList);

    freeUpMemory(clickableList, BUTTON_NUMBER_OPTIONS);
}

void OpenSaveMenu(SDL_Renderer** renderer) {

}

void OpenLoadMenu(SDL_Renderer** renderer) {

}

void OpenScoreMenu(SDL_Renderer** renderer) {

}
