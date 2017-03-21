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
#include <SDL2/SDL_image.h>
#include <string.h>
#include "const.h"
#include "write.h"
#include "read.h"
#include "tests.h"
#include "game.h"
#include "ask.h"
#include "main.h"

int SDLError(char* message) {
    printf(message, SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
}

int main(int argc, char* args[]) {
    //Proposer une interface sdl ou console (pb include SDL empeche le lancement console,
    //il faudra gerer avec les variables pre processeur)

	short quit = 0;
	SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) return SDLError("Can't init SDL : %s\n");
	if(IMG_Init(IMG_INIT_JPG) < 0) return SDLError("Can't init SDL_image : %s\n");

	window = SDL_CreateWindow("Awale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS);
	if(window == NULL) return SDLError("Can't create window : %s\n");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) return SDLError("Can't create renderer : %s\n");

    char filename[PATH_SIZE] = "sprites/background.jpg";
    surface = IMG_Load(filename);
    if(surface == NULL) return SDLError("Can't create surface : %s\n");

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL) return SDLError("Can't create texture : %s\n");

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT: quit = 1;
                break;
        }

        SDL_Rect rect = {SCREEN_WIDTH / 2 - surface -> w / 2, SCREEN_HEIGHT / 2 - surface -> h / 2, surface -> w, surface -> h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
	return EXIT_SUCCESS;
    //*/

    /*/ =========== TESTS ==========

    //testSave();
    //testSaveInList();

    //playNewGame_c();
    //playSavedGame_c();

    play_ConsoleMode();

    //testSave();

    return 0;//*/
}
