/*
 *  read.h
 *  Lecture des donnees stockees sur un .txt externe
 *  Created on: 15 mars 2017
 *      Author: Olivier
 */

#ifndef READ_H
#define READ_H

#include <stdlib.h>
#include <stdio.h>
#include "const.h"

void readlines (char* directory[NAME_FILE_SIZE]); // Pour lire toutes les lignes d'un fichier
void read_specific (char* directory[NAME_FILE_SIZE], int i); //Pour lire la ieme ligne

#endif // READ_H
