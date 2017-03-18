/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

 #ifndef WRITE_H
 #define WRITE_H

 #include <stdlib.h>
 #include <stdio.h>
 #include "const.h"
 #include <time.h>

 // efface le contenu du fichier specitfie
 void initialize (char* directory[NAME_FILE_SIZE]);

 // rajoute la ligne chaine a la fin du fichier specifie
 void write_new_ligne (char* directory[NAME_FILE_SIZE], char* chaine[LINE_SIZE]);

 // ecrit dans file le temps passe a jouer (date de debut stockee dans tpsReference)
 void time_elapsed(FILE* file, struct tm *tpsReference);

 // enregistre dans save.txt toutes les donnees relative a une partie
 void save (char* directory[NAME_FILE_SIZE], Game* game, struct tm *tpsReference); // sauve les donnees d'une partie dans save.txt

 #endif // WRITE_H
