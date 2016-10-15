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

typedef struct couple {
	int i;	// Premiere composante
	int j; // Deuxième composante
} couple;

/**
* \class carre: structure a la base de l'algo complet
*/
class carre {
		private:
	//atributs
		vector< vector<variable> > grille; /*!<la grille qui contien toutes les variables du carre */
		int k;/*!<la taille du carre*/
		vector<couple> historique; /*<historique des case auquel on a associe une valeur*/

		public:
	//constructeur
		/**
		* \brief construit un carre de taille k avec toutes les possibilite restante
		*
		* \param[in] k la taille du carre
		*/
		carre(const int k);

	//deconstructeur
		/**
		* \brief libere la memoire prise par un carre
		*/
		~carre();

	//methodes
		/**
		* \brief affiche la valeurs des variable de ce carre dans la sortie standard
		*/
		void affiche() const;

		/**
		* \brief assigne la valeur val a la case (i,j)
		*
		* \param[in] val la valeur a assigner
		* \param[in] i la premier coordonne de la case
		* \param[in] j la deuxieme coordonne de la case
		*/
		void choisir(const int val, const int i, const int j);

		/**
		* \brief annule le dernier assignement de variable
		*/
		void annuler();

		/**
		* \brief calcule si toute les valeurs ont ete atribue
		*
		* \return vrai ssi toutes les cases ont une valeur
		*/
		bool fini() const;

		/**
		* \brief calcule si cette solution est impossible
		*
		* \return vrai ssi il y a au moins une variable auquel on ne peut assigner aucune valeur
		*/ 
		bool culdesac() const;
};

#endif