/*
 *  read.h
 *  Lecture des donnees stockees sur un .txt externe
 *  Created on: 15 mars 2017
 *      Author: Olivier
 */

#ifndef READ_H
#define READ_H

/**
 * Pour lire toutes les lignes d'un fichier
 */
void readlines (char*);

/**
 * Pour lire la ieme ligne
 */
void read_specific (char*, int);

/**
* 1 si le fichier est vide, 0 sinon
*/
int isEmpty (char chemin[NAME_FILE_SIZE]);

/**
* Lit les noms dans le fichier deja ouvert et modifie game.joueur
* file car on evite d'ouvrir 2 fois le fichier (cf. loard_game)
*/
void readNames(FILE* file, char joueur1[NAME_PLAYER_SIZE], char joueur2[NAME_PLAYER_SIZE]);

#endif // READ_H
