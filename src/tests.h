/*
 * main.c
 *
 *  Created on: 14 mars 2017
 *      Author: Olivier
 */

#ifndef TESTS_H
#define TESTS_H

/**
 * Affiche le plateau de jeu stocke sous forme matricielle
 */
void testBoardInit(short[][NB_HOLES]);

/**
 * Permet de tester la sauvegarde des parametres d'une partie dans le fichier "save.txt"
 */
void testSave();

/**
* Test la sauvegarde dans listGames.txt
*/
void testSaveGame();

/**
* Affiche le contenu de la struct Game en parametre
*/
void gameToString(Game*);
#endif // TESTS_H
