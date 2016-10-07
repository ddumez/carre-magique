/**
 * \file incomplet.hpp
 * \brief définition des fonction de l'algo de resolution incomplet
 * \author Dorian D.
 */


#include <vector>

#include "grille.hpp"

#ifndef INCOMPLET
#define INCOMPLET

/**
* \brief retroune un carre magique normal de taille k remplit
*
* \param[in] k la taille du carré magique souhaité
* \return un tableau de taille k*k contenant un carré magique normal de taille k
*/
grille * resolI(int k);

#endif
