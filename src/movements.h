/*
 * movements.h
 *
 *  Created on: 8 mars 2017
 *      Author: Jerem
 */

#ifndef SRC_MOVEMENTS_H_
#define SRC_MOVEMENTS_H_

/**
 * Distribution des graines prises dans un trou dans les trous successifs
 * de facon inverse des aiguilles d'une montre
 */
void distribute(short*, short, short);

/**
 * Supprime les graines du trou selectionné et retourne le même nombre de graines
 */
short remove(short*, short, short);

#endif
