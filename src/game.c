#include "game.h"

int whichNumber(char* directory[NAME_FILE_SIZE]) {

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
    else {
        printf("Impossible de lire le fichier");
    }
}

