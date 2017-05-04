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
void initialize(char*);

/**
 * Rajoute une ligne definie a la fin du fichier
 */
void writeNewLine(char*, char*);

/**
 * Ecrit le temps passe a jouer dans le fichier (date de debut stockee dans tpsReference)
 * Si on part d'une partie enregistree, on doit y rajouter le temps deja passe a jouer (additionnal)
 */
void timeElapsed(FILE*, struct tm*, int[3]);

/**
 * Pour faire un print et non ecrire dans un fichier avec fprintf (redit time_elapsed())
 */
void timeElapsedToString (struct tm*);

/**
 * Enregistre dans directory (= save.txt) toutes les donnees relative a une partie
 */
void save(const char*, Game*, struct tm*);

/**
 * Enregistre les resultats d'une partie finie dans listGames.txt (reprise impossible) a la suite des precedentes
 * A appeller des qu'une partie est terminee
 */
void saveInList(const char*, struct tm*);

/**
 * Affiche une belle partie en mode console
 */
void affichage(Game*);

#endif // WRITE_H
