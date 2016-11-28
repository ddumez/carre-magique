include "alldifferent.mzn";

%variable
par int: n = 9;
array[1..n,1..n] of var 0..(n*n): c; %case du carre

%contraintes
constraint alldifferent(i,j in 1..n)(c[i,j]);
constraint sum(i in 1..n)(2*c[i,i]) = (n*(n*n+1)); %valeur des diagonales
constraint sum(i in 1..n)(2*c[i,n-i+1]) = (n*(n*n+1)); %valeur de l'autre diagonale
constraint forall(i in 1..n) (sum(j in 1..n)(2*c[i,j]) = (n*(n*n+1))); %valeur des lignes
constraint forall(i in 1..n) (sum(j in 1..n)(2*c[j,i]) = (n*(n*n+1))); %valeur des colones

%trouve sur http://www.hakank.org/minizinc/
constraint c[1,1] > c[1,n]; %cassage de symetrie droite/gauche
constraint c[1,n] > c[n,1]; %cassage de symetrie haut/bas
constraint c[1,1] > c[n,n]; %cassage de symetrie diagonale 1

%solve
solve::int_search([c[i,j] | i,j in 1..n], dom_w_deg, indomain_median, complete) satisfy;

%output
output[show(c)];