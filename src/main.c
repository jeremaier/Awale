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
#include "const.h"
#include "write.h"
#include "read.h"
#include "tests.h"
//#include <SDL/SDL.h> // il faut supprimer cet include pour afficher des printf sur la sortie standard
#include "game.h"
#include "main.h"

#include "ask.h"
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {

    // au demarrage proposer une interface sdl ou console (pb include SDL empeche le lancement console,
    //il faudra gerer avec les variables pre processeur)

    /*
    SDL_Surface *screen;
    if( SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Can't init SDL:  %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);

    if(screen == NULL) {
        printf( "Can't set video mode: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Delay(3000);
    FreeSurface ?

    return EXIT_SUCCESS;
    */



    // =========== TESTS ==========

    //testSave();
    //testSaveInList(); ok
    //playNewGame_c(); ok

    play_console();

    /*
     time_t secondes;
        struct tm timeExit;
        time(&secondes);
        timeExit = *localtime(&secondes);

    Game game = {42, "Olive", "Tom", 0, 0, {{5,6,2,4,3,4}, {4,4,4,4,4,4}}, &timeExit, 1, {0,0,0}};

    char file_save[NAME_FILE_SIZE] = "saved.txt";

    save(file_save, &game, &timeExit);
    */


    return 0;
}
