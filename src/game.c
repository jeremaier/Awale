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
#include "ask.h"
#include "time.h"
#include "write.h"

int whichNumber(char* directory) { // date | game_number | name_winner | gain winner | name_loser | gain_loser | time_elapsed

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

void boardInit(short board[][NB_HOLES]) {

    int i, j;
    for(i = 0; i < NB_ROW; i++)
    	for(j = 0; j < NB_HOLES; j++)
    		board[i][j] = NB_SEED_INIT;
}

void init_game(Game *game, struct tm *timer) {

    char file_saved[NAME_FILE_SIZE] = "saved.txt";
    char file_list[NAME_FILE_SIZE] = "listGames.txt";

    // on recupere quel devrait etre le numero de cette partie (i+1 si i parties deja jouees)
    int number = whichNumber(file_list);

    // on ne gere pas le cas de la sauvergarde pour le moment (apres) :
    game -> gameNumber = number;
    game -> gain1 = 0;
    game -> gain2 = 0;
    game -> currentPlayer = askCurrent(); // renvoit 1 ou 2 pour savoir a qui de jouer en premier
    game -> creationGame = timer;

    // whichNumber == numeroDeLaPartieDansSaved, alors c'est une sauvergarde

}

void play() {

    char answer = ' ';

        do {

            // on cree la struct game
            Game game;

            // on initialise son tableau de jeu avec NB_SEED_INIT
            boardInit(game.board_config);

            /** test1, affichage du plateau
            int i, j;
            for(i = 0; i < NB_ROW; i++) {
                for(j = 0; j < NB_HOLES; j++)
                    printf("%hd ", game.board_config[i][j]);

                printf("\n");
            }*/

            // on demande le nom des joueurs et on complete la struct Game:
            askName(game.joueur1);
            askName(game.joueur2);

            // on recupere les infos temporelles de sa creation
            time_t secondes;
            struct tm creationGame;
            time(&secondes);
            creationGame = *localtime(&secondes);

            // on initialise la struct Game
            init_game(&game, &creationGame);

            /** test2, affichage de Game game: */
            gameToString(&game, &creationGame);

            /** test3, sauvegarde de la structure creee dans saved.txt*/
            char file_saved[NAME_FILE_SIZE] = "saved.txt";
            save(file_saved, &game, &creationGame);

            /** test4, ajout de la partie a la list des parties finies (listGames.txt) */
            char file_list[NAME_FILE_SIZE] = "listGames.txt";
            saveInList(file_list, &game, &creationGame);

            // pour rejouer
            printf("\n PLAY AGAIN? (y/n)\n");
            do {
                scanf("%c", &answer);
            } while (answer != 'y' && answer != 'n');
        } while (answer == 'y');
}

/*void jouer() {}

    - s'il s'agit d'une nouvelle partie :

        _ on recupere le numero de la partie a creer via whichNumber()
        _ on demande le nom des 2 joueurs
        _ les gains sont mis a 0
        _ le plateau de jeu est initialise
        _ on recupere la date d'execution de la fonction comme date de creation du jeu (repere pour time elapsed)
        _ on demande qui doit commencer (joueur 1 ou 2)

        TANT QUE : il n'y a pas de gagnant || on ne quitte pas la partie (avec confirmation && quitter sans sauvergarder ?)

        _ si sauvergarde, on enregistre les parametres dans saved.txt via save() avec maj time_elapsed
        _ si gagnant on enregistre la partie a la suite dans listGames.txt

        _ sinon, on recupere l'action a jouer
        _ si conforme aux regles, maj gains, plateau de jeu, current joueur (current++ mod 2)

        FIN TANT QUE

    - s'il s'agit d'une reprise a partir d'une sauvergarde existante dans saved.txt :

        _ on recupere les infos et maj via elles (on doit recupere le vrai temps du debut de la partie cette fois)
        _ on rentre dans la boucle precedente
*/
