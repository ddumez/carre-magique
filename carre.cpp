#include "variable.hpp"
#include "carre.hpp"

#include <vector>
#include <set>


using namespace std;

carre::carre(const int k) {
	this->k = k;

	this->grille.resize(k);
	for(int i = 0; i<k; ++i) {
		this->grille.at(i).resize(k);
		for(int j = 0; j<k; ++j) {
			this->grille.at(i).at(j).initialise(k);
		}
	}
}