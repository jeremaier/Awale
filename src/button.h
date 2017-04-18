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

Clickable CreateNewButton(int, int, const char*, Clickable*, SDL_Renderer**, void (*)(SDL_Renderer**), short, short);

/**
 * Action de chaque cliquable
 */
void Action(void*);

/**
 * Va tester la position de chaque bouton pour savoir si on a cliquer dedans
 */
void Click(int, int, Clickable*);

#endif /* SRC_BUTTON_H_ */
