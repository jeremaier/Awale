/*
 * game.h
 *
 * Created on: 18 mars 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int whichNumber(char* directory) {
    FILE* file = NULL;
    file = fopen(directory, "r");

    int const lineNbrPerSave = 19;
    int line;
    int cpt = 0;

    if(file != NULL) {
        while((line = fgetc(file)) != EOF) {
        	if(line == '\n')
        		cpt++;
        }

        fclose(file);
    }
    else printf("Impossible de lire le fichier");

    return cpt / lineNbrPerSave;
}

