/*
 * button.h
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <SDL2/SDL.h>

typedef enum ButtonType {
	BUTTON_TYPE_EMPTY,
	BUTTON_TYPE_WITH_SURFACE,
	BUTTON_TYPE_WITH_SURFACE_OVER,
	BUTTON_TYPE_WITH_OVER_AND_TEXT
} ButtonType;

typedef struct Clickable {
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Surface* surfaceOver;
	SDL_Texture* textureOver;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Rect textRect;
	ButtonType type;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
	short (*Action)(SDL_Renderer**);
	void* data;
	char* text;
} Clickable;

/**
 * Creer un nouveau bouton et l'ajoute dans la liste des boutons
 */
Clickable CreateNewButton(int, int, const char*, const char*, Clickable*, SDL_Renderer**, short (*)(SDL_Renderer**), short, ButtonType, char*);

/**
 * Action de chaque cliquable
 */
void Action(void*);

/**
 * Regarde si la souris est au dessus d'un bouton
 */
Clickable IsOverButton(int, int, Clickable*);

/**
 * Change la liste des boutons qui sont clickable dans le menu courant
 */
void AllocationClickableList();

/**
 * Liberation de l'espace memoire utilise par les images SDL
 */
void FreeUpMemoryButton(Clickable*);

#endif /* SRC_BUTTON_H_ */
