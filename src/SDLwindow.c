/*
 * SDLwindow.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "button.h"
#include "SDLwindow.h"

int SDLError(char* message) {
    printf(message, SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}

void CreateTexture(char* path, SDL_Surface** surface, SDL_Texture** texture, SDL_Renderer** renderer) {
    *surface = IMG_Load(path);
    *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
}

void Display(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Surface* surface, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

int LaunchWindow(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** fontSurface, SDL_Texture** fontTexture) {
	short quit = 0;
	int xMouse = 0, yMouse = 0;
	SDL_Event event;
	SDL_Surface* boardSurface = NULL;
	SDL_Texture* boardTexture = NULL;
	Clickable clickableList[BUTTON_NUMBER];

	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/options.png", clickableList, renderer, 4, 12);
	const Clickable optionsButton = clickableList[12];
	int xSizeOptions = optionsButton.sizeX / 4, ySizeOptions = optionsButton.sizeY / 4;

	//Clickable saveButton;
	//Clickable loadButton;

    CreateTexture("sprites/board+background.png", &boardSurface, &boardTexture, renderer);

    Display(*renderer, boardTexture, boardSurface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Display(*renderer, optionsButton.texture, optionsButton.surface, SCREEN_WIDTH - xSizeOptions - 5, 5, xSizeOptions, ySizeOptions);

    while(!quit) {
    	while(SDL_PollEvent(&event)) {
    		xMouse = event.motion.x;
    		yMouse = event.motion.y;
    	}

        switch (event.type) {
            case SDL_QUIT: quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN: Click(xMouse, yMouse, clickableList);
            	break;
        }
    }

    SDL_DestroyTexture(boardTexture);
    SDL_DestroyTexture(optionsButton.texture);
    SDL_FreeSurface(boardSurface);
    SDL_FreeSurface(optionsButton.surface);

    return EXIT_SUCCESS;
}

int LaunchSDL() {
    //Proposer une interface sdl ou console (pb include SDL empeche le lancement console,
    //il faudra gerer avec les variables pre processeur)
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* fontSurface = NULL;
	SDL_Texture* fontTexture = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) return SDLError("Can't init SDL : %s\n");
	if(IMG_Init(IMG_INIT_JPG) < 0) return SDLError("Can't init SDL_image : %s\n");

	window = SDL_CreateWindow("Awale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS);
	if(window == NULL) return SDLError("Can't create window : %s\n");

	SDL_SetWindowIcon(window, IMG_Load("sprites/logo2.png"));

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) return SDLError("Can't create renderer : %s\n");

    CreateTexture("sprites/background.jpg", &fontSurface, &fontTexture, &renderer);
    if(fontSurface == NULL || fontTexture == NULL) return SDLError("Can't create surface or texture : %s\n");

    LaunchWindow(&window, &renderer, &fontSurface, &fontTexture);

    SDL_DestroyTexture(fontTexture);
    SDL_FreeSurface(fontSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

	return EXIT_SUCCESS;
}
