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

 void save (char* directory[NAME_FILE_SIZE], Game* game) {

    FILE* file = NULL;
    file = fopen(directory, "w"); // append, pour lire ou ecrire a la fin d'un fichier

    if (file != NULL) {

        // on recupere la date et heure
        time_t secondes;
        struct tm instant;
        time(&secondes);
        instant=*localtime(&secondes);
        fprintf(file, "date : %d/%d/%d %d:%d:%d\n", instant.tm_mday+1, instant.tm_mon+1, instant.tm_year+1900, instant.tm_hour, instant.tm_min, instant.tm_sec);

        fprintf(file, "n° game : %d\n", game -> gameNumber); // ecrit un int dans le fichier
        fprintf(file, "names : %s %s\n", game -> joueur1, game -> joueur2);
        fprintf(file, "profits : %d %d\n", game -> gain1, game -> gain2);

        int i, j;
        for (i=0; i<NB_ROW; i++) {
            for (j=0; j<NB_HOLES; j++)
                fprintf(file, "%d\n", game -> board_config[i][j]);
        }

        fprintf(file, "elapsed time : %f\n", game -> timeSpended);
        fprintf(file, "current player : %hd\n", game -> currentPlayer);
        fclose(file);
    }
    else {
        printf("Impossible d'ecrire dans le fichier");


    }
 }


