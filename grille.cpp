#include <iostream>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
#include "grille.hpp"

using namespace std;

grille::grille (const int k) {
	vector<int> restant;
	for(int i = 0; i<k*k; ++i) {restant.push_back(i+1);}
	random_shuffle ( restant.begin(), restant.end() );
	int parc = 0;
	this->k = k;
	this->lagrille.resize(this->k);
	for(int i = 0; i<this->k; ++i) {
		this->lagrille.at(i).resize(this->k);
		for(int j = 0; j<k; ++j) {
			this->lagrille.at(i).at(j) = restant.at(parc);
			++parc;
		}
	}
}

grille::grille (const grille * const original) { //constructeur de recopie
	this->k = original->k;
	this->lagrille.resize(this->k);
	for(int i = 0; i<this->k; ++i) {
		this->lagrille.at(i).resize(this->k);
		for(int j = 0; j<this->k; ++j) {
			this->lagrille.at(i).at(j) = original->lagrille.at(i).at(j);
		}
	}
}

//methodes


int grille::get(const int i, const int j) const {
	return this->lagrille.at(i).at(j);
}


void grille::put(const int i, const int j, const int val) {
	this->lagrille.at(i).at(j) = val;
}


int grille::borne() const {
	return this->k * this->k + 1;
}


int grille::nombremagique() const {
	return ( this->k * (this->k * this->k + 1) ) /2;
}


int grille::taille() const {
	return this->k;
}


void grille::affiche() const {
	for(int i = 0; i<k; ++i) {
		for(int j = 0; j<k; ++j) {
			cout<<lagrille.at(i).at(j)<<" ";
		}
		cout<<"\n";
	}
}


int grille::sumL(const int i) const {
	int res = 0;
	for(int j = 0; j< this->k; ++j) {
		res += this->lagrille.at(i).at(j);
	}
	return res;
}


int grille::sumC(const int j) const {
	int res = 0;
	for(int i = 0; i< this->k; ++i) {
		res += this->lagrille.at(i).at(j);
	}
	return res;
}


int grille::sumd1() const {
	int res = 0;
	for(int i = 0; i< this->k; ++i) {
		res += this->lagrille.at(i).at(i);
	}
	return res;
}


int grille::sumd2() const {
	int res = 0;
	for(int i = 0; i< this->k; ++i) {
		res += this->lagrille.at(i).at(k-1-i);
	}
	return res;
}


bool grille::estCorrect(const bool present) const {
	//variable
		bool res = true;
		int i = 0;
		int j = 0;
		set<int> restant;
	//début
		
		if (present) {			
			for(i = 1; i<this->k * this->k+1; ++i) {
				restant.insert(i); //ensemble des valeurs possible : de 1 a k*k
			}
		}
	
		i = 0;
		while ( (i< this->k) && res ) {
			res = res && (this->sumL(i) == this->nombremagique()); //test somme des lignes
			res = res && (this->sumC(i) == this->nombremagique()); //test somme des colones
			
			if (present) {
				j = 0;
				while ( (i< this->k) && res ) { //teste si bonnes valeures
					res = res && (0 != restant.count(this->lagrille.at(i).at(j)));
					restant.erase(this->lagrille.at(i).at(j));
					++j;
				}	
			}
			
			++i;
		}
		
		//test diagonales
		res = res && (this->sumd1() == this->nombremagique()); 
		res = res && (this->sumd2() == this->nombremagique());
	
	//fin
	return res;
}
/*
int grille::permute() {
	grille * copie = new grille(*this);
	grille * copietmp;

	for(int i = 0; i<k; ++i) {
		//test des permuation en ligne
		copietmp = new grille (*this);
		copietmp->permuteL(i);
		if ( copietmp->score() < copie->score() ) {
			delete(copie);
			copie = new grille(*copietmp);
		}
		delete(copietmp);

		//test des permuation en colone
		copietmp = new grille (*this);
		copietmp->permuteC(i);
		if ( copietmp->score() < copie->score() ) {
			delete(copie);
			copie = new grille(*copietmp);
		}
		delete(copietmp);
	}

	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<this->k; ++j) {
			this->lagrille.at(i).at(j) = copie->lagrille.at(i).at(j);
		}
	}

	delete(copie);
	return this->score();
}

void grille::permuteL(const int i) {
	//variable
		grille copie(*this);
		int meilleur = this->score();
	
	//début
		sort(copie.lagrille.at(i).begin(),copie.lagrille.at(i).end());
		
		do { //passer en revue toutes les permutations de la ligne i
			if (copie.score() < meilleur) { //on applique les changements de copie sur notre grille
				for(int j = 0; j<this->k; ++j) {
					this->put(i,j,copie.lagrille.at(i).at(j));
				}
			}
		} while ( std::next_permutation(copie.lagrille.at(i).begin(),copie.lagrille.at(i).end()) );	
	//fin
}


void grille::permuteC(const int j) {
	//variable
		grille copie(*this);
		int meilleur = this->score();
		vector<int> colonej (this->k);
		int i;
	//début
		//on ne peut pas acceder directement à la jeme colone donc on la recopie dans un tableau
		for(i = 0; i<this->k; ++i) {
			colonej.at(i) = this->get(i,j);
		}
		
		sort(colonej.begin(),colonej.end());
		
		do { //passer en revue toutes les permutations de la ligne i
			//on met les changements dans notre copie
			for(i = 0; i<this->k; ++i) {
				copie.put(i,j,colonej.at(i));
			}
			
			if (copie.score() < meilleur) { //on applique les changements de copie sur notre grille si interessant
				for(int parc = 0; parc<this->k; ++parc) {
					this->put(parc,j,colonej.at(parc));
				}
			}
			
		} while ( std::next_permutation(colonej.begin(),colonej.end()) );	
	//fin
}
*/

