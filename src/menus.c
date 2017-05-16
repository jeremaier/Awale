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

Clickable CreateBoardButtons(SDL_Renderer** renderer) {
	buttonNumber = BUTTON_NUMBER_BOARD;
	menuNumber = 0;
	AllocationClickableList();
	CreateClickableBoard(clickableList, renderer);
	CreateNewButton(610, 190, "sprites/restart.png", "sprites/restartOver.png", clickableList, renderer, Restart, 14, BUTTON_TYPE_WITH_OVER_AND_TEXT, "Recommencer");

	return CreateNewButton(0, 0, "", "", clickableList, renderer, NULL, 0, BUTTON_TYPE_EMPTY, "");
}

int OpenBoardMenu(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture, TTF_Font** boardFont, char* gamer1, char* gamer2) {
	short quit = 0, xMouse = 0, yMouse = 0, over = 0, winner = 0;
	char winText[10 + NAME_PLAYER_SIZE] = {"Le joueur "};
	Clickable currentButton;
	SDL_Event event;
	SDL_Color whiteColor = {255, 255, 255};
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

	restart = 0;
	playerRect.x = HINITTEXT;
	playerRect.y = SCREEN_HEIGHT - 80;
	g1Rect.x = playerRect.x + HSPACETEXT;
	g1Rect.y = playerRect.y;
	g2Rect.x = playerRect.x + 2 * HSPACETEXT;
	g2Rect.y = playerRect.y;
	Clickable overButton = CreateBoardButtons(renderer);

	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	InitializeGame(window, renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor, gamer1, gamer2, &winner);
	RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);

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

					if(action == 0) {
						if(menuNumber == 1) {
							InitializeGame(window, renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor, gamer1, gamer2, &winner);
							SDL_DestroyTexture(winTexture);
							SDL_FreeSurface(winSurface);
							TTF_CloseFont(buttonFont);
							restart = 1;
							quit = 1;
						} else {
							menuNumber = 0;
							CreateBoardButtons(renderer);
							RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);
						}
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
							RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);
							OpenGameOverMenu(renderer, &winTexture, &winSurface, boardFont, &buttonFont, winText, whiteColor, &clickableList[14]);
							break;

						case 3:
							RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);
							OpenGameOverMenu(renderer, &winTexture, &winSurface, boardFont, &buttonFont, "Il y a égalité", whiteColor, &clickableList[14]);
							break;
						default:
							break;
						}
					}

					if(menuNumber != 1)
						RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);

					switch(action) {
					case -3:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, boardFont, "Mauvaise ligne", whiteColor);
						break;

					case -2:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, boardFont, "Pas de graines à deplacer", whiteColor);
						break;

					case -1:
						PrintTempMessage(renderer, &messageTexture, &messageSurface, boardFont, "Il faut nourrir l'adversaire", whiteColor);
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
	FreeUpMemoryButton(clickableList);

	if(menuNumber == 1)
		TTF_CloseFont(buttonFont);

	if(restart) {
		restart = 0;
		OpenNameSelectionMenu(window, renderer, fontTexture, boardFont);
	}

	TTF_CloseFont(*boardFont);

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
	SDL_Surface* pauseText = NULL;
	SDL_Texture* optionsTexture = NULL;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* pauseFont = NULL;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	pauseFont = TTF_OpenFont("calibril.ttf", 72);
	if(pauseFont == NULL) return SDLError("Can't create police : %s\n");

	pauseText = TTF_RenderText_Blended(pauseFont, "Pause", whiteColor);
	textTexture = SDL_CreateTextureFromSurface(*renderer, pauseText);

	const char *buttonsImg[BUTTON_NUMBER_OPTIONS] = {"sprites/save.png", "sprites/load.png"};
	const char *buttonsImgOver[BUTTON_NUMBER_OPTIONS] = {"sprites/saveOver.png", "sprites/loadOver.png"};
	const char *buttonsText[BUTTON_NUMBER_OPTIONS] = {"Save", "Load"};
	short (*buttonsFonction[BUTTON_NUMBER_OPTIONS])(SDL_Renderer** renderer) = {OpenSaveMenu, OpenLoadMenu};

	CreateButtons(buttonsImg, buttonsImgOver, buttonsFonction, clickableList, renderer, 300, 0, 250, 50, BUTTON_TYPE_WITH_OVER_AND_TEXT, buttonsText);
	CreateNewButton(SCREEN_WIDTH - 5, 5, "sprites/options.png", "sprites/optionsOver.png", clickableList, renderer, Restart, 3, BUTTON_TYPE_WITH_SURFACE_OVER, "");
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

