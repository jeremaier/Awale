/*
 * game.h
 *
 * Created on: 18 mars 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>
////////////
#include <string.h>
////////////

#include "menus.h"
#include "ask.h"
#include "time.h"
#include "write.h"
#include "read.h"
#include "movements.h"
#include "board.h"
#include "game.h"

void LoadBlankGame(const char* file_list, struct tm *timer) {
    // on demande le nom des joueurs et on complete la struct Game:
    //askName(game.joueur1, 1);
    //askName(game.joueur2, 2);

    game.gameNumber = WhichNumber(file_list);
    game.gains[0] = 0;
    game.gains[1] = 0;
    game.currentPlayer = 0; //game.currentPlayer = askCurrent(); // renvoie 0 ou 1 pour savoir a qui de jouer
    game.creationGame = timer;

    (game.timeSpent)[0] = 0;
    (game.timeSpent)[1] = 0;
    (game.timeSpent)[2] = 0;

    BoardInit(game.board_config);
}

int GameOver() {
    short i = 0;

    // on verifie que le joueur peut "nourrir" son adversaire (si il n'a plus de graine il ne pourra pas : inutile de verifier)
	for(i = 0; i < 6; i++) {
		if(game.currentPlayer == 0 && game.board_config[0][i] > i + 1)
			return 0; // Le joueur peut jouer : la partie n'est pas finie
		else if(game.board_config[1][i] > 5 - i)
			return 0; // Le joueur peut jouer : la partie n'est pas finie
	}

    const short a = game.gains[0] - game.gains[1]; // La partie est terminee : il faut trouver le vainqueur

    if(a > 0)
    	return 1; // le joueur 1 gagne
    else if(a < 0)
    	return 2; // le joueur 2 gagne

    return 3; // aucun joueur ne gagne : match nul
}

int Quit(char* file_save, char* file_list, struct tm *dateCreation) {
    //char file_save[NAME_FILE_SIZE] = "saved.txt";
    //char file_list[NAME_FILE_SIZE] = "listGames.txt";

    char ans = ' ';

    do {
        printf("\n Do you want to save the game ? (y/n)\n");
        scanf("\n%c", &ans);
    } while (ans != 'y' && ans != 'n');

    if (ans == 'y') {
        Save(file_save, &game, dateCreation);
        printf(" The game has been saved with success\n");
    }

/*    char ans2 = ' ';

    do {
        printf("\n Do you want to quit? (y/n)\n");
        scanf("\n%c", &ans2);
    } while (ans2 != 'y' && ans2 != 'n');

    if (ans2 == 'y') {

        // on retourne le gagnant :
        if (game -> gain1 > game -> gain2)
            printf("\n CONGRATULATION ! %s has won with a total score of: %d\n", game -> joueur1, game -> gain1);

        else {

            if (game -> gain1 < game -> gain2)
                printf("\n CONGRATULATION ! %s has won with a total score of: %d\n", game -> joueur2, game -> gain2);
            else printf("\n No winner for this game \n");
        }

        
        time_t secondes;
        struct tm timeExit;
        time(&secondes);
        timeExit = *localtime(&secondes);
        

        saveInList(file_list, game, dateCreation);
        printf(" listGames.txt has been completed\n");

        return 1;
    } */ //Si la partie est quittee avant d'etre finie, pas de gagnant
    return 0;
}

void ChangePlayer() {
    game.currentPlayer ++;
    game.currentPlayer %= 2;
}

void NextStep(const int caseSelected) {
    const short current = (game.currentPlayer); // on recupere le joueur qui a la main (0 ou 1)

    if (current == 0)
        printf("\n %s has choosen to play square %d \n", game.joueur1, caseSelected);
    else printf("\n %s has choosen to play square %d \n", game.joueur2, caseSelected);

    DistributeSeeds(current, caseSelected - 1);
    ChangePlayer();

    printf("\n");
    DisplayConsole(&game);
}