int grille::score() const {
//score avec les moindre carré

	//variables
		int res = 0;
		int nbmagique = this->nombremagique();
	//debut
		for(int i = 0; i<this->taille(); ++i) {
			res += (int)pow( (double)(nbmagique - this->sumC(i)) , 2.0);
			res += (int)pow( (double)(nbmagique - this->sumL(i)) , 2.0);
		}
		res += (int)pow( (double)(nbmagique - this->sumd1()) , 2.0);
		res += (int)pow( (double)(nbmagique - this->sumd2()) , 2.0);
	//fin
	return res;

//score avec le nombre de contraintes respecté
/*
	//variable
		int res = 0;
		int nbmagique = this->nombremagique();
	
	//début
		for(int i = 0; i<k; ++i) {
			res += (this->sumC(i) != nbmagique);
			res += (this->sumL(i) != nbmagique);
		}
		res += (this->sumd1() != nbmagique);
		res += (this->sumd2() != nbmagique);
	
	//fin
	return res;
*/
}

void grille::restart() {
	vector<int> restant;
	for(int i = 0; i< (this->k) * (this->k); ++i) {restant.push_back(i+1);}
	random_shuffle ( restant.begin(), restant.end() );
	int parc = 0;

	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<k; ++j) {
			this->lagrille.at(i).at(j) = restant.at(parc);
			++parc;
		}
	}
}

void grille::perturbe() {
	//variable
		int i1,j1, i2, j2;
		int tmp;
		int score = this->score();
	//début
		i1 = 0;
		while ((i1 < this->k) && (0 != score)) {
			j1 = 0;
			while ((j1 < this->k) && (0 != score)) {
				i2 = i1;
				while ((i2 < this->k) && (0 != score)) {
					
					if(i1 == i2) {
						j2 = j1+1;
					} else {
						j2 = 0;
					}
					
					while ((j2 < this->k) && (0 != score)) {
						tmp = this->lagrille.at(i1).at(j1);
						this->lagrille.at(i1).at(j1) = this->lagrille.at(i2).at(j2);
						this->lagrille.at(i2).at(j2) = tmp;

						//on garde la permutation si elle est efficace
						if (this->score() <= score) {
							score = this->score();
						} else {
							tmp = this->lagrille.at(i2).at(j2);
							this->lagrille.at(i2).at(j2) = this->lagrille.at(i1).at(j1);
							this->lagrille.at(i1).at(j1) = tmp;
						}
						++j2;
					}
					++i2;
				}
				++j1;
			}
			++i1;
		} 
	//fin
}

int grille::nouveauscore(const int i1, const int j1, const int i2, const int j2, const int score) const {
	//variable
		int res = score;
	//debut
		res = res - this->sumC(j1) - this->sumC(j2) - this->sumL(i1) - this->sumL(i2);
		if (i1 == j1) {
			res -= this->sumd1();
		}
		if(j1 == this->k - i1 + 1) {
			res -= this->sumd2()
		}
		if (i2 == j2) {
			res -= this->sumd1();
		}
		if(j2 == this->k - i2 + 1) {
			res -= this->sumd2()
		}
	//fin
}