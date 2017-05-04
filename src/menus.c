/*
 * menus.c
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <time.h>
////////////
#include <string.h>
////////////

#include "board.h"
#include "game.h"
#include "write.h"
#include "SDLwindow.h"
#include "menus.h"

void CreateButtons(const char* buttonsImg[buttonNumber], const char* buttonsImgOver[buttonNumber], short (*buttonsFonction[buttonNumber])(SDL_Renderer** renderer), Clickable* clickableList, SDL_Renderer** renderer, int horizontalSpace, int verticalSpace, int xFirstPos, int yFirstPos, ButtonType buttonType, char* text) {
	short i;
	AllocationClickableList();

	for(i = 0; i < buttonNumber; i++)
		CreateNewButton(xFirstPos + horizontalSpace * i, yFirstPos + verticalSpace * i, buttonsImg[i], buttonsImgOver[i], clickableList, renderer, buttonsFonction[i], i + 1, buttonType, text);
}

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		const Clickable button = clickableList[i + 1];

		if(button.type != BUTTON_TYPE_EMPTY)
			Display(*renderer, button.texture, button.posX, button.posY, button.sizeX, button.sizeY, 1);
	}
}

int LaunchWindow(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture) {
	short quit = 0, xMouse = 0, yMouse = 0, over = 0, winner = 0;
	char winText[10 + NAME_PLAYER_SIZE] = {"Le joueur "};
	Clickable currentButton;
	SDL_Event event;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* boardFont = NULL;
	SDL_Surface* playerSurface = NULL;
	SDL_Surface* arrowSurface = NULL;
	SDL_Surface* g1Surface = NULL;
	SDL_Surface* g2Surface = NULL;
	SDL_Surface* messageSurface = NULL;
	SDL_Texture* playerTexture = NULL;
	SDL_Texture* arrowTexture = NULL;
	SDL_Texture* g1Texture = NULL;
	SDL_Texture* g2Texture = NULL;
	SDL_Texture* messageTexture = NULL;
	SDL_Rect playerRect;
	SDL_Rect g1Rect;
	SDL_Rect g2Rect;
	buttonNumber = BUTTON_NUMBER_BOARD;
	menuNumber = 0;
	playerRect.x = HINITTEXT;
	playerRect.y = SCREEN_HEIGHT - 80;
	g1Rect.x = playerRect.x + HSPACETEXT;
	g1Rect.y = playerRect.y;
	g2Rect.x = playerRect.x + 2 * HSPACETEXT;
	g2Rect.y = playerRect.y;

	boardFont = TTF_OpenFont("calibril.ttf", 30);
	if(boardFont == NULL) return SDLError("Can't create police : %s\n");

	AllocationClickableList();
	Clickable overButton = CreateNewButton(0, 0, "", "", clickableList, renderer, NULL, 0, BUTTON_TYPE_EMPTY, "");
	CreateClickableBoard(clickableList, renderer);

	////////////////////////////
	const char file_list[NAME_FILE_SIZE] = "listGames.txt";
	struct tm dateCreation = currentTime();
	loadBlankGame(file_list, &dateCreation);
	strcpy(game.joueur1 , "PD");
	strcpy(game.joueur2 , "PD2");
	////////////////////////////

	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor);

	while(!quit) {
		SDL_Delay(10);

		while(SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(currentButton.type != BUTTON_TYPE_EMPTY) {
					const short action = currentButton.Action(currentButton.data);

					if(!winner && action > 0) {
						changePlayer();
						/*
						 *
						 * Verifier s'il y a des graines a recup
						 *
						 */
						winner = gameOver();

						switch(winner) {
						case 1:
							strcat(winText, game.joueur1);
							strcat(winText, " a gagné");
							OpenGameOverMenu(renderer, &boardFont, winText, whiteColor);
							break;
						case 2:
							strcat(winText, game.joueur2);
							strcat(winText, " a gagné");
							OpenGameOverMenu(renderer, &boardFont, winText, whiteColor);
							break;
						case 3:
							OpenGameOverMenu(renderer, &boardFont, "Il y a égalité", whiteColor);
							break;
						default:
							break;
						}
					}

					RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor);

					if(action == -2 || action == -1) {
						if(action == -2)
							PrintTempMessage(renderer, &messageTexture, &messageSurface, &boardFont, "Mauvaise ligne", whiteColor);
						else PrintTempMessage(renderer, &messageTexture, &messageSurface, &boardFont, "Pas de graines à deplacer", whiteColor);

						SDL_RenderPresent(*renderer);
					}
				}

				break;
			case SDL_MOUSEMOTION:
				xMouse = event.motion.x;
				yMouse = event.motion.y;
				currentButton = IsOverButton(xMouse, yMouse, clickableList);

				if(overButton.type != currentButton.type) {
					if(!over) {
						over = 1;
						overButton = currentButton;

						if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER)
							Display(*renderer, overButton.textureOver, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					} else {
						over = 0;

						if(overButton.type != BUTTON_TYPE_EMPTY)
							Display(*renderer, overButton.texture, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					}
				}

				break;
			default:
				break;
			}
		}
	}

	SDL_DestroyTexture(arrowTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(messageTexture);
	SDL_DestroyTexture(g1Texture);
	SDL_DestroyTexture(g2Texture);
	SDL_FreeSurface(arrowSurface);
	SDL_FreeSurface(playerSurface);
	SDL_FreeSurface(messageSurface);
	SDL_FreeSurface(g1Surface);
	SDL_FreeSurface(g2Surface);
	TTF_CloseFont(boardFont);
	freeUpMemoryButton(clickableList);

	return EXIT_SUCCESS;
}

