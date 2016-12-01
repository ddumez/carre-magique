#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#include "grille.hpp"
#include "complet.hpp"

carre * resolC(int k) {
	//variable
		carre * sol = new carre(k);
		set<variable *> afaire;
	//début
		//initialisation de la file de priorite
		for(int i=0; i<sol->gettaille(); ++i) {
			for(int j=0; j<sol->gettaille(); ++j) {
				afaire.insert(sol->getvar(i,j));
			}
		}
		//prefiltrage
		if (1 != k) sol->filtrersymetrie();

		//lancement de la recherche
		cout<<"trouvé : "<< ( (resolCRec(sol, &afaire)) ? "oui" : "non" ) <<endl;
	//fin
	return sol;
}

bool resolCRec(carre * sol, set<variable *> * afaire) {
	if (afaire->empty()) { //cas de base
		return true; //on a plus de variable a traite donc elles ont toute une valeur
	} else {
		//variable
		variable * courant = *min_element(afaire->begin(),afaire->end(),mycomparison());
		set<int> restant (* courant->getrestant());
		const int nbmagique = sol->nombremagique();
		bool flag;
		const int i = courant->getposi();
		const int j = courant->getposj();
		int it;
		afaire->erase(courant); //on enleve courant des variables a traiter

		//debut
			while(! restant.empty() ) {
				it = *min_element(restant.begin(),restant.end(),compint(  (int)(sol->gettaille() * sol->gettaille() / 2)  ));
				restant.erase(it);

				sol->choisir(it, i, j);

				//la solution reste admissible
				sol->filtrerligne(i);
				sol->filtrercolonne(j);
				sol->filtrerdiag1();
				sol->filtrerdiag2();
				sol->filtrersymetrie();

				if ( !sol->culdesac(afaire) ){
					//on passe à la variable suivante
					flag = resolCRec(sol, afaire);
				} else {
					flag = false;
				}
			
				if (! flag) {
					sol->annuler();
				} else {
					if ((sol->suml(i) == nbmagique) && (sol->sumc(j) == nbmagique) && (sol->sumd1() == nbmagique) && (sol->sumd2() == nbmagique)) {
						return true;
					} else {
						sol->annuler();
					}
				}
			}
		//fin
		afaire->insert(courant); //on n'a pas reussis a la fixer donc il faudra la re-considerer
		return false;
	}
}