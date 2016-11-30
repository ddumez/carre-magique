/**
 * \file complet.hpp
 * \brief définition des fonction de l'algo de resolution complet
 * \author Dorian D.
 */
#include <functional>
#include <set>
#include <vector>
#include <cmath>

#ifndef COMPLET
#define COMPLET

#include "variable.hpp"
#include "carre.hpp"

/**
* \brief operateur pour comparer les variables * dans la file de priorite
*/
class mycomparison {
	public:
 		mycomparison() {}

	bool operator() (variable* lhs, variable* rhs) const {
		return lhs->getrestant()->size() < rhs->getrestant()->size();
  	}
};

/**
* \brief compare des int pour avoir aproximativement les valeures mediannes en premier
*/
class compint {
	private:
		int median;

	public:
 		compint(const int median) {this->median = median;}

	bool operator() (int lhs, int rhs) const {
		if (abs(this->median - lhs) == abs(this->median - rhs)) {
			return lhs < rhs;
		} else {
			return abs(this->median - lhs) < abs(this->median - rhs);
		}
  	}
};

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
bool resolCRec(carre * sol, set<variable *> * afaire);

#endif
