/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#ifndef WRITE_H
#define WRITE_H
#include "game.h"

/**
 * Efface le contenu du fichier
 */
void Initialize(char*);

/**
 * Rajoute une ligne definie a la fin du fichier
 */
void WriteNewLine(char*, char*);

/**
 * Ecrit le temps passe a jouer dans le fichier (date de debut stockee dans tpsReference)
 * Si on part d'une partie enregistree, on doit y rajouter le temps deja passe a jouer (additionnal)
 */
void TimeElapsed(FILE*, struct tm*, int[3]);

/**
 * Pour faire un print et non ecrire dans un fichier avec fprintf (redit time_elapsed())
 */
void TimeElapsedToString (struct tm*);

/**
 * Enregistre dans directory (= save.txt) toutes les donnees relative a une partie
 */
void Save(const char*, struct tm*);

/**
 * Enregistre les resultats d'une partie finie dans listGames.txt (reprise impossible) a la suite des precedentes
 * A appeller des qu'une partie est terminee
 */
void SaveInList(const char*, struct tm*);

/**
 * Affiche une belle partie en mode console
 */
void DisplayConsole(Game*);

#endif // WRITE_H
