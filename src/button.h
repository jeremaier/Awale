/*
 * button.h
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
	const char* text;
} Clickable;

/**
 * Creer un nouveau bouton et l'ajoute dans la liste des boutons
 */
Clickable CreateNewButton(int, int, const char*, const char*, Clickable*, SDL_Renderer**, short (*)(SDL_Renderer**), short, ButtonType, const char*, const short);

/**
 * Action de chaque cliquable
 */
void Action(void*);

/**
 * Regarde si la souris est au dessus d'un bouton
 */
Clickable IsOverButton(int, int, Clickable*);

/**
 * Creation de l'ensemble des boutons necessaires
 */
Clickable CreateBoardButtons(SDL_Renderer** renderer, TTF_Font**, SDL_Color*);

/**
 * Cree tous les boutons du menu en fonction de leur image, de la position du premier bouton, de leur espacement entre eux et de leur fonction
 */
void CreatePauseButtons(const char*[BUTTON_NUMBER], const char*[BUTTON_NUMBER], short (*[BUTTON_NUMBER])(SDL_Renderer**), Clickable*, SDL_Renderer**, int, ButtonType, const char*[BUTTON_NUMBER]);

/**
 * Affiche une liste de boutons en fonction des espaces entre eux
 */
void DisplayButtons(SDL_Renderer**, Clickable*, short);

/**
 * Liberation de l'espace memoire utilise par les images SDL des boutons en fonction de leur type
 */
void FreeUpMemoryButton(Clickable*);

#endif /* SRC_BUTTON_H_ */
