/*
 *  game.h
 *  Initialise les parametres d'une nouvelle partie
 *  Created on: 18 mars 2017
 *      Author: Olivier
<<<<<<< HEAD
 */

#ifndef GAME_H
#define GAME_H
=======
 */

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

>>>>>>> 71720aea6652c56179be587913923dbe0a699aa0
#include "const.h"

typedef struct Game {
    short gameNumber; // le numero de la partie [1, 10]
    char joueur1[NAME_PLAYER_SIZE]; // nom joueur1 entre 1 (scanf exige au min une entree) et NAME_PLAYERS_SIZE-1 caracteres (cf askName)
    char joueur2[NAME_PLAYER_SIZE];
<<<<<<< HEAD
    short gain[2]; // nbre de graines collectees par les joueurs 
=======
    short gains[2];
>>>>>>> 71720aea6652c56179be587913923dbe0a699aa0
    short board_config[NB_ROW][NB_HOLES]; // l'etat du plateau de jeu
    struct tm *creationGame; // date et heure de creation du jeu, ou de la derniere sauvegarde si on reprend une partie sauvegarde
    short currentPlayer; // joueur qui a la main
    int timeSpent[3]; // le temps deja passer à jouer (utile dans le cas d'une sauvergarde) hrs min sec
<<<<<<< HEAD
} Game;

Game game;

/**
 * Initialise la struct game lors d'une nouvelle partie
 */
void loadBlankGame(const char*, struct tm*);

/**
 * Regarde si la partie est finie, si oui, on indique le joueur gagnant
 */
int gameOver();
=======
} Game;

Game game;

/**
 * Initialise la struct game lors d'une nouvelle partie
 */
void LoadBlankGame(const char*, struct tm*);

/**
 * Regarde si la partie est finie, si oui, on indique le joueur gagnant
 */
int GameOver();
>>>>>>> 71720aea6652c56179be587913923dbe0a699aa0

/**
 * Arrete le jeu en renvoyant 1 et indique quel est le gagnant (gain max)
 * Peut egalement faire la sauvegarde dans les .txt
 */
<<<<<<< HEAD
int quit(char[NAME_FILE_SIZE], char[NAME_FILE_SIZE], struct tm*);

/**
 * Demande de jouer un coup au current joueur
 * et maj des parametres de struct game
 */
void nextStep(const int);
=======
int Quit(char[NAME_FILE_SIZE], char[NAME_FILE_SIZE], struct tm*);

/**
 * Changement de joueur courant
 */
void ChangePlayer();

/**
 * Demande de jouer un coup au current joueur
 * et maj des parametres de struct game
 */
void NextStep(const int);
>>>>>>> 71720aea6652c56179be587913923dbe0a699aa0

/**
 * Fourni le temps present du jeu
 */
struct tm CurrentTime();

/**
 * Permet de jouer en console
 */
<<<<<<< HEAD
void play_console();

#endif // GAME_H

=======
void PlayConsole();

/**
 * Initialisation ou reinitialisation de l'ensemble du jeu pour permettre de rejouer une partie
 */
void Start(SDL_Renderer**, SDL_Rect*, SDL_Rect*, SDL_Rect*, SDL_Surface**, SDL_Surface**, SDL_Surface**, SDL_Surface**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, SDL_Texture**, TTF_Font**, SDL_Color);

/**
 * Signifie au jeu que le bouton "recommencer" a été appuyé
 */
short Restart();

#endif // GAME_H

>>>>>>> 71720aea6652c56179be587913923dbe0a699aa0
