/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#ifndef WRITE_H
#define WRITE_H

// efface le contenu du fichier specitfie
void initialize(char*);

// rajoute la ligne chaine a la fin du fichier specifie
void write_new_line(char*, char*);

// ecrit dans file le temps passe a jouer (date de debut stockee dans tpsReference)
void time_elapsed(FILE*, struct tm *tpsReference);

// enregistre dans directory (= save.txt) toutes les donnees relative a une partie
void save(char*, Game*, struct tm *tpsReference); // sauve les donnees d'une partie dans save.txt

#endif // WRITE_H
