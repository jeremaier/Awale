/*
 * test.h
 * Classe de test pour tester certaines methodes !
 * Created on: 14 mars 2017
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
void testSaveInList();

/**
* Permet d'afficher le contenu de Game game en console
*/
void gameToString(Game* game, struct tm*);

#endif // TESTS_H
