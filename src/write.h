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

 // premiere ligne du fichier reservée aux informations : joueur1, joueur2, grain1, grain2, time (score.txt)
 // board, gain1, gain2 (play_config.txt)

 void initialize (char* directory[NAME_FILE_SIZE]); // efface le contenu du fichier specitfie
 void write_new_ligne (char* directory[NAME_FILE_SIZE], char* chaine[LINE_SIZE]); // rajoute une ligne a la fin du fichier
 void save (char* directory[NAME_FILE_SIZE], Game* game); // sauve les donnees d'une partie dans save.txt

 void affiche (char*);

 #endif // WRITE_H
