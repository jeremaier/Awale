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
  BUTTON_TYPE_BOARD,
  BUTTON_TYPE_OPTIONS,
  BUTTON_TYPE_SAVE,
  BUTTON_TYPE_LOAD
} ButtonType;

typedef struct Clickable {
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Surface* surfaceOver;
	SDL_Texture* textureOver;
	ButtonType type;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
	void (*Action)(SDL_Renderer**);
	void *data;
} Clickable;

/**
 * Creer un nouveau bouton et l'ajoute dans la liste des boutons
 */

Clickable CreateNewButton(int, int, const char*, const char*, Clickable*, SDL_Renderer**, void (*)(SDL_Renderer**), short, short);

/**
 * Action de chaque cliquable
 */
void Action(void*);

/**
 * Regarde si la souris est au dessus d'un bouton
 */
Clickable Over(int, int, Clickable*);

/**
 * Liberation de l'espace memoire utilise par les images SDL
 */
void freeUpMemoryButton(Clickable*, short);

#endif /* SRC_BUTTON_H_ */
