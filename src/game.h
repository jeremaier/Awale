/*
 *  game.h
 *  Initialise les parametres d'une nouvelle partie
 *  Created on: 18 mars 2017
 *      Author: Olivier
 */

#ifndef GAME_H
#define GAME_H

#include "const.h"

typedef struct Game {
    short gameNumber; // le numero de la partie
    char joueur1[NAME_PLAYER_SIZE]; // nom joueur1 entre 1 (scanf exige au min une entree) et NAME_PLAYERS_SIZE-1 caracteres (cf askName)
    char joueur2[NAME_PLAYER_SIZE];
    short gains[2]; // nbre de graines collectees par les joueurs													  
    short board_config[NB_ROW][NB_HOLES]; // l'etat du plateau de jeu
    struct tm *creationGame; // date et heure de creation du jeu, ou de la derniere sauvegarde si on reprend une partie sauvegarde
    short currentPlayer; // joueur qui a la main (0 et 1)
    int timeSpent[3]; // le temps deja passer � jouer (utile dans le cas d'une sauvergarde) hrs min sec
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

/**
 * Arrete le jeu en renvoyant 1 et indique quel est le gagnant (gain max)
 * Peut egalement faire la sauvegarde dans les .txt
 */
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

/**
 * Fourni le temps present du jeu
 */
struct tm CurrentTime();

/**
 * Permet de jouer en console
 */
void PlayConsole();

/**
 * Initialisation ou reinitialisation de l'ensemble du jeu pour permettre de rejouer une partie
 */
void InitializeGame(char*, char*, short*);

/**
 * Signifie qu'une partie doit etre recommence
 */
short Restart();

#endif // GAME_H
