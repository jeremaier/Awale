/*
 * movements.h
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#ifndef SRC_MOVEMENTS_H_
#define SRC_MOVEMENTS_H_

/**
 * Supprime les graines du trou selectionné et retourne le même nombre de graines
 */
short removeSeeds(short[][NB_HOLES], short, short);

/**
 * Distribution des graines prises dans un trou dans les trous successifs
 * de facon inverse des aiguilles d'une montre
 */
void distributeSeeds(short[][NB_HOLES], short, short);

#endif
