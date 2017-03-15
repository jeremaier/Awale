/*
 * main.c
 *
 *  Created on: 1 mars 2017
 *      Author: Jerem
 */

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "main.h"
#include "SDL2/SDL.h"

#include "tests.h"

// short au lieu de int car faibles unitees
short board[NB_ROW][NB_HOLES];

// initialisation de la matrice
void boardInit() {
    short player;

    //error: 'for' loop initial declarations are only allowed in C99 or C11 mode|
    int i; int j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;

    // on ne gere pas les erreurs d'entrees car ce sera des boutons
    printf("Quel joueur commence en premier ? haut(0), bas(1)\n");
    scanf("%hd", &player); // %hd used for a short int
}

int main(int argc, char** argv) {
    boardInit();

    // =========== TESTS ==========
    //testBoardInit(board);

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }

    {
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Awale", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

        if(pWindow) {
            SDL_Delay(3000);
            SDL_DestroyWindow(pWindow);
        } else {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}
