#include <cstdlib>
#include <vector>

#include <iostream>

#include "grasp.hpp"
#include "./../Distancier/Distancier.hpp"
#include "./../Path-Relinking/PathRel.hpp"
#include "./../code_fourni.hpp"
#include "./../2-opt/2opt.hpp"
#include "./../3-opt/3opt.hpp"
#include "./../vnd/vnd.hpp"
#include "./../vns/vns.hpp"

using namespace std;


void construireSolNNHrand(int * sol, const Distancier * const dist, const double a) {
	int i,j;
	const int n = dist->getN();
	double min, max, lim;
	vector<int> * RCL;
	int tmp, jchoix;

	//initialise la solution avec un circuit qui correspond a la permutation identite
	//plus facile pour connaire les villes restantes
	for (i=0; i<n; ++i) {
    	sol[i] = i;
	}

	// calcule la distance min/max de la ville i a toutes les autres villes
	for (i=0; i<n-1; ++i) {
		min = dist->getDistance( sol[i] , sol[i+1] );
		max = dist->getDistance( sol[i] , sol[i+1] );

		for (j=i+2; j<n; ++j) {
		//localise le min/max sur une ligne de la matrice triangulaire superieure
			if (dist->getDistance( sol[i] , sol[j] ) < min) {
				min = dist->getDistance( sol[i] , sol[j] );
			}
			if (dist->getDistance( sol[i] , sol[j] ) > max) {
				max = dist->getDistance( sol[i] , sol[j] );
			}
		}

		//calcul de la limite d'acceptation en fonction du min et du max
		lim = max + a * (min - max); //sens inverse car on est en min

		//recherche de la ville que l'on va mettre
		RCL = new vector<int>();
		for (j=i+1; j<n; ++j) {
			if (dist->getDistance( sol[i] , sol[j] ) <= lim) {
				RCL->push_back(j);
			}
		}
		jchoix = RCL->at( rand() % RCL->size() );

		// echange entre la ville i+1 et jmin dans la solution
		tmp = sol[i+1];
		sol[i+1] = sol[jchoix];
		sol[jchoix] = tmp;

		delete(RCL);
	}	
}

int * grasp(const Distancier * const dist, const double alpha) {
	int nogood = 0;
	int * sol; int tmp;
	int * best = new int[dist->getN()]; construireSolNNH(best, dist); //initialisation du best
	double zbest = calculerLongueurCircuitSol(best, dist); //initialisation de zbest
	bool improved;
	do {
		sol = new int[dist->getN()];
		construireSolNNHrand(sol, dist, alpha);
		sol = vnd(sol, dist);
		
		if ( (tmp = calculerLongueurCircuitSol(sol, dist)) < zbest) {
			delete(best);
			zbest = tmp;
			best = sol;
			nogood = 0;
		} else {
			delete(sol);
			++nogood;
		}

	} while (nogood < dist->getN()/5);

	return best;
}