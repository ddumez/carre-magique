#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <climits>

using namespace std;

#include "grille.hpp"
#include "incomplet.hpp"

grille * resolI(int k) {
	//variable
		grille * res = new grille(k);
		int repet,scoreprec, score;

		int tours, restart;
		tours = restart = 0;
		
	//début
		scoreprec = INT_MAX;
		//repet = 0; //inutile
		
		while(0 != (score = res->score()) ) {
			
			if (score == scoreprec) { 
				++repet;
			} else {
				repet = 0;
			}
			
			if(1 == repet) {
				repet = 0;
				res->restart();
				score = res->score();
				++restart;
			}
			
			res->perturbe();

			++tours;

			scoreprec = score;

		}

	//fin
cout<<"tours : "<<tours<<" ; restart : "<<restart<<endl;
return res;
}
