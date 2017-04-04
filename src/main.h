/*
 * main.h
 *
 *  Created on: 1 mars 2017
 *      Author: Jerem
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

/*
 * Renvoi une erreur lors d'erreurs d'initialisations de variables SDL
 */
int SDLError(char*);

/*
 * Assignation à la variable surface d'une nouvelle surface et à texture d'une nouvelle texture
 */
void CreateTexture(char*, SDL_Surface**, SDL_Texture**, SDL_Renderer**);

/*
 * Affiche une texture à une certaine postion et avec une certaine dimension sur la fenetre
 */
void Display(SDL_Renderer*, SDL_Texture*, SDL_Surface*, int, int, int, int);

/*
 * Lancement de la fenêtre de jeu et son affichage
 */
int LaunchWindow(SDL_Window**, SDL_Renderer**, SDL_Surface**, SDL_Texture**);

#endif
