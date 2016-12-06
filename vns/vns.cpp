#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "vns.hpp"

#include "./../Distancier/Distancier.hpp"
#include "./../code_fourni.hpp"
#include "./../3-opt/3opt.hpp"
#include "./../2-opt/2opt.hpp"
#include "./../vnd/vnd.hpp"

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
						voisin = deuxoptconverge(voisin, dist);
						if ( ( zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							delete(voisin);
							improved = false;
						}
					break;
				case 2:
						voisin = voisintroisopt(sol, dist);
						voisin = troisoptconverge(voisin, dist);
						if ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							delete(voisin);
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
	const int taille = dist->getN();
	int i = rand() % taille;
	int j = rand() % (taille -3);

	int iD = i % taille;
	int iF = (i+1) % taille;
	int jD = (i+j+2) % taille;

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
	const int taille = dist->getN();
	int tmp, lim, k;

	int * res = new int[dist->getN()];
	
	int i = rand() % taille;
	int j;
	do {j = rand() % (taille -5);} while (taille-6-j < 1);
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
		case 0:
				//on ne change rien
			break;
		case 1: //2-opt
				for(k = 0; k<taille; ++k) {res[k] = sol[k];} //recopie de la solution
				tmp = res[jD];
				res[jD] = res[iF];
				res[iF] = tmp;
				inverseSens(res, iF, jD, taille);
			break;
		case 2: //2-opt
				for(k = 0; k<taille; ++k) {res[k] = sol[k];} //recopie de la solution
				tmp = res[nD];
				res[nD] = res[jF];
				res[jF] = tmp;
				inverseSens(res, jF, nD, taille);
			break;
		case 3: //2-opt
				for(k = 0; k<taille; ++k) {res[k] = sol[k];} //recopie de la solution
				tmp = res[iD];
				res[iD] = res[nF];
				res[nF] = tmp;
				//inversion manuelle car differente des autres
					//calcul du nombre de case entre iD et nF divise par 2
				if (nF < iD) {
					lim = (iD-nF) / 2;
				} else { //iD > nF
					lim = (dist->getN() - nF + iD) / 2;
				}
					//inversion
				for(k = 1; k<lim; ++k) {
					tmp = res[(iD-k+dist->getN()) % dist->getN()];
					res[(iD-k+dist->getN()) % dist->getN()] = res[(nF+k) % dist->getN()];
					res[(nF+k) % dist->getN()] = tmp;
				}
			break;
		case 4: 
				k = iD; //k est l'indice du tableau res auquel on est rendu

				res[k] = sol[iD]; //le point de depart
				++k;
				
				//on place le segment jF-nD
				res[k % dist->getN()] = sol[jF];
				++k;
				for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
				res[k % dist->getN()] = sol[nD];
				++k;

				
				//on place le segment jD-iF
				res[k % dist->getN()] = sol[jD];
				++k;
				for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp + dist->getN()) % dist->getN() != iF; --tmp ) {
					res[k % dist->getN()] = sol[(tmp + dist->getN()) % dist->getN()];
					++k;							
				}
				res[k % dist->getN()] = sol[iF];
				++k;

				//on place le segment nF-iD, on revien au point de depard
				res[k % dist->getN()] = sol[nF];
				++k;
				for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
			break;
		case 5:
				k = iD; //k est l'indice du tableau res auquel on est rendu

				res[k] = sol[iD]; //le point de depart
				++k;
				
				//on place le segment nD-jF
				res[k % dist->getN()] = sol[nD];
				++k;
				for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
					res[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
					++k;
				}
				res[k % dist->getN()] = sol[jF];
				++k;

				
				//on place le segment iF-jD
				res[k % dist->getN()] = sol[iF];
				++k;
				for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;							
				}
				res[k % dist->getN()] = sol[jD];
				++k;

				//on place le segment nF-iD, on revien au point de depard
				res[k % dist->getN()] = sol[nF];
				++k;
				for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
			break;
		case 6:
				k = iD; //k est l'indice du tableau res auquel on est rendu

				res[k] = sol[iD]; //le point de depart
				++k;
				
				//on place le segment jD-iF
				res[k % dist->getN()] = sol[jD];
				++k;
				for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != iF; --tmp ) {
					res[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
					++k;							
				}
				res[k % dist->getN()] = sol[iF];
				++k;

				//on place le segment nD-jF
				res[k % dist->getN()] = sol[nD];
				++k;
				for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
					res[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
					++k;
				}
				res[k % dist->getN()] = sol[jF];
				++k;

				//on place le segment nF-iD, on revien au point de depard
				res[k % dist->getN()] = sol[nF];
				++k;
				for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
			break;
		case 7:
				k = iD; //k est l'indice du tableau res auquel on est rendu

				res[k] = sol[iD]; //le point de depart
				++k;
				
				//on place le segment jF-nD
				res[k % dist->getN()] = sol[jF];
				++k;
				for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
				res[k % dist->getN()] = sol[nD];
				++k;

				
				//on place le segment iF-jD
				res[k % dist->getN()] = sol[iF];
				++k;
				for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;							
				}
				res[k % dist->getN()] = sol[jD];
				++k;

				//on place le segment nF-iD, on revien au point de depard
				res[k % dist->getN()] = sol[nF];
				++k;
				for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
					res[k % dist->getN()] = sol[tmp % dist->getN()];
					++k;
				}
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
						voisin = deuxoptPPDconverge(voisin, dist);
						if ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							delete(voisin);
							improved = false;
						}			
					break;
				case 2:
						voisin = voisintroisopt(sol, dist);
						voisin = troisoptPPDconverge(voisin, dist);		
						if ( (zvoisin = calculerLongueurCircuitSol(voisin, dist)) < zsol ) {
							zsol = zvoisin;
							delete(sol);
							sol = voisin;
							improved = true;
						} else {
							delete(voisin);
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
