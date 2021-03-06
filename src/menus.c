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
#include "read.h"
#include "SDLwindow.h"
#include "movements.h"
#include "ia.h"
#include "menus.h"

void WarningMessage(int action, SDL_Renderer** renderer, SDL_Surface** messageSurface, SDL_Texture** messageTexture, TTF_Font** boardFont, SDL_Color color) {
	switch(action) {
	case -3:
		PrintTempMessage(renderer, messageTexture, messageSurface, boardFont, "Mauvaise ligne", color);
		break;

	case -2:
		PrintTempMessage(renderer, messageTexture, messageSurface, boardFont, "Pas de graines � deplacer", color);
		break;

	case -1:
		PrintTempMessage(renderer, messageTexture, messageSurface, boardFont, "Il faut nourrir l'adversaire", color);
		break;

	case 100:
		PrintTempMessage(renderer, messageTexture, messageSurface, boardFont, "La derni�re partie a �t� charg�e", color);
		break;

	case 101:
		PrintTempMessage(renderer, messageTexture, messageSurface, boardFont, "La partie a �t� sauvegard�e", color);
		break;

	default:
		break;
	}
}

void Next(short* winner, int action, SDL_Renderer** renderer, SDL_Rect* playerRect, SDL_Rect* g1Rect, SDL_Rect* g2Rect, SDL_Surface** winSurface, SDL_Surface** playerSurface, SDL_Surface** arrowSurface, SDL_Surface** g1Surface, SDL_Surface** g2Surface, SDL_Texture** winTexture, SDL_Texture** fontTexture, SDL_Texture** playerTexture, SDL_Texture** arrowTexture, SDL_Texture** g1Texture, SDL_Texture** g2Texture, TTF_Font** boardFont, TTF_Font** buttonFont, char* winText, SDL_Color color) {
	if(action > 0 && action < 100) {
		// On recupere le gain, change de joueur et verifie s'il y a un gagnant
		TakeWonSeeds(action);
		ChangePlayer();
		*winner = GameOver();

		switch(*winner) {
		// Affichage du gagnant et demarrage du menu pour recommencer
		case 1: case 2:
			if(*winner == 1) {
				strcat(winText, "Le joueur ");
				strcat(winText, game.joueur1);
			} else {
				if(strcmp(game.joueur2, "ia") == 0)
					strcat(winText, "L'IA");
				else {
					strcat(winText, "Le joueur ");
					strcat(winText, game.joueur2);
				}
			}

			strcat(winText, " a gagn�");
			RefreshParameters(renderer, playerRect, g1Rect, g2Rect, playerSurface, arrowSurface, g1Surface, g2Surface, fontTexture, playerTexture, arrowTexture, g1Texture, g2Texture, boardFont, color);
			OpenGameOverMenu(renderer, winTexture, winSurface, boardFont, buttonFont, winText, color, &clickableList[15]);
			break;

		// Il y a �galit� et demarrage du menu pour recommencer
		case 3:
			RefreshParameters(renderer, playerRect, g1Rect, g2Rect, playerSurface, arrowSurface, g1Surface, g2Surface, fontTexture, playerTexture, arrowTexture, g1Texture, g2Texture, boardFont, color);
			OpenGameOverMenu(renderer, winTexture, winSurface, boardFont, buttonFont, "Il y a �galit�", color, &clickableList[15]);
			break;

		default:
			break;
		}
	}
}

