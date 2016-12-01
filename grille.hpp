/**
 * \file grille.hpp
 * \brief définition de la grille, base de l'algo incomplet
 * \author Dorian D.
 */


#include <vector>

using namespace std;

#ifndef GRILLE
#define GRILLE

/**
* \class grille: la grille contien toute les information d'une grille de carré magique et tout les outils arriver elle meme à la solution
*/
class grille {
	//atributs
		private:
		vector< vector<int> > lagrille; /*!<tableau qui stoke les valeurs de la grille (0 si on n'y a rien mit)*/
		int k; /*!<la taille de la grille*/

		public:
	//constructeur
		/**
		* \brief construit et initialise une grille de taille k
		*
		* \param[in] k la taille de la grille
		*/
		grille (const int k);
		
		/**
		* \brief créé une copie de la grille originale
		*
		* \param[in] original la grille à copier
		*/
		grille (const grille * const original);
		
	//deconstructeur
		/**
		* \brief dessaloue toute la grille
		*/
		~grille() {}
		
	//methodes
		/**
		* \brief retourne le nombre à la ieme ligne et la jeme colone (0 si il n'y a rien)
		*/
		int get(const int i, const int j) const;

		/**
		* \brief met la valeur val dans la case à la ligne i et la colone j
		*/
		void put(const int i, const int j, const int val);

		/**
		* \brief retourne le plus petit nombre positif que l'on ne peut pas mettre dans notre grille
		*/
		int borne() const;

		/**
		* \brief retourne le nombre magique de cette grille
		*/	
		int nombremagique() const;

		/**
		* \brief retourne la taille de la grille
		*
		* \return le nombre de case par coté de la grille
		*/
		int taille() const;

		/**
		* \brief affiche la grille dans la sortie standard
		*/
		void affiche() const;

		/**
		* \brief somme tout les terme de la ieme ligne de la grille
		*
		* \param[in] i le numero de la ligne dont on doit faire la somme
		* \return la somme des terme de la ieme ligne de la grille
		*/
		int sumL(const int i) const;

		/**
		* \brief somme tout les terme de la jeme colone de la grille
		*
		* \param[in] j le numero de la colone dont on doit faire la somme
		* \return la somme des terme de la jeme colone de la grille
		*/
		int sumC(const int j) const;

		/**
		* \brief somme tout les terme de la 1ere diagonale de la grille
		*
		* \return la somme des terme de la diagonale de gauche (en haut) à droite(en bas) de la grille 
		*/
		int sumd1() const;

		/**
		* \brief somme tout les terme de la 2eme diagonale de la grille
		*
		* \return la somme des terme de la diagonale de droite (en haut) à gauche (en bas) de la grille 
		*/
		int sumd2() const;
		
		/**
		* \brief teste si la grille est corecte
		*
		* \param[in] present pour savoir si on doit tester les valeures presentes
		*/
		bool estCorrect(const bool present) const;

		/**
		* \brief effectue toutes le permutation possible de chaque ligne et chaque colone pour selectionner la meilleure
		*
		* \return le score de la grille obtenue
		*/
		int permute();

		/**
		* \brief teste toutes les permutation de la ieme ligne et applique la plus prometeuse (selon le score)
		*
		* \param[in] i le numero de la ligne à permuter
		*/
		void permuteL(const int i);

		/**
		* \brief teste toutes les permutation de la jeme colone et applique la plus prometeuse (selon le score)
		*
		* \param[in] j le numero de la colone à permuter
		*/
		void permuteC(const int j);

		/**
		* \brief donne un score à la grille
		*
		* \return la somme des ecart au nombre magique sur chaque ligne, colone et diagonale
		*/
		int score() const;
		
		/**
		* \brief re-initialise la grille comme à la construction
		*/
		void restart();
		
		/**
		* \brief parcour la grille et teste toutes les permutation possible de 2 element en les appliquants si elle ameliore le score
		*/
		void perturbe();

		/**
		* \brief pour eviter de recaluler le score en entier
		*
		* \param[in] i1 premier indice de la premier case
		* \param[in] j1 deuxieme indice de la premiere case
		* \param[in] i2 premier indice de la deuxieme case
		* \param[in] j2 deuxieme indice de la deuxieme case
		* \param[in] score le score actuel de la grille
		* \return le score de la grille si on inverse les deux case decrite en parametre
		*/
		int nouveauscore(const int i1, const int j1, const int i2, const int j2, const int score) const;
};

#endif
