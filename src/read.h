/*
 *  read.h
 *  Lecture des donnees stockees sur un .txt externe
 *  Created on: 15 mars 2017
 *      Author: Olivier
 */

#ifndef READ_H
#define READ_H
#include "game.h"
#include "const.h"

/**
 * Pour lire toutes les lignes d'un fichier
 */
void ReadLines(char*);

/**
 * Pour lire la ieme ligne
 */
void ReadSpecific(char*, int);

/**
 * 1 si le fichier est vide, 0 sinon
 */
int IsEmpty(const char[NAME_FILE_SIZE]);

/**
 * Lit les noms dans le fichier deja ouvert et modifie game.joueur
 * file car on evite d'ouvrir 2 fois le fichier (cf. loadGame)
 */
void ReadNames(FILE*, char[NAME_PLAYER_SIZE], char[NAME_PLAYER_SIZE]);

/**
 * Charge la struct game avec les donnees de la partie stockee dans saved.txt
 * Le temps passe a jouer sera celui deja passse (enregistre dans saved.txt) + le temps passe a jouer jusqu'a une nouvelle action
 */
void LoadSavedGame(Game*);

/**
 * Pour connaitre le numero de la partie a creer on regarde le nombre de partie creee
 * dans listGames.txt ie nb de lignes ecrites
 */
int WhichNumber(const char*);

#endif // READ_H
