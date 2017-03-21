/*
 * ask.h
 * Gere tout ce qui est demande d'information a l'utilisateur
 * Created on: 19 mars 2017
 *     Author: Olivier
 */

 #ifndef ASK_H
 #define ASK_H

 /**
 * Demande quel joueur doit commencer (1 ou 2)
 */
 int askCurrent();

 /**
 * Demande le nom du joueur et modifie le nom dans la structure game
 * Ne peut renvoyer directement la chaine de caractere (elle ne serait generee que dans le corps de la fonction
 * et non en dehors. Donc on pourrait renvoyer un pointeur vers cette chaine !
 */
 void askName(char* joueur, int numberPlayer);

 #endif // ASK_H
