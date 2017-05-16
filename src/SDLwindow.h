/*
 * SDLwindow.h
 *
 *  Created on: 14 avr. 2017
 *      Author: Jerem
 */

#ifndef SRC_SDLWINDOW_H_
#define SRC_SDLWINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "const.h"

/**
 * Renvoi une erreur lors d'erreurs d'initialisations de variables SDL
 */
int SDLError(char*);

/**
 * Assignation à la variable surface d'une nouvelle surface et à texture d'une nouvelle texture
 */
void CreateTexture(const char*, SDL_Surface**, SDL_Texture**, SDL_Renderer**);

/**
 * Affiche une texture à une certaine postion et avec une certaine dimension sur la fenetre
 */
void Display(SDL_Renderer*, SDL_Texture*, int, int, int, int, int);

/**
 * Affiche l'ensemble du menu principal (plateau, scores, bouton options)
 */
void BoardDiplayed(SDL_Renderer**, SDL_Rect*, SDL_Rect*, SDL_Rect*, SDL_Surface**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, TTF_Font**, SDL_Color);

/**
 * Rafraichi un texte
 */
void RefreshText(SDL_Renderer**, TTF_Font**, SDL_Rect*, SDL_Surface**, SDL_Texture**, const char* text, SDL_Color, short);

/**
 * Rafraichi l'ensemble du plateau
 */
void RefreshParameters(SDL_Renderer**, SDL_Rect*, SDL_Rect*, SDL_Rect*, SDL_Surface**, SDL_Surface**, SDL_Surface**, SDL_Surface**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, TTF_Font**, SDL_Color);

/**
 * Afficher un message temporaire sur la fenetre (ne clique pas sur la bonne rangée, sur une case vide,...)
 */
void PrintTempMessage(SDL_Renderer**, SDL_Texture**, SDL_Surface**, TTF_Font**, char*, SDL_Color);

/**
 * Lancement de toutes les initialisations SDL avec demarrage de la fenetre principale
 */
int LaunchSDL();

#endif /* SRC_SDLWINDOW_H_ */
