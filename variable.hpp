/**
 * \file variable.hpp
 * \brief définition des variables de l'algo complet
 * \author Dorian D.
 */

#include <vector>
#include <set>

using namespace std;

#ifndef VARIABLE
#define VARIABLE

/**
* \class variable: contien toutes les information sur une case d'un carre magique
*/
class variable {
	//atributs
		private:
			int val; /*!<la valeur de la variable si celle ci est fixé, 0 sinon */
			set<int> restant; /*!<ensemble des valeures possibles restantes*/
			vector< set<int> > historique; /*!<historique des valeure enleve a restant par les dernier choix*/

		public:
	//constructeur
		/**
		* \brief cree une variable qui a besoin d'etre initialise
		*/
		variable();

		/**
		* \brief construit une variable sans valeur avec comme valeur possible tout les nombre de 1 a k*k
		*
		* \param[in] k la taille de la grille a laquele apartien la variable
		*/
		variable(const int k);

	//deconstructeur
		~variable();

	//methodes
		/**
		* \brief initialise une variable comme le ferai le constructeur avec parametre
		*
		* \param[in] k la taille du carre auquel apartien la variable
		*/
		void initialise(const int k);

		/**
		* \brief choisis une valeure de la variable
		*
		* \param[in] val la valeur choisie
		*/
		void choix(const int val);

		/**
		* \brief indique qu'un nouveau choix a ete fait sur une autre variable
		*
		* \param[in] val la valeur prise par cette autre variable
		*/
		void nouveauchoix(const int val);

		/**
		* \brief enleve une valeur possible à la variable
		*
		* \param[in] val la valeur a enlever, si elle n'est deja plus possible ne fait rien
		*/
		void enlever(const int val);

		/**
		* \brief indique si l'ensemble des valeurs possible est vide
		*
		* \return vrai ssi l'ensemble des valeurs possible restant est vide et qu'elle n'a pas de valeur choisie
		*/
		bool estvide() const;

		/**
		* \brief si il ne reste que une seule valeur possible
		*
		* \return vrai ssi il ne reste que une seule valeur possible restante ou si la valeur à été choisie, sinon renvoi faux
		*/
		bool resteun() const;

		/**
		* \brief retourne la valeur de la variable, 0 si elle n'a pas ete choisie
		*
		* \return 0 ssi la valeur de la variable n'a pas encore ete fixe, sinon la valeur de la variable
		*/
		int getval() const;

		/**
		* \brief retourne l'ensemble des valeurs possible
		*
		* \return une reference vers l'ensemble des valeurs restantes
		*/
		set<int> const * getrestant() const;

		/**
		* \brief enleve la veleur de cette variable (la remet a 0)
		*/
		void enleverval();

		/**
		* \brief annule le dernier filtrage
		*/
		void annule();

};

#endif