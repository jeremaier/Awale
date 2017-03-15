/*
 * main.c
 *
 *  Created on: 14 mars 2017
 *      Author: Olivier
 */
#include "tests.h"

void testBoardInit(int matrice[][]) {
    printf("=== testBoardInit begin ===\n");
    int i, j;
     for(i = 0; i < NB_ROW; i++) {
    	for(j = 0; j < NB_HOLES; j++) {
    		printf("%d ", matrice[i][j]);
        }
        printf("\n");
     }
    printf("=== testBoardInit end ===\n");
}

void lecture_tab (int* tab, int taille) {
    int i;
    for (i=0; i<taille; i++) {
        printf("%d\n", tab[i]);
    }
}
