#include <vector>

using namespace std;

#ifndef GRILLE
#define GRILLE

class grille {
	//atributs
		private:
		vector< vector<int> > lagrille; //tableau qui stoke les valeurs de la grille (0 si on n'y a rien mit)
		int k; //la taille de la grille

		public:
	//constructeur
		grille (const int k);
		
		grille (const grille * const original);
		
	//deconstructeur
		~grille() {}
		
	//methodes
		
		/**
		* retourne le nombre à la ieme ligne et la jeme colone (0 si il n'y a rien)
		*/
		int get(const int i, const int j) const;

		/**
		* met la valeur val dans la case à la ligne i et la colone j
		*/
		void put(const int i, const int j, const int val);

		/**
		* retourne le plus petit nombre positif que l'on ne peut pasmettre dans notre grille
		*/
		int borne() const;

		/**
		* retourne le nombre magique de cette grille
		*/	
		int nombremagique() const;

		/**
		* retoourne la taille de la grille
		*
		* @return le nombre de case par coté de la grille
		*/
		int taille() const;

		/**
		* affiche la grille dans la sortie standard
		*/
		void affiche() const;

		/**
		* somme tout les terme de la ieme ligne de la grille
		*
		* @param[in] grille la grille sur laquelle on travaille
		* @param[in] i le numero de la ligne dont on doit faire la somme
		* @return la somme des terme de la ieme ligne de la grille (les valeur non atribué sont à 0 donc elle ne compte pas)
		*/
		int sumL(const int i) const;

		/**
		* somme tout les terme de la jeme colone de la grille
		*
		* @param[in] grille la grille sur laquelle on travaille
		* @param[in] j le numero de la colone dont on doit faire la somme
		* @return la somme des terme de la jeme colone de la grille (les valeur non atribué sont à 0 donc elle ne compte pas)
		*/
		int sumC(const int j) const;

		/**
		* somme tout les terme de la 1ere diagonale de la grille
		*
		* @param[in] grille la grille sur laquelle on travaille
		* @return la somme des terme de la diagonale de gauche (en haut) à droite(en bas) de la grille 
				(les valeur non atribué sont à 0 donc elle ne compte pas)
		*/
		int sumd1() const;

		/**
		* somme tout les terme de la 2eme diagonale de la grille
		*
		* @param[in] grille la grille sur laquelle on travaille
		* @return la somme des terme de la diagonale de droite (en haut) à gauche (en bas) de la grille 
				(les valeur non atribué sont à 0 donc elle ne compte pas)
		*/
		int sumd2() const;
		
		/**
		* teste si la grille est corecte
		*
		* @param[in] present pour savoir si on doit tester les valeures presentes
		*/
		bool estCorrect(const bool present) const;

		/**
		* effectue toutes le permutation possible de chaque ligne et chaque colone pour selectionner la meilleure
		*
		* @return le score de la grille obtenue
		*/
		int permute();

		/**
		* teste toutes les permutation de la ieme ligne et applique la plus prometeuse (selon le score)
		*
		* @param[in] i le numero de la ligne à permuter
		*/
		void permuteL(const int i);

		/**
		* teste toutes les permutation de la jeme colone et applique la plus prometeuse (selon le score)
		*
		* @param[in}] j le numero de la colone à permuter
		*/
		void permuteC(const int j);

		/**
		* donne un score à la grille
		*
		* @param[in] la grille à tester
		* @return la somme des ecart au nombre magique sur chaque ligne, colone et diagonale
		*/
		int score() const;
		
		/**
		* re-initialise la grille comme à la construction
		*/
		void restart();
		
		/**
		* perturbe la grille pour sortir d'un minima local
		* effectue k permuatation de 2 éléments qui améliore le score
		*/
		void perturbe();

};

#endif
