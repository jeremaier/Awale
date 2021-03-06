/*
 * SDLwindow.c
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "game.h"
#include "menus.h"
#include "SDLwindow.h"

int SDLError(char* message) {
    printf(message, SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}

void CreateTexture(const char* path, SDL_Surface** surface, SDL_Texture** texture, SDL_Renderer** renderer) {
	// Cr�� une image
    *surface = IMG_Load(path);
    *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
}

void Display(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int firstInit) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Fais le rendu si ce n'est pas la derni�re � afficher sur le m�me panel
    if(!firstInit)
    	SDL_RenderPresent(renderer);
}

void BoardDiplayed(SDL_Renderer** renderer, SDL_Rect* playerRect, SDL_Rect* g1Rect, SDL_Rect* g2Rect, SDL_Surface** arrowSurface, SDL_Texture** fontTexture, SDL_Texture** playerTexture, SDL_Texture** arrowTexture, SDL_Texture** g1Texture, SDL_Texture** g2Texture, TTF_Font** boardFont, SDL_Color color) {
	short i = 0;

	// Affiche le fond
	if(menuNumber != 2)
	    Display(*renderer, *fontTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);

	if(menuNumber == 0) {
		// Affiche les boutons annexes
		Display(*renderer, clickableList[13].texture, clickableList[13].posX, clickableList[13].posY, clickableList[13].sizeX, clickableList[13].sizeY, 1);
		Display(*renderer, clickableList[14].texture, clickableList[14].posX, clickableList[14].posY, clickableList[14].sizeX, clickableList[14].sizeY, 1);
		Display(*renderer, clickableList[13].textTexture, clickableList[13].textRect.x, clickableList[13].textRect.y, clickableList[13].textRect.w, clickableList[13].textRect.h, 0);
		Display(*renderer, clickableList[14].textTexture, clickableList[14].textRect.x, clickableList[14].textRect.y, clickableList[14].textRect.w, clickableList[14].textRect.h, 0);

		// Affiche les trous avec le nombre des graines qui correspond
	    for(i = 0; i < NB_HOLES * NB_ROW; i++) {
		    Display(*renderer, clickableList[i + 1].texture, clickableList[i + 1].posX, clickableList[i + 1].posY, clickableList[i + 1].sizeX, clickableList[i + 1].sizeY, 1);

		    char seedNumber[3];
			SDL_Surface* seedSurface = NULL;
		    SDL_Texture* seedTexture = NULL;
		    SDL_Rect seedRect;

		    // Rafraichissement du nombre de graines affich� sur un trou
		    sprintf(seedNumber, "%d", game.board_config[i / NB_HOLES][(i - (i / NB_HOLES) * NB_HOLES)]);
		    RefreshText(renderer, boardFont, &seedRect, &seedSurface, &seedTexture, seedNumber, color, 0);
		    seedRect.x = clickableList[i + 1].posX + clickableList[i + 1].sizeX / 2 - seedRect.w / 2;
		    seedRect.y = clickableList[i + 1].posY + clickableList[i + 1].sizeY / 2 - seedRect.h / 2;

		    SDL_RenderCopy(*renderer, seedTexture, NULL, &seedRect);
	    }
	}

	// Affiche la fl�che pour savoir � qui c'est de jouer
    if(!game.currentPlayer)
    	Display(*renderer, *arrowTexture, 15, clickableList[1].posY + clickableList[1].sizeY / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);
    else Display(*renderer, *arrowTexture, 15, clickableList[7].posY + clickableList[7].sizeY / 2 - (*arrowSurface) -> h / 2, (*arrowSurface) -> w, (*arrowSurface) -> h, 1);

    SDL_RenderCopy(*renderer, *playerTexture, NULL, playerRect);
    SDL_RenderCopy(*renderer, *g1Texture, NULL, g1Rect);
    SDL_RenderCopy(*renderer, *g2Texture, NULL, g2Rect);

    SDL_RenderPresent(*renderer);
}

void RefreshText(SDL_Renderer** renderer, TTF_Font** boardFont, SDL_Rect* rect, SDL_Surface** textSurface, SDL_Texture** textTexture, const char* text, SDL_Color color, short center) {
	*textSurface = TTF_RenderText_Blended(*boardFont, text, color);
	*textTexture = SDL_CreateTextureFromSurface(*renderer, *textSurface);
	SDL_QueryTexture(*textTexture, NULL, NULL, &(rect -> w), &(rect -> h));

	// Centre le texte
	if(center)
		rect -> x = SCREEN_WIDTH / 2 - rect -> w / 2;
}

void RefreshParameters(SDL_Renderer** renderer, SDL_Rect* playerRect, SDL_Rect* g1Rect, SDL_Rect* g2Rect, SDL_Surface** playerSurface, SDL_Surface** arrowSurface, SDL_Surface** g1Surface, SDL_Surface** g2Surface, SDL_Texture** fontTexture, SDL_Texture** playerTexture, SDL_Texture** arrowTexture, SDL_Texture** g1Texture, SDL_Texture** g2Texture, TTF_Font** boardFont, SDL_Color color) {
    char playerText[10 + NAME_PLAYER_SIZE];
    char g1Text[10 + NAME_PLAYER_SIZE];
    char g2Text[10 + NAME_PLAYER_SIZE];
    char g1[3];
    char g2[3];

    // Enregistrement des gains par joueur et le joueur courant dans des variables
	sprintf(g1, "%hd", game.gains[0]);
	sprintf(g2, "%hd", game.gains[1]);
	strcpy(playerText , "Joueur : ");
	strcpy(g1Text , "Gain ");
	strcpy(g2Text , "Gain ");
	strcat(g1Text, game.joueur1);
	strcat(g2Text, game.joueur2);
	strcat(g1Text, " : ");
	strcat(g2Text, " : ");
	strcat(g1Text, g1);
	strcat(g2Text, g2);

	if(!game.currentPlayer)
		strcat(playerText, game.joueur1);
	else strcat(playerText, game.joueur2);

	// Rafraichissement des gains et du joueur courant
	RefreshText(renderer, boardFont, playerRect, playerSurface, playerTexture, playerText, color, 0);
	RefreshText(renderer, boardFont, g1Rect, g1Surface, g1Texture, g1Text, color, 0);
	RefreshText(renderer, boardFont, g2Rect, g2Surface, g2Texture, g2Text, color, 0);
	BoardDiplayed(renderer, playerRect, g1Rect, g2Rect, arrowSurface, fontTexture, playerTexture, arrowTexture, g1Texture, g2Texture, boardFont, color);
}

void PrintTempMessage(SDL_Renderer** renderer, SDL_Texture** messageTexture, SDL_Surface** messageSurface, TTF_Font** boardFont, char* messageText, SDL_Color color) {
    SDL_Rect messageRect;

    // Choix de la position d'un texte d'erreur de jeu
    messageRect.y = 215;

	RefreshText(renderer, boardFont, &messageRect, messageSurface, messageTexture, messageText, color, 1);
    SDL_RenderCopy(*renderer, *messageTexture, NULL, &messageRect);
    SDL_RenderPresent(*renderer);
}

int LaunchSDL() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* fontSurface = NULL;
	SDL_Texture* fontTexture = NULL;
	TTF_Font* boardFont = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) return SDLError("Can't init SDL : %s\n");
	if(IMG_Init(IMG_INIT_JPG) < 0) return SDLError("Can't init SDL_image : %s\n");
	if(TTF_Init() < 0) return SDLError("Can't init SDL_image : %s\n");

	window = SDL_CreateWindow("Awale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS);
	if(window == NULL) return SDLError("Can't create window : %s\n");

	SDL_SetWindowIcon(window, IMG_Load("sprites/logo.png"));

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) return SDLError("Can't create renderer : %s\n");

    CreateTexture("sprites/background.png", &fontSurface, &fontTexture, &renderer);
    if(fontSurface == NULL || fontTexture == NULL) return SDLError("Can't create surface or texture : %s\n");

	boardFont = TTF_OpenFont("calibril.ttf", 30);
	if(boardFont == NULL) return SDLError("Can't create police : %s\n");

    OpenNameSelectionMenu(&window, &renderer, &fontTexture, &boardFont); // Lancement du menu de selection de pseudo

    // Fermeture du jeu et free des surfaces, textures, police d'ecriture
    SDL_DestroyTexture(fontTexture);
    SDL_FreeSurface(fontSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(boardFont);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

	return EXIT_SUCCESS;
}