void RefreshNameSelection(char* name, short gamer, SDL_Renderer** renderer, TTF_Font** boardFont, SDL_Rect* name1Rect, SDL_Rect* name2Rect, SDL_Rect* gamer1Rect, SDL_Rect* gamer2Rect, SDL_Texture** arrowTexture, SDL_Texture** name1Texture, SDL_Texture** name2Texture, SDL_Texture** gamer1Texture, SDL_Texture** gamer2Texture, SDL_Texture** fontTexture, SDL_Surface** arrowSurface, SDL_Surface** nameSurface, SDL_Color color, short* SDLQuit) {
	if(gamer == 1)
		RefreshText(renderer, boardFont, name1Rect, nameSurface, name1Texture, name, color, 0);
	else RefreshText(renderer, boardFont, name2Rect, nameSurface, name2Texture, name, color, 0);

	Display(*renderer, *fontTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	SDL_RenderCopy(*renderer, *gamer1Texture, NULL, gamer1Rect);
	SDL_RenderCopy(*renderer, *gamer2Texture, NULL, gamer2Rect);
	SDL_RenderCopy(*renderer, *name1Texture, NULL, name1Rect);
	SDL_RenderCopy(*renderer, *name2Texture, NULL, name2Rect);

    if(gamer == 1)
    	Display(*renderer, *arrowTexture, 200, gamer1Rect -> y + gamer1Rect -> h / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);
    else Display(*renderer, *arrowTexture, 200, gamer2Rect -> y + gamer2Rect -> h / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);

	SDL_RenderPresent(*renderer);
}

short OpenNameSelectionMenu(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture, TTF_Font** boardFont) {
	SDL_Surface* gamer1Surface = NULL;
	SDL_Surface* gamer2Surface = NULL;
	SDL_Surface* arrowSurface = NULL;
	SDL_Texture* gamer1Texture = NULL;
	SDL_Texture* gamer2Texture = NULL;
	SDL_Texture* name1Texture = NULL;
	SDL_Texture* name2Texture = NULL;
	SDL_Texture* arrowTexture = NULL;
	SDL_Rect gamer1Rect;
	SDL_Rect gamer2Rect;
	SDL_Rect name1Rect;
	SDL_Rect name2Rect;
	SDL_Color whiteColor = {255, 255, 255};
	char* gamer1Text = {"Joueur 1 : "};
	char* gamer2Text = {"Joueur 2 : "};
	char* gamer1;
	char* gamer2;
	short SDLQuit = 0;

	gamer1Rect.x = 300;
	gamer2Rect.x = 300;
	name1Rect.x = gamer1Rect.x + 130;
	name2Rect.x = gamer2Rect.x + 130;
	gamer1Rect.y = SCREEN_HEIGHT / 2 - 50;
	gamer2Rect.y = SCREEN_HEIGHT / 2 + 20;
	name1Rect.y = gamer1Rect.y;
	name2Rect.y = gamer2Rect.y;

	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	RefreshText(renderer, boardFont, &gamer1Rect, &gamer1Surface, &gamer1Texture, gamer1Text, whiteColor, 0);
	RefreshText(renderer, boardFont, &gamer2Rect, &gamer2Surface, &gamer2Texture, gamer2Text, whiteColor, 0);
	SDL_RenderCopy(*renderer, gamer1Texture, NULL, &gamer1Rect);
	SDL_RenderCopy(*renderer, gamer2Texture, NULL, &gamer2Rect);
	Display(*renderer, *fontTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	Display(*renderer, arrowTexture, 200, gamer1Rect.y + gamer1Rect.h / 2 - arrowSurface -> h / 2, arrowSurface -> w, arrowSurface -> h, 1);
	SDL_RenderPresent(*renderer);

	gamer1 = ReadStringSDL(1, renderer, boardFont, &name1Rect, &name2Rect, &gamer1Rect, &gamer2Rect, &arrowTexture, &name1Texture, &name2Texture, &gamer1Texture, &gamer2Texture, fontTexture, &arrowSurface, whiteColor, &SDLQuit);

	if(!SDLQuit)
		gamer2 = ReadStringSDL(2, renderer, boardFont, &name1Rect, &name2Rect, &gamer1Rect, &gamer2Rect, &arrowTexture, &name1Texture, &name2Texture, &gamer1Texture, &gamer2Texture, fontTexture, &arrowSurface, whiteColor, &SDLQuit);

	SDL_DestroyTexture(gamer1Texture);
	SDL_DestroyTexture(gamer2Texture);
	SDL_DestroyTexture(name1Texture);
	SDL_DestroyTexture(name2Texture);
	SDL_FreeSurface(gamer1Surface);
	SDL_FreeSurface(gamer2Surface);

	if(!SDLQuit)
		OpenBoardMenu(window, renderer, fontTexture, boardFont, gamer1, gamer2);

	return 1;
}

char* ReadStringSDL(short gamer, SDL_Renderer** renderer, TTF_Font** boardFont, SDL_Rect* name1Rect, SDL_Rect* name2Rect, SDL_Rect* gamer1Rect, SDL_Rect* gamer2Rect, SDL_Texture** arrowTexture, SDL_Texture** name1Texture, SDL_Texture** name2Texture, SDL_Texture** gamer1Texture, SDL_Texture** gamer2Texture, SDL_Texture** fontTexture, SDL_Surface** arrowSurface, SDL_Color color, short* SDLQuit) {
	int index = 0, quit = 0, letter;
	SDL_Event event;
	SDL_Surface* nameSurface = NULL;
	char* name = (char*)malloc(NAME_PLAYER_SIZE * sizeof(char));
	name[0] = '\0';

	RefreshNameSelection(name, gamer, renderer, boardFont, name1Rect, name2Rect, gamer1Rect, gamer2Rect, arrowTexture, name1Texture, name2Texture, gamer1Texture, gamer2Texture, fontTexture, arrowSurface, &nameSurface, color, SDLQuit);

	if(gamer == 1)
		RefreshText(renderer, boardFont, name1Rect, &nameSurface, name1Texture, name, color, 0);
	else RefreshText(renderer, boardFont, name2Rect, &nameSurface, name2Texture, name, color, 0);

	while(!quit) {
		SDL_Delay(10);

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				*SDLQuit = 1;
				quit = 1;
				break;

			case SDL_KEYDOWN:
				letter = event.key.keysym.sym;

				if(letter >= 32 && letter <= 127 && index < NAME_PLAYER_SIZE) {
					name[index] = (char)letter;
					name[index + 1] = '\0';
					index++;
				} else if(letter == SDLK_BACKSPACE && index) {
					printf("%d", index);
					name[index - 1] = '\0';
					index--;
				} else if(letter == SDLK_RETURN && index != 0) {
					name[index] = '\0';
					quit = 1;
				}

				RefreshNameSelection(name, gamer, renderer, boardFont, name1Rect, name2Rect, gamer1Rect, gamer2Rect, arrowTexture, name1Texture, name2Texture, gamer1Texture, gamer2Texture, fontTexture, arrowSurface, &nameSurface, color, SDLQuit);

				break;
			}
		}
	}

	SDL_FreeSurface(nameSurface);

	return name;
}
