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

#define NBTEST 30

int main(int argc, char *argv[]) {
	//variable
		int k; //taille du carré magique
		//carre * soluceC; //solution trouvé par l'algorithme complet
		grille * soluceI; //solution trouvé par l'algorithme incomplet
		clock_t tc, ti, toti, max, min;
	//début
		//entrées
		//cout<<"taille du carre magique : ";
		//cin>>k;
		k = atoi(argv[1]);
		cout<<"taille : "<<k<<endl;


		//calculs
		/*tc = clock();
		soluceC = resolC(k);
		tc = clock() - tc;
		*/ti = clock();
		soluceI = resolI(k);
		ti = clock() - ti;

		//sorties
		/*cout<<"temps de calcul de l'algo complet : "<<(double)((double)tc/(double)(CLOCKS_PER_SEC))<<endl;
		cout<<"solution trouvé par l'algorithme complet :"<<endl;
		soluceC->affiche();
		*/
		cout<<"temps de calcul de l'algo incomplet : "<<(double)((double)ti/(double)(CLOCKS_PER_SEC))<<endl;
		cout<<"solution trouvé par l'algorithme incomplet :"<<endl;
		soluceI->affiche();

		
		toti = 0;
		min = 60 *30 * CLOCKS_PER_SEC; max = 0; //on suppose que 30 minutes est un majorant large
		for(int i = 0; i<NBTEST; ++i) {
			ti = clock();
			delete(resolI(k));
			ti = clock() - ti;
			toti += ti;
			if (ti < min) {min = ti;}
			if (ti > max) {max = ti;}
		}
		cout<<"temps moyen de calcul ("<<NBTEST<<" iterations) pour l'algo incomplet : "<<(double)((double)toti/(double)(CLOCKS_PER_SEC*NBTEST))<<endl;
		cout<<"temps min de calcul : "<<(double)((double)min/(double)(CLOCKS_PER_SEC))<<endl;
		cout<<"temps max de calcul : "<<(double)((double)max/(double)(CLOCKS_PER_SEC))<<endl;
		
	//fin
	//delete(soluceC);
	delete(soluceI);
	cout<<"\n\n"<<endl;
return 0;
}
