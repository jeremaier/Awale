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
    short gameNumber; // le numero de la partie [1, 10]
    char joueur1[NAME_PLAYER_SIZE]; // nom joueur1 entre 1 (scanf exige au min une entree) et NAME_PLAYERS_SIZE-1 caracteres (cf askName)
    char joueur2[NAME_PLAYER_SIZE];
    short gain1; // nbre de graines collectees par le joueur 1
    short gain2;
    short board_config[NB_ROW][NB_HOLES]; // l'etat du plateau de jeu
    struct tm *creationGame; // date et heure de creation du jeu, ou de la derniere sauvegarde si on reprend une partie sauvegarde
    short currentPlayer; // joueur qui a la main
    int timeSpent[3]; // le temps deja passer à jouer (utile dans le cas d'une sauvergarde) hrs min sec
} Game;

Game game;

/**
 * Pour connaitre le numero de la partie a creer on regarde le nombre de partie creee
 * dans listGames.txt ie nb de lignes ecrites
 */
int whichNumber(const char*);

/**
 * Initialise la struct game lors d'une nouvelle partie
 */
void loadBlankGame(const char*, Game*, struct tm*);

/**
 * Indique si plus de graines dans le camps adverse (1 si oui, 0 sinon)
 */
int hasWinner(Game*);

/**
 * Demande de jouer un coup au current joueur
 * et maj des parametres de struct game
 */
void nextStep(Game*, const int);

/**
 * Arrete le jeu en renvoyant 1 et indique quel est le gagnant (gain max)
 * Peut egalement faire la sauvegarde dans les .txt
 */
int quit(char[NAME_FILE_SIZE], char[NAME_FILE_SIZE], Game*, struct tm*);

#endif // GAME_H