int OpenBoardMenu(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture, TTF_Font** boardFont, char* gamer1, char* gamer2) {
	// Initialisation de l'ensmenble des variables, surfaces, textures, police d'ecriture, �v�nement necessaires
	short quit = 0, xMouse = 0, yMouse = 0, over = 0, winner = 0;
	char winText[10 + NAME_PLAYER_SIZE] = "";
	Clickable currentButton;
	SDL_Event event;
	SDL_Color whiteColor = {255, 255, 255};
	TTF_Font* buttonFont = TTF_OpenFont("calibril.ttf", 30);
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

	// Choix des positions des ecritures et creation des boutons du board
	menuNumber = 0;
	restart = 0;
	playerRect.x = HINITTEXT;
	playerRect.y = SCREEN_HEIGHT - 80;
	g1Rect.x = playerRect.x + HSPACETEXT;
	g1Rect.y = playerRect.y;
	g2Rect.x = playerRect.x + 2 * HSPACETEXT;
	g2Rect.y = playerRect.y;
	Clickable overButton = CreateBoardButtons(renderer, &buttonFont, &whiteColor);

	// Creation de la fleche, initialisation du jeu et affichage de l'ensemble
	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	InitializeGame(gamer1, gamer2, &winner);
	RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);

	while(!quit) {
		SDL_Delay(20);

		while(SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(currentButton.type != BUTTON_TYPE_EMPTY) {
					short action = currentButton.Action(currentButton.data);

					// On clique sur le bouton recommencer
					if(action == 0 && menuNumber == 1) {
						InitializeGame(gamer1, gamer2, &winner);
						restart = 1;
						quit = 1;
					}

					// On joue la case choisie par le joueur et l'ia s'il y en a une
					if(!winner) {
						Next(&winner, action, renderer, &playerRect, &g1Rect, &g2Rect, &winSurface, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, &winTexture, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, &buttonFont, winText, whiteColor);

						if(strcmp(game.joueur2, "ia") == 0 && game.currentPlayer == 1) {
							action = DistributeSeeds(game.currentPlayer, PlayIA());
							Next(&winner, action, renderer, &playerRect, &g1Rect, &g2Rect, &winSurface, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, &winTexture, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, &buttonFont, winText, whiteColor);
						}
					}

					if(menuNumber != 1)
						RefreshParameters(renderer, &playerRect, &g1Rect, &g2Rect, &playerSurface, &arrowSurface, &g1Surface, &g2Surface, fontTexture, &playerTexture, &arrowTexture, &g1Texture, &g2Texture, boardFont, whiteColor);

					WarningMessage(action, renderer, &messageSurface, &messageTexture, boardFont, whiteColor);
				}

				break;
			case SDL_MOUSEMOTION:
				xMouse = event.motion.x;
				yMouse = event.motion.y;
				currentButton = IsOverButton(xMouse, yMouse, clickableList);

				// Surbrillance de bouton quand on passe la souris au dessus en fonction du type de bouton
				if(overButton.type != currentButton.type) {
					if(!over) {
						over = 1;
						overButton = currentButton;

						if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER || overButton.type == BUTTON_TYPE_WITH_OVER_AND_TEXT)
							Display(*renderer, overButton.textureOver, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					} else {
						over = 0;

						if(overButton.type == BUTTON_TYPE_WITH_SURFACE_OVER || overButton.type == BUTTON_TYPE_WITH_OVER_AND_TEXT)
							Display(*renderer, overButton.texture, overButton.posX, overButton.posY, overButton.sizeX, overButton.sizeY, 0);
					}

					if(overButton.type == BUTTON_TYPE_WITH_OVER_AND_TEXT)
						Display(*renderer, overButton.textTexture, overButton.textRect.x, overButton.textRect.y, overButton.textRect.w, overButton.textRect.h, 0);
				}

				break;
			default:
				break;
			}
		}
	}

	// Free textures et surfaces
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(arrowTexture);
	SDL_DestroyTexture(g1Texture);
	SDL_DestroyTexture(g2Texture);
	SDL_DestroyTexture(messageTexture);
	SDL_FreeSurface(playerSurface);
	SDL_FreeSurface(arrowSurface);
	SDL_FreeSurface(g1Surface);
	SDL_FreeSurface(g2Surface);
	SDL_FreeSurface(messageSurface);
	FreeUpMemoryButton(clickableList);

	if(menuNumber == 1) {
		SDL_DestroyTexture(winTexture);
		SDL_FreeSurface(winSurface);
		TTF_CloseFont(buttonFont);
		SDL_DestroyTexture(clickableList[15].texture);
		SDL_DestroyTexture(clickableList[15].textureOver);
		SDL_DestroyTexture(clickableList[15].textTexture);
		SDL_FreeSurface(clickableList[15].surface);
		SDL_FreeSurface(clickableList[15].surfaceOver);
	}

	if(restart == 1) {
		restart = 0;
		OpenNameSelectionMenu(window, renderer, fontTexture, boardFont);
	}

	return EXIT_SUCCESS;
}

void OpenGameOverMenu(SDL_Renderer** renderer, SDL_Texture** winTexture, SDL_Surface** winSurface, TTF_Font** boardFont, TTF_Font** buttonFont, char* winText, SDL_Color color, Clickable* restartButton) {
	SDL_Rect winnerRect;

	// Choix des positions du bouton
	menuNumber = 1;
	winnerRect.y = 140;
	restartButton -> textRect.x = restartButton -> posX + 10;
	restartButton -> textRect.y = restartButton -> posY + 12;

	// Affichage du bouton pour recommencer une partie
	Display(*renderer, restartButton -> texture, restartButton -> posX, restartButton -> posY, restartButton -> sizeX, restartButton -> sizeY, 1);

	// Affichage du joueur ayant gagn�
	RefreshText(renderer, boardFont, &winnerRect, winSurface, winTexture, winText, color, 1);
	RefreshText(renderer, buttonFont, &(restartButton -> textRect), &(restartButton -> textSurface), &(restartButton -> textTexture), restartButton -> text, color, 0);
	SDL_RenderCopy(*renderer, *winTexture, NULL, &winnerRect);
	SDL_RenderCopy(*renderer, restartButton -> textTexture, NULL, &(restartButton -> textRect));
	SDL_RenderPresent(*renderer);
}

short OpenSaveMenu(SDL_Renderer** renderer) {
	const char saveFile[NAME_FILE_SIZE] = "saved.txt";
	struct tm dateCreation = CurrentTime();
	Save(saveFile, &dateCreation);

	return 101;
}

short OpenLoadMenu(SDL_Renderer** renderer) {
	LoadSavedGame();

	return 100;
}

