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

#endif // READ_H
