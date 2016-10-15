#include "variable.hpp"
#include "carre.hpp"

#include <iostream>
#include <vector>
#include <set>

using namespace std;

carre::carre(const int k) {
	this->k = k;
	this->historique.resize(0);

	this->grille.resize(k);
	for(int i = 0; i<k; ++i) {
		this->grille.at(i).resize(k);
		for(int j = 0; j<k; ++j) {
			this->grille.at(i).at(j).initialise(k);
		}
	}
}

carre::~carre() {}

void carre::affiche() const {
	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<this->k; ++j) {
			cout<<this->grille.at(i).at(j).getval()<<" ";
		}
		cout<<"\n";
	}
}

void carre::choisir(const int val, const int i, const int j) {
	this->grille.at(i).at(j).choix(val);
	for(int parci = 0; parci<this->k; ++parci) {
		for(int parcj = 0; parcj<this->k; ++parcj) {
			if ( (i != parci) && (j != parcj)) {
				this->grille.at(i).at(j).nouveauchoix(val);
			}
		}
	}
	couple nouv; nouv.i = i; nouv.j = j;
	this->historique.push_back(nouv);
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
	bool res = true;
	int i = 0;
	int j;
	while ( (res) && (i<k) ) {
		j = 0;
		while ( (res) && (j<k) ) {
			res = res && ((! this->grille.at(i).at(j).getrestant()->empty()) || (0 != this->grille.at(i).at(j).getval()));
			++j;
		}
		++i;
	}
	return res;
}