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

const set<int> * const carre::getrestant(const int i, const int j) {
	return this->grille.at(i).at(j).getrestant();
}

void carre::annuler() {
	this->grille.at(this->historique.back().i).at(this->historique.back().j).enleverval();
	
	for(int i = 0; i<this->k; ++i) {
		for(int j = 0; j<this->k; ++j) {
cout<<"annule ("<<i<<","<<j<<") : ";
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
	if (res) {cout<<"(erreur sur ("<<--i<<","<<--j<<") ) ";}
	return res;
}

int carre::suml(const int i) const {
	int res = 0;
	for(int j = 0; j<k; ++j) {
		res += this->grille.at(i).at(j).getval();
	}
if (res > this->nombremagique()) {cout<<"(erreur soml = "<<res<<") ";}
	return res;
}

int carre::sumc(const int j) const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(j).getval();
	}
if (res > this->nombremagique()) {cout<<"(erreur somc = "<<res<<") ";}
	return res;
}

int carre::sumd1() const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(i).getval();
	}
if (res > this->nombremagique()) {cout<<"(erreur somd1 = "<<res<<") ";}
	return res;
}

int carre::sumd2() const {
	int res = 0;
	for(int i = 0; i<k; ++i) {
		res += this->grille.at(i).at(this->k - i -1).getval();
	}
if (res > this->nombremagique()) {cout<<"(erreur somd2 = "<<res<<") ";}
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