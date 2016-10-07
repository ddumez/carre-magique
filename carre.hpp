/**
 * \file caree.hpp
 * \brief définition de la grille qui contien des variables
 * \author Dorian D.
 */

#include <vector>
#include <set>

using namespace std;

#ifndef CARRE
#define CARRE

/**
* \class carre: structure a la base de l'algo complet
*/
class carre {
		private:
	//atributs
		vector< vector<variable> > grille; /*!<la grille qui contien toutes les avriable s du carre */
		int k;/*!<la taille du carre*/

		public:
	//constructeur
		/**
		* \brief construit un carre de taille k avec toutes les possibilite restante
		*
		* \param[in] k la taille du carre
		*/
		carre(const int k);

	//deconstructeur

	//methodes
};

#endif