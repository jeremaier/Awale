#include <stdio.h>
#include <stdlib.h>
#define NB_ROW 2
#define NB_SEED_INIT 4

void init() {
    short player;
    short nbHole;
    printf("Quel joueur commence en premier? (bas(0), haut(1))");
    scanf("%i", &player);
    printf("Combien de trou par rangees?");
    scanf("%i", &nbHole);
    short board[NB_ROW][nbHole] = NB_SEED_INIT;
}

void distribute(short *board[][], short init, short dest) {
    int i;

    /*for(i = init; i < *board[init], i++) {

    }*/
}

void change(short *board[][], short init, short dest) {
    *board[dest] = *board[init];
    remove(&board, init);
}

void remove(short *board[][], short hole) {
    //*board[init] =
}

int main() {
    init();
    return 0;
}
