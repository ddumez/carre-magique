#include <iostream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

#include "grille.hpp"
#include "complet.hpp"

carre * resolC(int k) {
	//variable
		carre * sol = new carre(k);
		priority_queue_variable afaire;
	//début
		//initialisation de la file de priorite
		for(int i=0; i<sol->gettaille(); ++i) {
			for(int j=0; j<sol->gettaille(); ++j) {
				afaire.push(sol->getvar(i,j));
			}
		}
		//prefiltrage
		if (1 != k) sol->filtrersymetrie();

for(int i = 0; i<sol->gettaille(); ++i) {
	for(int j = 0; j<sol->gettaille(); ++j) {
		cout<<i<<" ; "<<j<<" : ";
		for (int parc : * sol->getvar(i,j)->getrestant()) {
			cout<<parc<<" ";
		}
		cout<<endl;
	}
}
cout<<"\n"<<endl;

		//lancement de la recherche
		cout<<"trouvé : "<<resolCRec(sol, &afaire)<<endl;
	//fin
	return sol;
}

bool resolCRec(carre * sol, priority_queue_variable * afaire) {
	if (afaire->empty()) { //cas de base
		return true; //on a plus de variable a traite donc elles ont toute une valeur
	} else {
		//variable
		variable * courant = afaire->top();
		const set<int> restant (* courant->getrestant());
		const int nbmagique = sol->nombremagique();
		bool flag;
		const int i = courant->getposi();
		const int j = courant->getposj();
		afaire->pop(); //on enleve courant des variables a traiter

		//debut
			for(set<int>::iterator it = restant.begin() ; it!=restant.end() ; ++it) {
				sol->choisir(*it, i, j);
cout<<*it<<" choisis en "<<i<<" "<<j<<endl;
				if ((sol->suml(i) <= nbmagique) && (sol->sumc(j) <= nbmagique) && (sol->sumd1() <= nbmagique) && (sol->sumd2() <= nbmagique)) {
					//la solution reste admissible
					sol->filtrerligne(i);
					sol->filtrercolonne(j);
					sol->filtrersymetrie();

for(int ii = 0; ii<sol->gettaille(); ++ii) {
	for(int jj = 0; jj<sol->gettaille(); ++jj) {
		cout<<ii<<" ; "<<jj<<" : ";
		for (int parc : * sol->getvar(ii,jj)->getrestant()) {
			cout<<parc<<" ";
		}
		cout<<endl;
	}
}
sol->affiche();
cout<<"\n"<<endl;

					if ( !sol->culdesac() ){
						//on passe à la variable suivante
						flag = resolCRec(sol, afaire);
					} else {
						flag = false;
					}
				} else {
					flag = false;
				}
				
				if (! flag) {
					
					sol->annuler();
cout<<"annule"<<endl;
for(int ii = 0; ii<sol->gettaille(); ++ii) {
	for(int jj = 0; jj<sol->gettaille(); ++jj) {
		cout<<ii<<" ; "<<jj<<" : ";
		for (int parc : * sol->getvar(ii,jj)->getrestant()) {
			cout<<parc<<" ";
		}
		cout<<endl;
	}
}
cout<<"\n"<<endl;

				} else {
					if ((sol->suml(i) == nbmagique) && (sol->sumc(j) == nbmagique) && (sol->sumd1() == nbmagique) && (sol->sumd2() == nbmagique)) {
						return true;
					} else {
						sol->annuler();

cout<<"mauvaise solution"<<endl;
for(int ii = 0; ii<sol->gettaille(); ++ii) {
	for(int jj = 0; jj<sol->gettaille(); ++jj) {
		cout<<ii<<" ; "<<jj<<" : ";
		for (int parc : * sol->getvar(ii,jj)->getrestant()) {
			cout<<parc<<" ";
		}
		cout<<endl;
	}
}
cout<<"\n"<<endl;

					}
				}
			}
		//fin
		afaire->push(courant); //on n'a pas reussis a la fixer donc il faudra la re-considerer
		return false;
	}
}