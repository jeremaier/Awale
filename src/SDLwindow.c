/*
 * SDLwindow.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//////////////////////////////////////////////
#include "game.h"
#include "tests.h"
#include <time.h>
/////////////////////////////////
#include "menus.h"
#include "board.h"
#include "const.h"
#include "button.h"
#include "SDLwindow.h"

int SDLError(char* message) {
    printf(message, SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}

void CreateTexture(const char* path, SDL_Surface** surface, SDL_Texture** texture, SDL_Renderer** renderer) {
    *surface = IMG_Load(path);
    *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
}

void Display(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

int LaunchWindow(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture) {
    /*/////////////////////////////////////////
    time_t secondes;
    struct tm creationGame;
    time(&secondes);
    creationGame = *localtime(&secondes);
    boardInit(game.board_config);
    gameToString(&game, &creationGame);
    //////////////////////////////////////////*/
	short quit = 0, xMouse = 0, yMouse = 0, over = 0, i = 0;

	SDL_Event event;

	/*SDL_Surface *texte = NULL;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("Calibri.ttf", 30);
    texte = TTF_RenderText_Blended(police, "Pause", couleurNoire);*/

	buttonNumber = BUTTON_NUMBER_BOARD;
	menuNumber = 0;

	AllocationClickableList();
	Clickable overButton = CreateNewButton(0, 0, "", "", clickableList, renderer, NULL, 1, 0, BUTTON_TYPE_EMPTY, "");
	CreateClickableBoard(clickableList, renderer);
    Display(*renderer, *fontTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Display(*renderer, clickableList[13].texture, clickableList[13].posX, clickableList[13].posY, clickableList[13].sizeX, clickableList[13].sizeY);

    for(i = 0; i < NB_HOLES * NB_ROW; i++)
	    Display(*renderer, clickableList[i + 1].texture, clickableList[i + 1].posX, clickableList[i + 1].posY, clickableList[i + 1].sizeX, clickableList[i + 1].sizeY);

    /*SDL_Rect position;
    position.x = 60;
    position.y = 370;
    SDL_Surface *pSurf = SDL_GetWindowSurface(*window);
    SDL_BlitSurface(texte, NULL, pSurf, &position);
    SDL_UpdateWindowSurface(*window);*/

    while(!quit) {
    	SDL_Delay(10);

    	while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                	quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                	if(overButton.type != BUTTON_TYPE_EMPTY)
                		overButton.Action(overButton.data);
                	break;
                case SDL_MOUSEMOTION:
                	xMouse = event.motion.x;
                	yMouse = event.motion.y;
                	Clickable currentButton = Over(xMouse, yMouse, clickableList);

                	if(overButton.type != currentButton.type) {
                		if(!over) {
                			over = 1;
                			overButton = currentButton;

                			if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER)
                				Display(*renderer, overButton.textureOver, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY);
						} else {
							over = 0;

							if(overButton.type != BUTTON_TYPE_EMPTY)
								Display(*renderer, overButton.texture, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY);
						}
                	}
                	break;
                default:
                	break;
            }
    	}
    }

    //TTF_CloseFont(police);
    freeUpMemoryButton(clickableList);

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
	//if(TTF_Init() < 0) return SDLError("Can't init SDL_ttf : %s\n");

	window = SDL_CreateWindow("Awale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS);
	if(window == NULL) return SDLError("Can't create window : %s\n");

	SDL_SetWindowIcon(window, IMG_Load("sprites/logo.png"));

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) return SDLError("Can't create renderer : %s\n");

    CreateTexture("sprites/back.png", &fontSurface, &fontTexture, &renderer);
    if(fontSurface == NULL || fontTexture == NULL) return SDLError("Can't create surface or texture : %s\n");

    LaunchWindow(&window, &renderer, &fontTexture);

    SDL_DestroyTexture(fontTexture);
    SDL_FreeSurface(fontSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    IMG_Quit();
    SDL_Quit();

	return EXIT_SUCCESS;
}
