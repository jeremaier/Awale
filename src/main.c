/*
 * main.c
 *
 *  Created on: 1 mars 2017
 *      Author: Jerem
 */

//#include "../essaiPerso.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // utilser la fonction _sleep(temps_ms);
#include <time.h>
#include <SDL2/SDL.h> // il faut supprimer cet include pour afficher des printf sur la sortie standard
#include <string.h>
#include "const.h"
#include "write.h"
#include "read.h"
#include "tests.h"
#include "game.h"
#include "ask.h"
#include "main.h"

int main(int argc, char** argv) {

    // au demarrage proposer une interface sdl ou console (pb include SDL empeche le lancement console,
    //il faudra gerer avec les variables pre processeur)

    /*
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* bitmapTex = NULL;
	SDL_Surface* bitmapSurface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Can't init SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    atexit(SDL_Quit);
    window = SDL_CreateWindow("Awale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
    							SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MOUSE_FOCUS);

    if(window == NULL) {
        printf("Can't create window : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL) {
        printf("Can't create renderer : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bitmapSurface = SDL_LoadBMP("sprites/background.jpg");
    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
    */



    // =========== TESTS ==========

    //testSave();
    //testSaveInList();

    //playNewGame_c();
    //playSavedGame_c();

    play_ConsoleMode();

    //testSave();

    return 0;
}
