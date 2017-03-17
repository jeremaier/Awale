/*
 * const.h
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#ifndef SRC_CONST_H_
#define SRC_CONST_H_

/** CONCERNANT LES PARAMETRES SDL : **/
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

/** CONCERNANT LES PARAMETRES DU JEU : **/

#define NB_ROW 2
#define NB_HOLES 6
#define NB_SEED_INIT 4

#define NAME_PLAYER_SIZE 10

struct Game {
    short gameNumber;
    char joueur1[NAME_PLAYER_SIZE];
    char joueur2[NAME_PLAYER_SIZE];
    short gain1;
    short gain2;
    short board_config[NB_ROW][NB_HOLES];
    double timeSpended;
    short currentPlayer;
};
typedef struct Game Game;

/** CONCERNANT LA GESTION DES FICHIERS : **/

#define NAME_FILE_SIZE 10
#define LINE_SIZE 100

typedef enum Files Files;

#endif // SRC_CONST_H_
