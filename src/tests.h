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
void TestBoardInit(short[][NB_HOLES]);

/**
 * Permet de tester la sauvegarde des parametres d'une partie dans un fichier
 */
void TestSave(char*);

/**
 * Permet d'afficher le contenu de Game game en console
 */
void GameToString(Game*, struct tm*);

/**
 * Pour lancer une nouvelle partie
 */
void PlayNewGame();

/**
 * Pour jouer a un jeu sauvergarde
 */
void PlaySavedGame();

#endif // TESTS_H
