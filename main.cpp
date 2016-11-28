/* DUMEZ dorian */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <vector>

#include "grille.hpp"
#include "variable.hpp"
#include "carre.hpp"
#include "complet.hpp"
#include "incomplet.hpp"

using namespace std;

int main() {
	//variable
		int k; //taille du carré magique
		carre * soluceC; //solution trouvé par l'algorithme complet
		grille * soluceI; //solution trouvé par l'algorithme incomplet
		clock_t tc, ti, toti;
	//début
		//entrées
		cout<<"taille du carre magique : ";
		cin>>k;

		//calculs
		tc = clock();
		soluceC = resolC(k);
		tc = clock() - tc;
		ti = clock();
		soluceI = resolI(k);
		ti = clock() - ti;

		//sorties
		cout<<"temps de calcul de l'algo complet : "<<(double)((double)tc/(double)(CLOCKS_PER_SEC))<<endl;
		cout<<"solution trouvé par l'algorithme complet :"<<endl;
		soluceC->affiche();
		
		cout<<"temps de calcul de l'algo incomplet : "<<(double)((double)ti/(double)(CLOCKS_PER_SEC))<<endl;
		cout<<"solution trouvé par l'algorithme incomplet :"<<endl;
		soluceI->affiche();

		/*
		toti = 0;
		for(int i = 0; i<10; ++i) {
			ti = clock();
			delete(resolI(k));
			ti = clock() - ti;
			toti += ti;
		}
		cout<<"temps moyen de calcul (10 iterations) pour l'algo incomplet : "<<(double)((double)toti/(double)(CLOCKS_PER_SEC*10))<<endl;
		*/
	//fin
	delete(soluceC);
	delete(soluceI);
return 0;
}
