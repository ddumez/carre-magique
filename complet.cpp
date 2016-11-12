#include <iostream>
using namespace std;

#include "grille.hpp"
#include "complet.hpp"

carre * resolC(int k) {
	//variable
		carre * sol = new carre(k);
	//début
		cout<<"trouvé : "<<resolCRec(sol, 0, 0)<<endl;
	//fin
	return sol;
}

bool resolCRec(carre * sol, const int i, const int j) {
cout<<"\n resolCRec : i = "<<i<<" j = "<<j<<endl;
sol->affiche();
cout<<"domaine restant : ";
for(set<int>::iterator it = sol->getrestant(i,j)->begin() ; it!=sol->getrestant(i,j)->end() ; ++it) {
	cout<<*it<<" ";
}
cout<<"\n"<<endl;


	if (sol->gettaille() == i) { //cas de base
		return true;
	} else {
		//variable
		const set<int> restant (* sol->getrestant(i,j));
		const int nbmagique = sol->nombremagique();
		bool flag;
		const int nexti = i + (int)((j+1)/sol->gettaille());
		const int nextj = (j+1) % sol->gettaille();


		//debut
			for(set<int>::iterator it = restant.begin() ; it!=restant.end() ; ++it) {
				sol->choisir(*it, i, j);
cout<<"domaine restant : ";
for(set<int>::iterator it2 = restant.begin() ; it2!=restant.end() ; ++it2) {
	cout<<*it2<<" ";
}
cout<<" : ";
				if ((sol->suml(i) <= nbmagique) && (sol->sumc(j) <= nbmagique) && (sol->sumd1() <= nbmagique) && (sol->sumd2() <= nbmagique) && !sol->culdesac()) {
					//la solution reste admissible
					//on passe à la variable suivante
cout<<"valeur choisie : "<<*it<<" en ("<<i<<","<<j<<")"<<endl;					
					flag = resolCRec(sol, nexti, nextj);
				} else {
cout<<"valeur abandonne : "<<*it<<" en ("<<i<<","<<j<<") :"<<endl;
					flag = false;
				}
				
				if (! flag) {
					sol->annuler();
				} else {
cout<<"trouve"<<endl;
					return true;
				}
			}
		//fin
cout<<"retour"<<endl;
		return false;
	}
}