struct tm CurrentTime() {
    time_t secondes;
    time(&secondes);
    return *localtime(&secondes);
}

void PlayConsole() {
    const char file_save[NAME_FILE_SIZE] = "saved.txt";
    const char file_list[NAME_FILE_SIZE] = "listGames.txt";
    char answer = ' ';
    short flag = 1; // pour quitter le jeu

    printf(" ================ COMMANDS ================\n");
    printf(" To launch a new game, press n\n");
    printf(" To load form an existing game, press l\n");
    printf(" To save, press s\n");
    printf(" To quit, press q\n");
    printf(" To select a square, choose between 1 and 6\n");
    printf(" ==========================================\n\n");
    fflush(stdin);

    do {
        struct tm dateCreation = CurrentTime();
        answer = getc(stdin);

        switch(answer) {
        	// on lance a new game
        	case 'n':
				LoadBlankGame(file_list, &dateCreation); // on initialise la struct game vide
				printf("\n ========================== THE GAME BEGINS =========================\n\n");
				DisplayConsole(&game); // on affiche le plateau
				break;

			// on charge via une partie existante si elle existe
        	case 'l':
				// si le fichier de sauvergarde est vide, il faut creer une nouvelle partie
				if (IsEmpty(file_save)) {
					printf("No data has been found, launching a new game:\n");
					LoadBlankGame(file_list, &dateCreation); // on initialise la struct game vide
					printf("\n ========================== THE GAME BEGINS =========================\n\n");
					DisplayConsole(&game); // on affiche le plateau
				} else { // sinon on charge la partie enregistree
					LoadSavedGame(&game);
					printf("\n ========================== THE GAME BEGINS =========================\n\n");
					DisplayConsole(&game);
				}
				break;

        	case '1': case '2': case '3': case '4': case '5': case '6':
				// on n'autorise pas a jouer une case vide
				if ((game.board_config)[game.currentPlayer][answer - '0' - 1] != 0)
					NextStep(answer - '0');
				break;

        	case 'q':
				fflush(stdin); // pour vider le buffer de getc answer et pouvoir en faire un autre a la suite
				printf("Do you want to quit ? (y / n)\n");
				const char confirm  = getc(stdin);

				if (confirm == 'y') {
					// ajout de la partie dans listGames.txt
					SaveInList(file_list, &dateCreation);
					printf("%s has been completed\n", file_list);

					// on affiche le vainqueur
					// ...

					flag = 0;
				}
				//fflush(stdin); // on vide le buffer confirm
				break;

			case 's':
				fflush(stdin);
				Save(file_save, &game, &dateCreation);
				printf(" The game has been saved with success\n");
				break;
		}

        fflush(stdin); // on vide le buffer de answer (ou de confirm pour le cas 'q')
    } while (flag);
}

void Start(SDL_Renderer** renderer, SDL_Rect* playerRect, SDL_Rect* g1Rect, SDL_Rect* g2Rect, SDL_Surface** playerSurface, SDL_Surface** arrowSurface, SDL_Surface** g1Surface, SDL_Surface** g2Surface, SDL_Texture** fontTexture, SDL_Texture** playerTexture, SDL_Texture** arrowTexture, SDL_Texture** g1Texture, SDL_Texture** g2Texture, TTF_Font** boardFont, SDL_Color color, short* winner) {
	const char file_list[NAME_FILE_SIZE] = "listGames.txt";
	struct tm dateCreation = CurrentTime();
	LoadBlankGame(file_list, &dateCreation);
	//////////////////////////////
	strcpy(game.joueur1 , "PD");
	strcpy(game.joueur2 , "PD2");
	//////////////////////////////
	menuNumber = 0;
	restart = 0;
	*winner = 0;
	RefreshParameters(renderer, playerRect, g1Rect, g2Rect, playerSurface, arrowSurface, g1Surface, g2Surface, fontTexture, playerTexture, arrowTexture, g1Texture, g2Texture, boardFont, color);
}

short Restart() {
	return 0;
}
