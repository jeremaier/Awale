/*
 * read.c
 *
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#include "read.h"

void readlines (char* directory[NAME_FILE_SIZE]) {

    FILE* file = NULL;
    char line[LINE_SIZE] = "";

    file = fopen(directory, "r"); // lecture seule pour plus de securite

    if (file != NULL) {
        while (fgets(line, LINE_SIZE, file) != NULL) {
            printf("%s", line); // le \n devra etre contenu dans la ligne a ajouter
        }
        fclose(file);
    }
    else {
        printf("Impossible de lire le fichier");
    }
}

void read_specific(char* directory[NAME_FILE_SIZE], int i) {
    FILE* file = NULL;
    char line[LINE_SIZE] = "";

    file = fopen(directory, "r");

    if (file != NULL) {
        int k;
        for (k=0; k<i; k++) {
            fgets(line, LINE_SIZE, file);
        }
        printf("%s", line);
        fclose(file);
    }
    else {
        printf("Impossible de lire le fichier");
    }
}