void OpenGameOverMenu(SDL_Renderer** renderer, TTF_Font** boardFont, char* winText, SDL_Color color) {
	const char file_list[NAME_FILE_SIZE] = "listGames.txt";
	struct tm dateCreation = currentTime();
	SDL_Surface* winSurface = NULL;
	SDL_Texture* winTexture = NULL;
	SDL_Rect winRect;

	winRect.x = 100;
	winRect.y = 300;

	RefreshText(renderer, boardFont, &winRect, &winSurface, &winTexture, winText, color, 1);
	SDL_RenderCopy(*renderer, winTexture, NULL, &winRect);
	saveInList(file_list, &dateCreation);
	/*
	 * SDL_DestroyTexture(*winTexture);
	 * SDL_FreeSurface(*winSurface);
	 */
}

short OpenOptionsMenu(SDL_Renderer** renderer) {
	buttonNumber = BUTTON_NUMBER_OPTIONS;
	menuNumber = 1;
	SDL_Surface* optionsSurface = NULL;
	SDL_Texture* optionsTexture = NULL;
	SDL_Surface *pauseText = NULL;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* pauseFont = NULL;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	pauseFont = TTF_OpenFont("calibril.ttf", 72);
	if(pauseFont == NULL) return SDLError("Can't create police : %s\n");

	pauseText = TTF_RenderText_Blended(pauseFont, "Pause", whiteColor);
	textTexture = SDL_CreateTextureFromSurface(*renderer, pauseText);

	const char *buttonsImg[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	const char *buttonsImgOver[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/save.png", "sprites/save.png"};
	short (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer) = {OpenSaveMenu, OpenLoadMenu, OpenScoreMenu};

	CreateButtons(buttonsImg, buttonsImgOver, buttonsFonction, clickableList, renderer, 300, 0, 250, 50, BUTTON_TYPE_WITH_SURFACE_OVER, "");
	CreateTexture("sprites/backOptions.png", &optionsSurface, &optionsTexture, renderer);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	textRect.x = SCREEN_WIDTH / 2 - textRect.w / 2;
	textRect.y = 180;

	Display(*renderer, optionsTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	DisplayButtons(renderer, clickableList, buttonNumber);
	SDL_RenderCopy(*renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(*renderer);

	return -1;
}

short OpenSaveMenu(SDL_Renderer** renderer) {
	return 0;
}

short OpenLoadMenu(SDL_Renderer** renderer) {
	return 0;
}

short OpenScoreMenu(SDL_Renderer** renderer) {
	return 0;
}
