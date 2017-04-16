/*
 * menus.h
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_

#include <SDL2/SDL.h>
#include "button.h"

/**
 * Affiche une liste de boutons en fonction des espaces entre eux
 */
void DisplayButtons(SDL_Renderer**, Clickable*, short, int, int, int, int);

/**
 * Boucle d'interractions avec la fenetre du jeu
 */
void eventLoop(Clickable*);

/**
 * Liberation de l'espace memoire utilise par les images SDL
 */
void freeUpMemory(Clickable*, short);

/**
 * Affichage et interractions avec le menu pause
 */
void OpenOptionsMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu de sauvegarde
 */
void OpenSaveMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu de chargement de partie
 */
void OpenLoadMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu des scores
 */
void OpenScoreMenu(SDL_Renderer**);

#endif /* SRC_MENUS_H_ */
