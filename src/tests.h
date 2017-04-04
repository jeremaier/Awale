/*
 * test.h
 * Classe de test pour tester certaines methodes !
 * Created on: 14 mars 2017
 *      Author: Olivier
 */

#ifndef TESTS_H
#define TESTS_H
#include "game.h"
#include "const.h"

/**
 * Affiche le plateau de jeu stocke sous forme matricielle
 */
void testBoardInit(short[][NB_HOLES]);

/**
 * Permet de tester la sauvegarde des parametres d'une partie dans un fichier
 */
void testSave(char*);

/**
 * Permet d'afficher le contenu de Game game en console
 */
void gameToString(Game*, struct tm*);

/**
 * Pour lancer une nouvelle partie
 */
void playNewGame_c();

/**
 * Pour jouer a un jeu sauvergarde
 */
void playSavedGame_c();

#endif // TESTS_H
