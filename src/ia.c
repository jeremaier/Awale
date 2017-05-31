/*
 * ia.c
 *
 * Created on: 16 mai 2017
 *     Author: Olivier
 */

#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "movements.h"
#include "ia.h"

short PlayIA() {
    // On cherche le nombre de graines ramassables pour chaque possible
    short gainsPossibles[6] = {0};
    short currentTry; 
    short tmpRow = 1;
    for(currentTry = 0; currentTry < 6; currentTry++){
    	short nbgrne = game.board_config[1][currentTry];
    	if(isFeeding(nbgrne, 1, currentTry) == 0){
    		short i = currentTry;
    		short cpt;
    		for(cpt = 0; cpt < nbgrne; cpt++) {
				short endLine = NB_HOLES - i;

				if(tmpRow == 0) {
					if(endLine >= 6)
					tmpRow = 1;
					else i--;
				} else {
					if(endLine <= 1)
					tmpRow = 0;
					else i++;
				}
			}
			short finalHole = i;
			
			tmpRow = 0;
			if(tmpRow == 0){
				short gainPossible = 0;
				short j = finalHole;
				while(j < NB_HOLES && (game.board_config[tmpRow][j] == 2 || game.board_config[tmpRow][j] == 3)) {
					gainPossible += game.board_config[tmpRow][j];
					j++;
				}
				gainsPossibles[currentTry] = gainPossible;
			}
    	} else {
    		gainsPossibles[currentTry] = -1;
    	}
    }
    // On cherche l'indice du maximum dans la liste des gains possibles
    short idMax = 0;
    short k;
    for(k = 1; k < 6; k++){
    	if (gainsPossibles[idMax] <= gainsPossibles[k]){
    		idMax = k;
    	}
    }
    return idMax;
}