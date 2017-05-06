/*
 * menus.h
 *
 *  Created on: 16 avr. 2017
 *      Author: Jerem
 */

#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "const.h"
#include "button.h"

Clickable* clickableList;
short menuNumber, buttonNumber, restart;

/**
 * Cree tous les boutons du menu en fonction de leur image, de la position du premier bouton, de leur espacement entre eux et de leur fonction
 */
void CreateButtons(const char*[buttonNumber], const char*[buttonNumber], short (*[buttonNumber])(SDL_Renderer**), Clickable*, SDL_Renderer**, int, int, int, int, ButtonType, const char*[buttonNumber]);

/**
 * Affiche une liste de boutons en fonction des espaces entre eux
 */
void DisplayButtons(SDL_Renderer**, Clickable*, short);

/**
 * Lancement de la fenêtre de jeu et son affichage
 */
int LaunchWindow(SDL_Window**, SDL_Renderer**, SDL_Texture**);

/**
 * Affiche le gagnant s'il y en a un
 */
void OpenGameOverMenu(SDL_Renderer**, SDL_Texture**, SDL_Surface**, TTF_Font**, TTF_Font**, char*, SDL_Color, Clickable*);

/**
 * Affichage et interractions avec le menu pause
 */
short OpenOptionsMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu de sauvegarde
 */
short OpenSaveMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu de chargement de partie
 */
short OpenLoadMenu(SDL_Renderer**);

/**
 * Affichage et interractions avec le menu des scores
 */
short OpenScoreMenu(SDL_Renderer**);

#endif /* SRC_MENUS_H_ */
