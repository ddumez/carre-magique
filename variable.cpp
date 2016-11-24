#include <iostream>

#include "variable.hpp"

#include <vector>
#include <set>


using namespace std;

variable::variable() {}

variable::variable(const int k, const int i, const int j) {
	this->initialise(k, i, j);
}

variable::~variable() {}

void variable::initialise(const int k, const int i, const int j) {
	this->val = 0;
	this->posi = i;
	this->posj = j;

	for(int i = 1; i<=k*k; ++i) {
		this->restant.insert(i);
	}
}

int variable::getposi() {return this->posi;}

int variable::getposj() {return this->posj;}

void variable::choix(const int val) {
	this->val = val;
	set<int> nouv;

	for(set<int>::iterator it = restant.begin() ; it!=restant.end() ; ++it) {
		nouv.insert(*it); //on copie les valeurs restantes (sauf celle utilise) pour l'historique
		this->restant.erase(*it); //on vide l'ensemble des valeurs possible restante
	}
	this->historique.push_back(nouv);
}

void variable::nouveauchoix(const int val) {
	set<int> nouv;
	if(1 == this->restant.erase(val)) { //si val est present dans restant l'enleve et retourne 1 sinon ne fait rien et retourne 0
		nouv.insert(val);
	}
	this->historique.push_back(nouv);
}

void variable::enlever(const int val) {
	if(1 == this->restant.erase(val)) {
		this->historique.back().insert(val);
	}
}

bool variable::estvide() const {
	return (0 == this->restant.size());
}

bool variable::resteun() const {
	return ((0 != this->val) || (1 == this->restant.size()));
}

int variable::getval() const {
	return this->val;
}

const set<int> * const variable::getrestant() const {
	return &(this->restant);
}

void variable::enleverval() {
	this->val = 0;
}

void variable::annule() {
	//on remet toute les variables filtre par le dernier assignement dans restant
	for(set<int>::iterator it = historique.back().begin() ; it!=historique.back().end() ; ++it) {
		this->restant.insert(*it);
	}
	this->historique.pop_back();
}