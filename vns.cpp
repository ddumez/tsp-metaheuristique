#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "vns.hpp"

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"
#include "vnd.hpp"

using namespace std;

int * vns(int * sol, const Distancier * const dist) {
	//variables
		bool improved = false;
		int k = 1;
		bool stop = false;
		int * voisin;
		double zsol, zvoisin;

		zsol = calculerLongueurCircuitSol(sol, dist);
	//debut
		do {
			//choix du voisinage utilise
			switch(k) {
				case 1:
						voisin = voisindeuxopt(sol, dist);
						if ( (deuxoptconverge(voisin, dist)) && ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol) ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							improved = false;
						}
					break;
				case 2:
						voisin = voisintroisopt(sol, dist);
						if ( (troisoptconverge(voisin, dist)) && ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol) ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							improved = false;
						}
					break;
				default :
						improved = false;
					break;
			}

			//action suivante
			if ((!improved) && (k>2)) {
				stop = true; //on a pas amélioré on a aucun autre voisinage
			} else if (!improved) {
				++k; //on a pas amélioré mais il nous reste des voisinage
			} else {
				k = 1;	//on a amélioré
			}

		} while (! stop);
	//fin

	return sol;
}

int * voisindeuxopt(const int * const sol, const Distancier * const dist) {
	srand (time(NULL));
	const int taille = dist->getN();
	int i = rand() % taille;
	int j = rand() % (taille -3);

	int iD = i % taille;
	int iF = (i+1) % taille;
	int jD = (i+j+2) % taille;
	int jF = (i+j+3) % taille;

	int * res = new int[dist->getN()];

	for(int k = 0; k<taille; ++k) {res[k] = sol[k];} //recopie de la solution

	//application du changement 
	int tmp = res[iF];
	res[iF] = res[jD];
	res[jD] = tmp;
	        
	// Inversion des segments du chemin entre les 2 segments traites
	if (iD < jD) {
	    for (int k=1; k<=(jD-(iD+2))/2; k++) {
		    tmp = res[iD+1+k];
		    res[iD+1+k] = res[jD-k];
		    res[jD-k] = tmp;
	    }
	} else {
		for (int k=1; k<=(taille-(iD-jD)-2)/2; k++) {
			tmp = res[(iD+1+k)%taille];
			res[(iD+1+k)%taille] = res[(taille+jD-k)%taille];
			res[(taille+jD-k)%taille] = tmp;
		}
	}

	return res;
}

int * voisintroisopt(const int * const sol, const Distancier * const dist) {
	srand (time(NULL));
	const int taille = dist->getN();
	int tmp1, tmp2, tmp3, tmp4;

	int * res = new int[dist->getN()];

	for(int k = 0; k<taille; ++k) {res[k] = sol[k];} //recopie de la solution

	int i = rand() % taille;
	int j = rand() % (taille -5);
	int n = rand() % (taille -6-j);

	//calcul de iD, iF, jD, jF, nD, nF
	int iD = i % taille;
	int iF = (i+1) % taille;
	int jD = (i+j+2) % taille;
	int jF = (i+j+3) % taille;
	int nD = (i+j+n+4) % taille;
	int nF = (i+j+n+5) % taille; 

	int min = (rand() % 7) + 1; //selection aléatoire du movement de 3opt choisis

	//application du mouvement
	switch(min) {
		case 1: //2-opt
				tmp1 = res[jD];
				res[jD] = res[iF];
				res[iF] = tmp1;
				inverseSens(res, iF, jD, taille);
			break;
		case 2: //2-opt
				tmp1 = res[nD];
				res[nD] = res[jF];
				res[jF] = tmp1;
				inverseSens(res, jF, nD, taille);
			break;
		case 3: //2-opt
				tmp1 = res[iD];
				res[iD] = res[nF];
				res[nF] = tmp1;
				inverseSens(res, nF, iD, taille);
			break;
		case 4:
				tmp1 = res[nD];
				tmp2 = res[iF];
				tmp3 = res[jD];
				tmp4 = res[jF];
				res[iF] = tmp1;
				res[jF] = tmp2;
				res[nD] = tmp3;
				res[jD] = tmp4;
				inverseSens(res, jF, nD, taille);
			break;
		case 5:
				tmp1 = res[iF];
				tmp2 = res[jD];
				tmp3 = res[jF];
				tmp4 = res[nD];
				res[nD] = tmp1;
				res[jF] = tmp2;
				res[iF] = tmp3;
				res[jD] = tmp4;		
				inverseSens(res, iF, jD, taille);
			break;
		case 6:
				tmp1 = res[iD];
				tmp2 = res[iF];
				tmp3 = res[jD];
				tmp4 = res[nF];
				res[jD] = tmp1;
				res[iD] = tmp2;
				res[nF] = tmp3;
				res[iF] = tmp4;		
				inverseSens(res, iF, jD, taille);
			break;
		case 7:
				tmp1 = res[iF];
				tmp2 = res[jD];
				tmp3 = res[jF];
				tmp4 = res[nD];
				res[jF] = tmp1;
				res[nD] = tmp2;
				res[iF] = tmp3;
				res[jD] = tmp4;
			break;
	}

	return res;
}


int * vnsPPD(int * sol, const Distancier * const dist) {
	//variables
		bool improved = false;
		int k = 1;
		bool stop = false;
		int * voisin;
		double zsol, zvoisin;

		zsol = calculerLongueurCircuitSol(sol, dist);
	//debut
		do {
			//choix du voisinage utilise
			switch(k) {
				case 1:
						voisin = voisindeuxopt(sol, dist);
						if ( (deuxoptPPDconverge(voisin, dist)) && ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol) ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							improved = false;
						}			
					break;
				case 2:
						voisin = voisintroisopt(sol, dist);					
						if ( (troisoptPPDconverge(voisin, dist)) && ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol) ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							improved = false;
						}
					break;
				default :
						improved = false;
					break;
			}

			//action suivante
			if ((!improved) && (k>2)) {
				stop = true; //on a pas amélioré on a aucun autre voisinage
			} else if (!improved) {
				++k; //on a pas amélioré mais il nous reste des voisinage
			} else {
				k = 1;	//on a amélioré
			}
		} while (! stop);
	//fin
	return sol;
}