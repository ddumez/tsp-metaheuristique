#include <iostream>

#include "code_fourni.hpp"
#include "./Distancier/Distancier.hpp"

using namespace std;

void construireSolNNH(int * sol, const Distancier * const dist) {
	int i,j;
	int n = dist->getN();
	double min; 
	int jmin;
	int tmp;

	//initialise la solution avec un circuit qui correspond a la permutation identite
	//plus facile pour connaire les villes restantes
	for (i=0; i<n; ++i) {
    	sol[i] = i;
	}

	// calcule la distance min de la ville i a toutes les autres villes
	for (i=0; i<n-1; ++i) {
		jmin = i+1;
		min = dist->getDistance( sol[i] , sol[i+1] );

		for (j=i+2; j<n; ++j) {
		//localise le min sur une ligne de la matrice triangulaire superieure
			if (dist->getDistance( sol[i] , sol[j] ) < min) {
				min = dist->getDistance( sol[i] , sol[j] );
				jmin = j;
			}
		}

		// echange entre la ville i+1 et jmin dans la solution
		tmp = sol[i+1];
		sol[i+1] = sol[jmin];
		sol[jmin] = tmp;
	}
}

double calculerLongueurCircuitSol(const int * const sol, const Distancier * const dist) {
	double zSol = 0; // longueur du circuit hamiltonien

	// les distances i a j depuis ville depart
	for (int k = dist->getN()-1; k > 0; --k) {
		zSol += dist->getDistance( sol[k] , sol[k-1]);
	}
	
	// dernier segments qui revient a la ville de depart à la ville d'arrivé
	zSol += dist->getDistance( sol[dist->getN()-1] , sol[0]);
	return zSol;
}

void afficheSol(const int * const sol, const Distancier * const dist) {
	for(int i = 0; i<dist->getN(); ++i) {
		dist->afficheVillei(sol[i]);
		cout<<" - ";
	}
	dist->afficheVillei(sol[0]);
	cout<<"\n taille : "<<calculerLongueurCircuitSol(sol, dist)<<endl;
}