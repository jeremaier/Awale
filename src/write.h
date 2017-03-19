/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#ifndef WRITE_H
#define WRITE_H

/**
 * Efface le contenu du fichier
 */
void initialize(char*);

/**
 * Rajoute une ligne definie a la fin du fichier
 */
void write_new_line(char*, char*);

/**
 * Ecrit le temps passe a jouer dans le fichier (date de debut stockee dans tpsReference)
 */
void time_elapsed(FILE* file, struct tm *tpsReference);

/**
* Pour faire un print et non ecrire dans un fichier avec fprintf (redit time_elapsed())
*/
void timeElapsedToString (struct tm *tpsReference);

/**
 * Enregistre dans directory (= save.txt) toutes les donnees relative a une partie
 */
void save(char*, Game*, struct tm *tpsReference);

/**
* Enregistre les resultats d'une partie finie dans listGames.txt (reprise impossible) a la suite des precedentes
* A appeller des qu'une partie est terminee
*/
void saveInList (char *directory, Game*, struct tm *tpsReference);

#endif // WRITE_H
