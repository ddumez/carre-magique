#include "variable.hpp"

#include <vector>
#include <set>


using namespace std;

variable::variable() {}

variable::variable(const int k) {
	this->val = 0;
	
	for(int i = 1; i<=k*k; ++i) {
		this->restant.insert(i);
	}
}

variable::~variable() {}

void variable::initialise(const int k) {
	this->val = 0;
	
	for(int i = 1; i<=k*k; ++i) {
		this->restant.insert(i);
	}	
}

void variable::choix(const int val) {
	this->val = val;
	set<int> nouv;

	for(set<int>::iterator it = restant.begin() ; it!=restant.end() ; ++it) {
		if (val != *it) {
			this->restant.erase(*it);
			nouv.insert(*it);
		}
	}
	this->historique.push_back(nouv);
}

void variable::nouveauChoix(const int val) {
	set<int> nouv;
	if(1 == this->restant.erase(val)) {
		nouv.insert(val);
	}
	this->historique.push_back(nouv);

}

void variable::enlever(const int val) {
	if(1 == this->restant.erase(val)) {
		this->historique.back().insert(val);
	}
}

bool variable::estVide() const {
	return (0 == this->restant.size());
}

bool variable::resteUn() const {
	return ((0!= this->val) || (1 == this->restant.size()));
}

int variable::getval() const {
	return this->val;
}

set<int> const * variable::getrestant() const {
	return &(this->restant) ;
}