void RefreshNameSelection(char* name, short gamer, SDL_Renderer** renderer, TTF_Font** boardFont, SDL_Rect* name1Rect, SDL_Rect* name2Rect, SDL_Rect* gamer1Rect, SDL_Rect* gamer2Rect, SDL_Texture** arrowTexture, SDL_Texture** name1Texture, SDL_Texture** name2Texture, SDL_Texture** gamer1Texture, SDL_Texture** gamer2Texture, SDL_Texture** fontTexture, SDL_Surface** arrowSurface, SDL_Surface** nameSurface, SDL_Color color, short* SDLQuit) {
	if(gamer == 1)
		RefreshText(renderer, boardFont, name1Rect, nameSurface, name1Texture, name, color, 0);
	else RefreshText(renderer, boardFont, name2Rect, nameSurface, name2Texture, name, color, 0);

	// Affichage de l'ensemble des �critures sur cette �cran
	Display(*renderer, *fontTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	SDL_RenderCopy(*renderer, *gamer1Texture, NULL, gamer1Rect);
	SDL_RenderCopy(*renderer, *gamer2Texture, NULL, gamer2Rect);
	SDL_RenderCopy(*renderer, *name1Texture, NULL, name1Rect);
	SDL_RenderCopy(*renderer, *name2Texture, NULL, name2Rect);

	// Affichage de la fl�che en face du joueur qui doit compl�t� son pseudo
	if(gamer == 1)
		Display(*renderer, *arrowTexture, 200, gamer1Rect -> y + gamer1Rect -> h / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);
	else Display(*renderer, *arrowTexture, 200, gamer2Rect -> y + gamer2Rect -> h / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);

	SDL_RenderPresent(*renderer);
}

short OpenNameSelectionMenu(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** fontTexture, TTF_Font** boardFont) {
	// Initialisation de l'ensemble des surfaces, texures, rect pour le menu de choix des pseudos
	SDL_Surface* backNameSurface = NULL;
	SDL_Surface* gamer1Surface = NULL;
	SDL_Surface* gamer2Surface = NULL;
	SDL_Surface* arrowSurface = NULL;
	SDL_Texture* backNameTexture = NULL;
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

	// Choix des positions des textures
	gamer1Rect.x = 300;
	gamer2Rect.x = 300;
	name1Rect.x = gamer1Rect.x + 130;
	name2Rect.x = gamer2Rect.x + 130;
	gamer1Rect.y = SCREEN_HEIGHT / 2 - 50;
	gamer2Rect.y = SCREEN_HEIGHT / 2 + 20;
	name1Rect.y = gamer1Rect.y;
	name2Rect.y = gamer2Rect.y;

	// Choix des textures et rafraichissement �criture
	CreateTexture("sprites/backgroundName.png", &backNameSurface, &backNameTexture, renderer);
	CreateTexture("sprites/arrow.png", &arrowSurface, &arrowTexture, renderer);
	RefreshText(renderer, boardFont, &gamer1Rect, &gamer1Surface, &gamer1Texture, gamer1Text, whiteColor, 0);
	RefreshText(renderer, boardFont, &gamer2Rect, &gamer2Surface, &gamer2Texture, gamer2Text, whiteColor, 0);

	// On lit les entr�es clavier pour chacun des deux joueurs
	gamer1 = ReadStringSDL(1, renderer, boardFont, &name1Rect, &name2Rect, &gamer1Rect, &gamer2Rect, &arrowTexture, &name1Texture, &name2Texture, &gamer1Texture, &gamer2Texture, &backNameTexture, &arrowSurface, whiteColor, &SDLQuit);

	if(!SDLQuit)
		gamer2 = ReadStringSDL(2, renderer, boardFont, &name1Rect, &name2Rect, &gamer1Rect, &gamer2Rect, &arrowTexture, &name1Texture, &name2Texture, &gamer1Texture, &gamer2Texture, &backNameTexture, &arrowSurface, whiteColor, &SDLQuit);

	// Free texture et surface
	SDL_DestroyTexture(backNameTexture);
	SDL_DestroyTexture(gamer1Texture);
	SDL_DestroyTexture(gamer2Texture);
	SDL_DestroyTexture(name1Texture);
	SDL_DestroyTexture(name2Texture);
	SDL_DestroyTexture(arrowTexture);
	SDL_FreeSurface(backNameSurface);
	SDL_FreeSurface(gamer1Surface);
	SDL_FreeSurface(gamer2Surface);
	SDL_FreeSurface(arrowSurface);

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

	// Rafrachissement du texte en fonction de joueur entrant son pseudo
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

				// On �crit une lettre
				if(letter >= 32 && letter <= 127 && index < NAME_PLAYER_SIZE) {
					name[index] = (char)letter;
					name[index + 1] = '\0';
					index++;
				// On efface une lettre
				} else if(letter == SDLK_BACKSPACE && index) {
					printf("%d", index);
					name[index - 1] = '\0';
					index--;
				// On confirme son pseudo
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
