/*
 * read.c
 *
 *  Created on: 16 mars 2017
 *      Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "read.h"

void readlines(char* directory) {
    FILE* file = NULL;
    char line[LINE_SIZE] = "";

    file = fopen(directory, "r"); // lecture seule pour plus de securite

    if (file != NULL) {
        while (fgets(line, LINE_SIZE, file) != NULL)
            printf("%s", line); // le \n devra etre contenu dans la ligne a ajouter
        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");
}

void read_specific(char* directory, int i) {
    FILE* file = NULL;
    char line[LINE_SIZE] = "";

    file = fopen(directory, "r");

    if (file != NULL) {
        int k;
        for (k = 0; k < i; k++)
            fgets(line, LINE_SIZE, file);

        printf("%s", line);
        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");
}

int isEmpty(char chemin[NAME_FILE_SIZE]) {

    FILE* file = NULL;
    file = fopen(chemin, "r");

    char line = ' ';

    if (file != NULL) {
        line = fgetc(file);
        fclose(file);
    }
    else {
        printf("Impossible de lire le fichier\n");
    }

    return line == EOF;
}
