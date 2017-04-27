/*
 * menus.c
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "SDLwindow.h"
#include "menus.h"

void CreateButtons(const char* buttonsImg[BUTTON_NUMBER_OPTIONS], const char* buttonsImgOver[BUTTON_NUMBER_OPTIONS], void (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer), Clickable* clickableList, short len, SDL_Renderer** renderer, short sizeDivideButtons, int horizontalSpace, int verticalSpace, int xFirstPos, int yFirstPos) {
	short i;

	for(i = 0; i < len; i++)
		CreateNewButton(xFirstPos + horizontalSpace * i, yFirstPos + verticalSpace * i, buttonsImg[i], buttonsImgOver[i], clickableList, renderer, buttonsFonction[i], sizeDivideButtons, i);
}

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++)
	    Display(*renderer, clickableList[i].texture, clickableList[i].posX, clickableList[i].posY, clickableList[i].sizeX, clickableList[i].sizeY);
}

void eventLoop(Clickable* clickableList) {
	/*short close = 0;
	SDL_Event event;
	int xMouse = 0, yMouse = 0;

    while(!close) {
    	while(SDL_PollEvent(&event)) {
    		xMouse = event.motion.x;
    		yMouse = event.motion.y;
    	}

        //if(event.type == SDL_MOUSEBUTTONDOWN)
            //Click(xMouse, yMouse, clickableList);
    }
    //*/
}

void OpenOptionsMenu(SDL_Renderer** renderer) {
	/*SDL_Surface* optionsSurface = NULL;
	SDL_Texture* optionsTexture = NULL;
	Clickable clickableList[BUTTON_NUMBER_OPTIONS];
	const char *buttonsImg[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	const char *buttonsImgOver[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	void (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer) = {OpenSaveMenu, OpenLoadMenu, OpenScoreMenu};

	CreateButtons(buttonsImg, buttonsImgOver, buttonsFonction, clickableList, BUTTON_NUMBER_OPTIONS, renderer, 4, 0, 0, 30, 0);
    CreateTexture("sprites/board+background.png", &optionsSurface, &optionsTexture, renderer);

    Display(*renderer, optionsTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	DisplayButtons(renderer, clickableList, BUTTON_NUMBER_OPTIONS);

    eventLoop(clickableList);

    freeUpMemoryButton(clickableList, BUTTON_NUMBER_OPTIONS);*/
}

void OpenSaveMenu(SDL_Renderer** renderer) {

}

void OpenLoadMenu(SDL_Renderer** renderer) {

}

void OpenScoreMenu(SDL_Renderer** renderer) {

}
