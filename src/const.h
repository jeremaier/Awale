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
    short gameNumber; // le numero de la partie [1, 10]
    char joueur1[NAME_PLAYER_SIZE]; // nom joueur1 entre 1 (scanf exige au min une entree) et NAME_PLAYERS_SIZE-1 caracteres (cf askName)
    char joueur2[NAME_PLAYER_SIZE];
    short gain1; // nbre de graines collectees par le joueur 1
    short gain2;
    short board_config[NB_ROW][NB_HOLES]; // l'etat du plateau de jeu
    struct tm *creationGame; // date et heure de creation du jeu, ou de la derniere sauvegarde si on reprend une partie sauvegarde
    short currentPlayer; // joueur qui a la main
};
typedef struct Game Game;

/** CONCERNANT LA GESTION DES FICHIERS : **/

#define NAME_FILE_SIZE 15
#define LINE_SIZE 100

#endif // SRC_CONST_H_
