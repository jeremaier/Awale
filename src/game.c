/*
 * game.h
 *
 * Created on: 18 mars 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "game.h"

int whichNumber(char* directory) {
    FILE* file = NULL;
    file = fopen(directory, "r");

    char line[LINE_SIZE] = "";
    int cpt = 0;

    if (file != NULL) {
        while (fgets(line, LINE_SIZE, file) != NULL) {
            fgets(line, LINE_SIZE, file);
            cpt++;
        }

        fclose(file);
    }
    else printf("Impossible de lire le fichier");

    return cpt;
}

