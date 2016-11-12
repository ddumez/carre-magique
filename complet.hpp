/**
 * \file complet.hpp
 * \brief définition des fonction de l'algo de resolution complet
 * \author Dorian D.
 */


#include "variable.hpp"
#include "carre.hpp"

#ifndef COMPLET
#define COMPLET

/**
* \brief retroune un carre magique normal de taille k remplit
*
* \param[in] k la taille du carré magique souhaité
* \return la solution sous al forme d'un carre
*/
carre * resolC(int k);

/**
* \brief parcour recursivement le carre pour le remplir
*
* \param[in,out] sol le carre sur lequel on travaille
* \param[in] i le premier indice de la case que l'on doit fixer
* \param[in] j le second indice de la case que l'on doit fixer
* \return si la grille a ete complete
*/
bool resolCRec(carre * sol, const int i, const int j);

#endif
