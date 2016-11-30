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
		* \brief retourne le nombre magique de cette grille
		*/
		int nombremagique() const;

		/**
		* \brief retourne la taille du carre magique
		*/
		int gettaille() const;

		/**
		* \brief affiche la valeurs des variable de ce carre dans la sortie standard
		*/
		void affiche() const;

		/**
		* \brief renvoir un pointeur vers la variable demande
		*
		* \param[in] i le premier indice de la variable
		* \param[in] j le deuxieme indice de la variable
		* \return un pointeur sur la variable situe a la case (i,j)
		*/
		variable * getvar(const int i, const int j);

		/**
		* \brief assigne la valeur val a la case (i,j)
		*
		* \param[in] val la valeur a assigner
		* \param[in] i la premier coordonne de la case
		* \param[in] j la deuxieme coordonne de la case
		*/
		void choisir(const int val, const int i, const int j);

		/**
		* \brief filtre les valeur possible sur une ligne apres une affectation sur celle ci
		* si une variable est filtre sa colone le sera
		*
		* \param[in] i la ligne a filtrer
		*/
		void filtrerligne(const int i);

		/**
		* \brief filtre les valeur possible sur une colonne apres une affectation sur celle ci
		* si une variable est filtre sa ligne le sera
		*
		* \param[in] j la colone a filtrer
		*/
		void filtrercolonne(const int j);

		/**
		* \brief filtre le valeur possible des varible des coin pour eviter les symetries
		* si une variable est filtre sa ligne et sa colone le seront
		*/
		void filtrersymetrie();

		/**
		* \brief renvoi l'ensemble des valeurs restantes possible pour la case (i,j)
		*
		* \param[in] i le premier indice de la case
		* \param[in] j le second indice de la case
		* \return l'ensemble des valeurs restantes pour cette case
		*/
		const set<int> * const getrestant(const int i, const int j);

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
		bool culdesac(const set<variable *> * const afaire) const;

		/**
		* \brief calcule la somme des valeur assigne sur la ligne i
		* 
		* \param[in] i le numero de la ligne dont on doit calculer la somme
		* \return la somme des valeurs des variable de la iemme ligne
		*/
		int suml(const int i) const;

		/**
		* \brief calcule la somme des valeurs assigne sur la colone j
		* 
		* \param[in] j le numero de la colone dont on doit calculer la somme
		* \return la somme des valeurs des variable de la jemme colone
		*/
		int sumc(const int j) const;

		/**
		* \brief calcule la somme des valeurs assigne sur 1ere diagonale
		* 
		* \return la somme des valeurs des variable de la 1ere diagonale
		*/
		int sumd1() const;

		/**
		* \brief calcule la somme des valeurs assigne sur 1ere diagonale
		* 
		* \return la somme des valeurs des variable de la 1ere diagonale
		*/
		int sumd2() const;

		/**
		* \brief regarde si toutes la variables de la iemme ligne ont une valeur
		*
		* \param[in] i la ligne a etudier
		* \return vrai ssi toutes les variables de la iemme ligne ont une valeur associe
		*/
		bool allassignligne(const int i) const;

		/**
		* \brief regarde si toutes la variables de la jemme colone ont une valeur
		*
		* \param[in] j la colone a etudier
		* \return vrai ssi toutes les variables de la jemme colone ont une valeur associe
		*/
		bool allasigncolone(const int j) const;

		/**
		* \brief regarde si toutes la variables de la 1ere diagonale ont une valeur
		*
		* \return vrai ssi toutes les variables de la 1ere diagonale ont une valeur associe
		*/
		bool allassignd1 () const;

		/**
		* \brief regarde si toutes la variables de la 2eme diagonale ont une valeur
		*
		* \return vrai ssi toutes les variables de la 2eme diagonale ont une valeur associe
		*/
		bool allassignd2() const;
};

#endif