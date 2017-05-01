/*
 * ask.h
 * Gere tout ce qui est demande d'information a l'utilisateur
 * Created on: 19 mars 2017
 *     Author: Olivier
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "ask.h"

int askCurrent() {
    short ans = 0;

    do {
        printf("Who is the current player ? (1 / 2)\n");
        scanf("%hd", &ans);
    } while(ans != 1 && ans != 2);

    return ans - 1; // -1 pour compatibilite avec affichage
 }

void askName(char joueur[NAME_PLAYER_SIZE], int numberPlayer) { // prend game.joueur1 en parametre (string, donc pointeur)
    char input[NAME_PLAYER_SIZE - 1];
    int i;

    do {
        printf("What's the name of player no %d:\n", numberPlayer);
        scanf("%s", input);
    } while(strlen(input) > NAME_PLAYER_SIZE);

    // on copie la valeur input dans joueur:
    for(i = 0; i < strlen(input); i++)
        joueur[i] = input[i];

    // pour eviter de garder des traces de nom precedent s'ils sont plus long que les nouveaux
    joueur[strlen(input)] = '\0';
}
