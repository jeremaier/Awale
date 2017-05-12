/*
 * menus.c
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "board.h"
#include "game.h"
#include "write.h"
#include "SDLwindow.h"
#include "movements.h"
#include "menus.h"

void CreateButtons(const char* buttonsImg[buttonNumber], const char* buttonsImgOver[buttonNumber], short (*buttonsFonction[buttonNumber])(SDL_Renderer** renderer), Clickable* clickableList, SDL_Renderer** renderer, int horizontalSpace, int verticalSpace, int xFirstPos, int yFirstPos, ButtonType buttonType, const char* buttonsText[buttonNumber]) {
	short i;
	//AllocationClickableList();

	for(i = 0; i < buttonNumber; i++)
		CreateNewButton(xFirstPos + horizontalSpace * i, yFirstPos + verticalSpace * i, buttonsImg[i], buttonsImgOver[i], clickableList, renderer, buttonsFonction[i], i + 1, buttonType, buttonsText[i]);
}

void DisplayButtons(SDL_Renderer** renderer, Clickable* clickableList, short len) {
	short i;

	for(i = 0; i < len; i++) {
		const Clickable button = clickableList[i + 1];

		if(button.type != BUTTON_TYPE_EMPTY)
			Display(*renderer, button.texture, button.posX, button.posY, button.sizeX, button.sizeY, 1);
	}
}

int OpenBoardMenu(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture) {
	short quit = 0, xMouse = 0, yMouse = 0, over = 0, winner = 0;
	char winText[10 + NAME_PLAYER_SIZE] = {"Le joueur "};
	Clickable currentButton;
	SDL_Event event;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* boardFont = NULL;
	TTF_Font* buttonFont = NULL;
	SDL_Surface* playerSurface = NULL;
	SDL_Surface* arrowSurface = NULL;
	SDL_Surface* g1Surface = NULL;
	SDL_Surface* g2Surface = NULL;
	SDL_Surface* messageSurface = NULL;
	SDL_Surface* winSurface = NULL;
	SDL_Texture* playerTexture = NULL;
	SDL_Texture* arrowTexture = NULL;
	SDL_Texture* g1Texture = NULL;
	SDL_Texture* g2Texture = NULL;
	SDL_Texture* messageTexture = NULL;
	SDL_Texture* winTexture = NULL;
	SDL_Rect playerRect;
	SDL_Rect g1Rect;
	SDL_Rect g2Rect;

	buttonNumber = BUTTON_NUMBER_BOARD;
	menuNumber = 0;
	restart = 0;
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
	CreateNewButton(610, 190, "sprites/restart.png", "sprites/restartOver.png", clickableList, renderer, Restart, 14, BUTTON_TYPE_WITH_OVER_AND_TEXT, "Recommencer");
	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	Start(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor, &winner);

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

					if(action == 0 && menuNumber == 1) {
						Start(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor, &winner);
						SDL_DestroyTexture(winTexture);
						SDL_FreeSurface(winSurface);
						TTF_CloseFont(buttonFont);
					}

					if(!winner && action > 0) {
						TakeWonSeeds(action);
						ChangePlayer();
						winner = GameOver();

						switch(winner) {
						case 1: case 2:
							if(winner == 1)
								strcat(winText, game.joueur1);
							else strcat(winText, game.joueur2);

							strcat(winText, " a gagné");
							RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor);
							OpenGameOverMenu(renderer, &winTexture, &winSurface, &boardFont, &buttonFont, winText, whiteColor, &clickableList[14]);
							break;

						case 3:
							RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor);
							OpenGameOverMenu(renderer, &winTexture, &winSurface, &boardFont, &buttonFont, "Il y a égalité", whiteColor, &clickableList[14]);
							break;
						default:
							break;
						}
					}

					if(menuNumber != 1)
						RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, &boardFont, whiteColor);

					switch(action) {
					case -3:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, &boardFont, "Mauvaise ligne", whiteColor);
						break;

					case -2:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, &boardFont, "Pas de graines à deplacer", whiteColor);
						break;

					case -1:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, &boardFont, "Il faut nourrir l'adversaire", whiteColor);
						break;

					default:
						break;
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

						if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER || overButton.type == BUTTON_TYPE_WITH_OVER_AND_TEXT)
							Display(*renderer, overButton.textureOver, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					} else {
						over = 0;

						if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER || (overButton.type == BUTTON_TYPE_WITH_OVER_AND_TEXT && menuNumber == 1))
							Display(*renderer, overButton.texture, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					}

					if(strcmp(overButton.text, "") != 0 && menuNumber == 1)
						Display(*renderer, overButton.textTexture, overButton.textRect.x, overButton.textRect.y, overButton.textRect.w, overButton.textRect.h, 0);
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
	SDL_DestroyTexture(winTexture);
	SDL_FreeSurface(arrowSurface);
	SDL_FreeSurface(playerSurface);
	SDL_FreeSurface(messageSurface);
	SDL_FreeSurface(g1Surface);
	SDL_FreeSurface(g2Surface);
	SDL_FreeSurface(winSurface);
	TTF_CloseFont(boardFont);
	FreeUpMemoryButton(clickableList);

	if(menuNumber == 1)
		TTF_CloseFont(buttonFont);

	return EXIT_SUCCESS;
}

void OpenGameOverMenu(SDL_Renderer** renderer, SDL_Texture** winTexture, SDL_Surface** winSurface, TTF_Font** boardFont, TTF_Font** buttonFont, char* winText, SDL_Color color, Clickable* restartButton) {
	const char file_list[NAME_FILE_SIZE] = "listGames.txt";
	struct tm dateCreation = CurrentTime();
	SDL_Rect winnerRect;

	menuNumber = 1;
	winnerRect.y = 140;
	restartButton -> textRect.x = restartButton -> posX + 10;
	restartButton -> textRect.y = restartButton -> posY + 12;
	*buttonFont = TTF_OpenFont("calibril.ttf", 30);

	Display(*renderer, clickableList[14].texture, clickableList[14].posX, clickableList[14].posY, clickableList[14].sizeX, clickableList[14].sizeY, 1);
	RefreshText(renderer, boardFont, &winnerRect, winSurface, winTexture, winText, color, 1);
	RefreshText(renderer, buttonFont, &(restartButton -> textRect), &(restartButton -> textSurface), &(restartButton -> textTexture), restartButton -> text, color, 0);
	SDL_RenderCopy(*renderer, *winTexture, NULL, &winnerRect);
	SDL_RenderCopy(*renderer, restartButton -> textTexture, NULL, &(restartButton -> textRect));
	SDL_RenderPresent(*renderer);
	SaveInList(file_list, &dateCreation);
}

short OpenOptionsMenu(SDL_Renderer** renderer) {
	buttonNumber = BUTTON_NUMBER_OPTIONS;
	menuNumber = 2;
	SDL_Surface* optionsSurface = NULL;
	SDL_Surface *pauseText = NULL;
	SDL_Texture* optionsTexture = NULL;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* pauseFont = NULL;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	pauseFont = TTF_OpenFont("calibril.ttf", 72);
	if(pauseFont == NULL) return SDLError("Can't create police : %s\n");

	pauseText = TTF_RenderText_Blended(pauseFont, "Pause", whiteColor);
	textTexture = SDL_CreateTextureFromSurface(*renderer, pauseText);

	const char *buttonsImg[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/load.png", "sprites/score.png"};
	const char *buttonsImgOver[BUTTON_NUMBER_OPTIONS] = {"sprites/saveOver.png", "sprites/loadOver.png", "sprites/scoreOver.png"};
	const char *buttonsText[BUTTON_NUMBER_OPTIONS] = {"Save", "Load", "Score"};
	short (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer) = {OpenSaveMenu, OpenLoadMenu, OpenScoreMenu};

	CreateButtons(buttonsImg, buttonsImgOver, buttonsFonction, clickableList, renderer, 300, 0, 250, 50, BUTTON_TYPE_WITH_OVER_AND_TEXT, buttonsText);
	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/options.png", "sprites/optionsOver.png", clickableList, renderer, NULL, 4, BUTTON_TYPE_WITH_SURFACE_OVER, "");
	CreateTexture("sprites/backOptions.png", &optionsSurface, &optionsTexture, renderer);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	textRect.x = SCREEN_WIDTH / 2 - textRect.w / 2;
	textRect.y = 180;

	Display(*renderer, optionsTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	DisplayButtons(renderer, clickableList, buttonNumber);
	SDL_RenderCopy(*renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(*renderer);

	return 0;
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
