/*
 * movements.h
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#ifndef SRC_MOVEMENTS_H_
#define SRC_MOVEMENTS_H_

short inOpponentRow;
short endHole;

/**
 * Verifie si on donne des graines a l'adversaire de facon a ce que la partie continue
 */
short isFeeding(const short, const short, const short);

/**
 * Supprime les graines du trou selectionné et retourne le même nombre de graines
 */
short RemoveSeeds(const short, const short);

/**
 * Distribution des graines prises dans un trou dans les trous successifs
 * de facon inverse des aiguilles d'une montre
 */
short DistributeSeeds(const short, const short);

/**
 * Verifie a chaque tour s'il y a des graines a recuperer
 */
void TakeWonSeeds(const short);

#endif
