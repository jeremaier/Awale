/*
 * menus.c
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "SDLwindow.h"
#include "menus.h"

void CreateButtons(const char* buttonsImg[buttonNumber], const char* buttonsImgOver[buttonNumber], void (*buttonsFonction[buttonNumber])(SDL_Renderer** renderer), Clickable* clickableList, SDL_Renderer** renderer, short sizeDivideButtons, int horizontalSpace, int verticalSpace, int xFirstPos, int yFirstPos, ButtonType buttonType, char* text) {
	short i;

	AllocationClickableList();

	for(i = 0; i < buttonNumber; i++)
		CreateNewButton(xFirstPos + horizontalSpace * i, yFirstPos + verticalSpace * i, buttonsImg[i], buttonsImgOver[i], clickableList, renderer, buttonsFonction[i], sizeDivideButtons, i + 1, buttonType, text);
}

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		const Clickable button = clickableList[i + 1];

		if(button.type != BUTTON_TYPE_EMPTY)
			Display(*renderer, button.texture, button.posX, button.posY, button.sizeX, button.sizeY);
	}
}

void OpenOptionsMenu(SDL_Renderer** renderer) {
	buttonNumber = BUTTON_NUMBER_OPTIONS;
	menuNumber = 1;
	SDL_Surface* optionsSurface = NULL;
	SDL_Texture* optionsTexture = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};

	AllocationClickableList();
	const char *buttonsImg[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	const char *buttonsImgOver[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	void (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer) = {OpenSaveMenu, OpenLoadMenu, OpenScoreMenu};

	CreateButtons(buttonsImg, buttonsImgOver, buttonsFonction, clickableList, renderer, 3, 300, 0, 250, 50, BUTTON_TYPE_WITH_SURFACE_OVER, "");
    CreateTexture("sprites/backOptions.png", &optionsSurface, &optionsTexture, renderer);

    Display(*renderer, optionsTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	DisplayButtons(renderer, clickableList, buttonNumber);
}

void OpenSaveMenu(SDL_Renderer** renderer) {

}

void OpenLoadMenu(SDL_Renderer** renderer) {

}

void OpenScoreMenu(SDL_Renderer** renderer) {

}

void AllocationClickableList() {
	if (clickableList != 0)
		clickableList = (Clickable*) realloc(clickableList, buttonNumber * sizeof(Clickable));
	else clickableList = (Clickable*) malloc(buttonNumber * sizeof(Clickable));
}
