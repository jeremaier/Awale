/*
 *  game.h
 *  Initialise les parametres d'une nouvelle partie
 *  Created on: 18 mars 2017
 *      Author: Olivier
 */

#ifndef GAME_H
#define GAME_H

 #include <stdlib.h>
 #include <stdio.h>
 #include "const.h"

// pour connaitre le numero de la partie a creer on regarde le nombre de partie creee dans listGames.txt ie nb de lignes ecrites
// 1 partie par ligne
int whichNumber(char* directory[NAME_FILE_SIZE]);

#endif // GAME_H

