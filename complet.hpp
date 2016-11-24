/**
 * \file complet.hpp
 * \brief définition des fonction de l'algo de resolution complet
 * \author Dorian D.
 */
#include <functional>
#include <queue>
#include <vector>

#include "variable.hpp"
#include "carre.hpp"

#ifndef COMPLET
#define COMPLET

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
* \brief file de priorite pour prendre les variable en fonction de la taille du domaine restant
*/
typedef std::priority_queue<variable *,std::vector<variable *>,mycomparison> priority_queue_variable;

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
bool resolCRec(carre * sol, priority_queue_variable * afaire);

#endif
