#include "variable.hpp"
#include "carre.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>

using namespace std;

carre::carre(const int k) {
	this->k = k;
	this->historique.resize(0);

	this->grille.resize(k);
	for(int i = 0; i<k; ++i) {
		this->grille.at(i).resize(k);
		for(int j = 0; j<k; ++j) {
			this->grille.at(i).at(j).initialise(k,i,j);
		}
	}
}

carre::~carre() {}

int carre::nombremagique() const {
	return ( this->k * (this->k * this->k + 1) ) /2;
}

int carre::gettaille() const {
	return this->k;
}

void carre::affiche() const {
	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<this->k; ++j) {
			cout<<this->grille.at(i).at(j).getval()<<" ";
		}
		cout<<"\n";
	}
}

variable * carre::getvar(const int i, const int j) {
	return & this->grille.at(i).at(j);
}

void carre::choisir(const int val, const int i, const int j) {
	this->grille.at(i).at(j).choix(val);

	for(int parci = 0; parci<this->k; ++parci) {
		for(int parcj = 0; parcj<this->k; ++parcj) {
			if ( (i != parci) || (j != parcj) ) {
				this->grille.at(parci).at(parcj).nouveauchoix(val);
			}
		}
	}
	couple nouv; nouv.i = i; nouv.j = j;
	this->historique.push_back(nouv);
}

void carre::filtrerligne(const int i) {
	if (! this->allassignligne(i)) {
		const int sum = this->suml(i); //on calule la somme actuelle de la ligne
		int tmp, j;
		int minval, maxval; //valeur etremes autorises
		int min = this->k * this->k; //plus petites valeurs des domaines, initialise a la plus grande
		int max = 0; //plus grandes valeurs des domaines, initialise a la plus petite
		vector<int> afixer; //indice des cases qu'il reste a fixer
		set<int> resteij;

		//recherche du min et du max
		for(j=0; j<this->k; ++j) { //pour toute les variables
			if ( 0 == this->grille.at(i).at(j).getval() ) { //si la variable n'est fixe
				//on trouve le min du domaine restant de (i,j) ou sa valeur si il est fixe et on le compare au min deja touve
				if( (tmp = (0 == this->grille.at(i).at(j).getval()) ? *min_element(this->grille.at(i).at(j).getrestant()->begin(),this->grille.at(i).at(j).getrestant()->end()) : this->grille.at(i).at(j).getval()) < min ) {
					min = tmp;
				}
				if( (tmp = (0 == this->grille.at(i).at(j).getval()) ? *max_element(this->grille.at(i).at(j).getrestant()->begin(),this->grille.at(i).at(j).getrestant()->end()) : this->grille.at(i).at(j).getval() ) > max ) {
					max = tmp;
				}
				afixer.push_back(j);
			}
		}

		//calcul des valeur extreme autorise
		minval = this->nombremagique() - sum + (afixer.size() -1)*( (afixer.size() / 2) -1 -max);
		maxval = this->nombremagique() - sum - (afixer.size() -1)*( (afixer.size() / 2) -1 +min);

		//on filtre les valeurs non autorise
		for(int j : afixer) {
			resteij = set<int>(* this->grille.at(i).at(j).getrestant());
			tmp = 0;
			for(set<int>::iterator it = resteij.begin() ; it!=resteij.end() ; ++it) {
				if ( (*it < minval) || (*it > maxval) ){
					this->grille.at(i).at(j).enlever(*it);
					++tmp;
				}
			}
			if(0 != tmp){this->filtrercolonne(j);}
		}
	}
}

