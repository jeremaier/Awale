/*
 *  game.h
 *  Initialise les parametres d'une nouvelle partie
 *  Created on: 18 mars 2017
 *      Author: Olivier
 */

#ifndef GAME_H
#define GAME_H
#include "const.h"

/**
 * Pour connaitre le numero de la partie a creer on regarde le nombre de partie creee
 * dans listGames.txt ie nb de lignes ecrites
 */
int whichNumber(char*);

/**
 * Initialisation du plateau de jeu avec selection du joueur et le nombre de graines par trou
 */
void boardInit(short[][NB_HOLES]);

/**
 * Initialise la struct game lors d'une nouvelle partie
*/
void loard_blank_game(FILE* file_list, Game *game, struct tm *timer);

/**
* Indique si plus de graines dans le camps adverse (1 si oui, 0 sinon)
*/
int hasWinner(Game* game);

/**
* Demande de jouer un coup au current joueur
* et maj des parametres de struct game
*/
void nextStep(Game* game, int* caseSelected);

/**
* Arrete le jeu en renvoyant 1 et indique quel est le gagnant (gain max)
* Peut egalement faire la sauvegarde dans les .txt
*/
int quit(char fileSave[NAME_FILE_SIZE], char fileList[NAME_FILE_SIZE], Game* game, struct tm* dateCreation);

#endif // GAME_H

