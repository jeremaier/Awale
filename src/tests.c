/*
 * test.c
 *
 *  Created on: 14 mars 2017
 *      Author: Olivier
 */
#include "tests.h"

void testBoardInit(short matrice[NB_ROW][NB_HOLES]) {
    printf("=== testBoardInit begin ===\n");
    int i, j;
     for(i = 0; i < NB_ROW; i++) {
    	for(j = 0; j < NB_HOLES; j++) {
    		printf("%hd ", matrice[i][j]);
        }
        printf("\n");
     } printf("=== testBoardInit end ===\n");
}