void carre::filtrercolonne(const int j) {
	if (! this->allasigncolone(j)) {
		const int sum = this->sumc(j); //on calule la somme actuelle de la colonne
		int tmp, i;
		int minval, maxval; //valeur etremes autorises
		int min = this->k * this->k; //plus petites valeurs des domaines
		int max = 0; //plus grandes valeurs des domaines
		vector<int> afixer; //indice des cases qu'il reste a fixer
		set<int> resteij;

		//recherche du min et du max
		for(i=0; i<this->k; ++i) { //pour toute les variables
			if ( 0 == this->grille.at(i).at(j).getval() ) { //si la variable n'est fixe
				if( (tmp = (0 == this->grille.at(i).at(j).getval()) ? *min_element(this->grille.at(i).at(j).getrestant()->begin(),this->grille.at(i).at(j).getrestant()->end()) : this->grille.at(i).at(j).getval()) < min ) {
					min = tmp;
				}
				if( (tmp = (0 == this->grille.at(i).at(j).getval()) ? *max_element(this->grille.at(i).at(j).getrestant()->begin(),this->grille.at(i).at(j).getrestant()->end()) : this->grille.at(i).at(j).getval()) > max ) {
					max = tmp;
				}
				afixer.push_back(i);
			}
		}

		//calcul des valeur extreme autorise
		minval = this->nombremagique() - sum + (afixer.size() -1)*( (afixer.size() / 2) -1 -max);
		maxval = this->nombremagique() - sum - (afixer.size() -1)*( (afixer.size() / 2) -1 +min);

		//on filtre les valeurs non autorise
		for(int i : afixer) {
			resteij = set<int>(* this->grille.at(i).at(j).getrestant());
			tmp = 0; //compte le nombre de valeur enleve
			for(set<int>::iterator it = resteij.begin() ; it!=resteij.end() ; ++it) {
				if ( (*it < minval) || (*it > maxval) ){
					this->grille.at(i).at(j).enlever(*it);
					++tmp;
				}
			}
			if (0 != tmp) {this->filtrerligne(i);}
		}
	}
}

void carre::filtrersymetrie() {
	int borne1, borne2, compt;
	set<int> reste;

	//filtrage de c[1,1]
	if (0 == this->grille.at(0).at(0).getval()) { //si elle n'est pas deja affecte
		//pour c[1,1] > c[1,n]
		borne1 = (0 == this->grille.at(0).at(this->k-1).getval()) ? *min_element(this->grille.at(0).at(this->k-1).getrestant()->begin(),this->grille.at(0).at(this->k-1).getrestant()->end()) : this->grille.at(0).at(this->k-1).getval();
		//pour c[1,1] > c[n,n]
		borne2 = (0 == this->grille.at(this->k-1).at(this->k-1).getval()) ? *min_element(this->grille.at(this->k-1).at(this->k-1).getrestant()->begin(),this->grille.at(this->k-1).at(this->k-1).getrestant()->end()) : this->grille.at(this->k-1).at(this->k-1).getval();
		//domaine de c[1,1]
		reste = set<int>(* this->grille.at(0).at(0).getrestant());

		//filtrage
		compt = 0; //compte le nombre de valeur enleve

		for(set<int>::iterator it = reste.begin() ; it!=reste.end() ; ++it) {
			if ( (*it <= borne1) || (*it <= borne2) ){
				this->grille.at(0).at(0).enlever(*it);
				++compt;
			}
		}
		if (0 != compt) {this->filtrerligne(0); this->filtrercolonne(0);}
	}

	//filtrage de c[1,n]
	if (0 == this->grille.at(0).at(this->k-1).getval()) {
		//pour c[1,1] > c[1,n]
		borne1 = (0 == this->grille.at(0).at(0).getval()) ? *max_element(this->grille.at(0).at(0).getrestant()->begin(),this->grille.at(0).at(0).getrestant()->end()) : this->grille.at(0).at(0).getval();
		//pour c[1,n] > c[n,1]
		borne2 = (0 == this->grille.at(this->k-1).at(0).getval()) ? *min_element(this->grille.at(this->k-1).at(0).getrestant()->begin(),this->grille.at(this->k-1).at(0).getrestant()->end()) : this->grille.at(this->k-1).at(0).getval();
		//domaine de c[1,n]
		reste = set<int>(* this->grille.at(0).at(this->k-1).getrestant());

		//filtrage
		compt = 0; //compte le nombre de valeur enleve

		for(set<int>::iterator it = reste.begin() ; it!=reste.end() ; ++it) {
			if ( (*it >= borne1) || (*it <= borne2) ){
				this->grille.at(0).at(this->k-1).enlever(*it);
				++compt;
			}
		}
		if (0 != compt) {this->filtrerligne(0); this->filtrercolonne(this->k-1);}
	}

	//filtrage de c[n,n]
	if (0 == this->grille.at(this->k-1).at(this->k-1).getval()) {
		//pour c[1,1] > c[n,n];
		borne1 = (0 == this->grille.at(0).at(0).getval()) ? *max_element(this->grille.at(0).at(0).getrestant()->begin(),this->grille.at(0).at(0).getrestant()->end()) : this->grille.at(0).at(0).getval();
		//domaine de c[n,n]
		reste = set<int>(* this->grille.at(this->k-1).at(this->k-1).getrestant());

		//filtrage
		compt = 0; //compte le nombre de valeur enleve

		for(set<int>::iterator it = reste.begin() ; it!=reste.end() ; ++it) {
			if ( (*it >= borne1)){
				this->grille.at(this->k-1).at(this->k-1).enlever(*it);
				++compt;
			}
		}
		if (0 != compt) {this->filtrerligne(this->k-1); this->filtrercolonne(this->k-1);}
	}

	//filtrage de c[n,1]
	if (0 == this->grille.at(this->k-1).at(0).getval()) {
		//pour c[1,n] > c[n,1]
		borne1 = (0 == this->grille.at(0).at(this->k-1).getval()) ? *max_element(this->grille.at(0).at(this->k-1).getrestant()->begin(),this->grille.at(0).at(this->k-1).getrestant()->end()) : this->grille.at(0).at(this->k-1).getval();
		//domaine de c[n,n]
		reste = set<int>(* this->grille.at(this->k-1).at(0).getrestant());

		//filtrage
		compt = 0; //compte le nombre de valeur enleve
		for(set<int>::iterator it = reste.begin() ; it!=reste.end() ; ++it) {
			if ( (*it >= borne1)){
				this->grille.at(this->k-1).at(0).enlever(*it);
				++compt;
			}
		}
		if (0 != compt) {this->filtrerligne(this->k-1); this->filtrercolonne(0);}
	}

}

