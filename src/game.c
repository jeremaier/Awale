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

    int line;
    int cpt = 1; // si le fichier est vide, aucune partie n'a ete instanciee, on ecrit donc la numero 1

    if(file != NULL) {

        line = fgetc(file);

        while(line != EOF) {
            if (line == '\n') {
                cpt++;
            } line = fgetc(file);
        }

        fclose(file);
    }
    else printf("Impossible de lire le fichier\n");

    return cpt;
}

