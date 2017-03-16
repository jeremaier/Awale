/*
 * write.h
 *  Sauvegarde des differents parametres dans un fichier externe et lecture
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

 #include "write.h"

  void initalize (char* directory[NAME_FILE_SIZE]) { // demander confirmation (do, while)
    FILE* file = NULL;
    file = fopen(directory, "w");

    if (file != NULL) {
        fseek(file, 0, SEEK_SET); // on place le curseur au debut
        fputs("", file); // on ecrit la chaine de caractere vide
        fclose(file);
    }
    else {
        printf("Impossible d'ecrire dans le fichier");
    }
 }

 void write_new_ligne (char* directory[NAME_FILE_SIZE], char* chaine[LINE_SIZE]) {

    FILE* file = NULL;
    file = fopen(directory, "a"); // append, pour lire ou ecrire a la fin d'un fichier

    if (file != NULL) {
        fputs(chaine, file);
        fclose(file);
    }
    else {
        printf("Impossible d'ecrire dans le fichier");
    }
 }