const set<int> * const carre::getrestant(const int i, const int j) {
	return this->grille.at(i).at(j).getrestant();
}

void carre::annuler() {
	this->grille.at(this->historique.back().i).at(this->historique.back().j).enleverval();
	
	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<this->k; ++j) {
			this->grille.at(i).at(j).annule();
		}
	}

	this->historique.pop_back();
}

bool carre::fini() const {
	bool res = true;
	int i = 0;
	int j;
	while ( (res) && (i<k) ) {
		j = 0;
		while ( (res) && (j<k) ) {
			res = res && (0 != this->grille.at(i).at(j).getval());
			++j;
		}
		++i;
	}
	return res;
}

bool carre::culdesac() const {
	bool res = false;
	int i = 0;
	int j;
	while ( (! res) && (i<k) ) {
		j = 0;
		while ( (! res) && (j<k) ) {
			res = res || ((this->grille.at(i).at(j).getrestant()->empty()) && (0 == this->grille.at(i).at(j).getval()));
			++j;
		}
		++i;
	}

	return res;
}

int carre::suml(const int i) const {
	int res = 0;
	for(int j = 0; j<k; ++j) {
		res += this->grille.at(i).at(j).getval();
	}
	return res;
}

int carre::sumc(const int j) const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(j).getval();
	}
	return res;
}

int carre::sumd1() const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(i).getval();
	}
	return res;
}

int carre::sumd2() const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(this->k - i -1).getval();
	}
	return res;
}

bool carre::allassignligne(const int i) const {
	bool res = true;
	int j = 0;
	while ( (j<k) && res ) {
		res = res && (0 != this->grille.at(i).at(j).getval());
		++j;
	}
	return res;
}

bool carre::allasigncolone(const int j) const {
	bool res = true;
	int i = 0;
	while ( (i<k) && res ) {
		res = res && (0 != this->grille.at(i).at(j).getval());
		++i;
	}
	return res;
}

bool carre::allassignd1 () const {
	bool res = true;
	int i = 0;
	while ( (i<k) && res ) {
		res = res && (0 != this->grille.at(i).at(i).getval());
		++i;
	}
	return res;
}

bool carre::allassignd2() const {
	bool res = true;
	int i = 0;
	while ( (i<k) && res ) {
		res = res && (0 != this->grille.at(i).at(this->k - i).getval());
		++i;
	}
	return res;
}