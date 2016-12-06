#include <cstdlib>
#include <stdlib.h>
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

int * reacgrasp(const Distancier * const dist) {
	int nogood = 0;
	int * sol; int tmp;

	int * best = new int[dist->getN()]; construireSolNNH(best, dist); //initialisation du best
	//amelioration de la solution
	/*sol = deuxoptconverge(sol, dist);
	sol = troisoptconverge(sol, dist);
	sol = deuxoptPPDconverge(sol, dist);
	sol = troisoptPPDconverge(sol, dist);
	*/best = vnd(best, dist);/*
	sol = vndPPD(sol, dist);
	sol = vns(sol, dist);
	sol = vnsPPD(sol, dist);*/

	int k;
	int compt = 0; //compte le nombre de tour de grasp
	double p[20]; for (k = 0; k<20; ++k){p[k] = k*0.05 + 0.05;} //probabilite de chaque alpha_k = 1 - k*0.05 -0.01
	double q[20]; double sumq;
	double zbest = calculerLongueurCircuitSol(best, dist); //initialisation de zbest
	double zworst = zbest;
	double avg[20]; for (k = 0; k<20; ++k){avg[k] = zbest;} //initialisation des moyennes
	double choix; //valeur aleatoire du choix de la valeur de alpha

	do {
		sol = new int[dist->getN()];
		
		//choix de la valeur de alpha
		choix = (double)((double)rand() / (double)RAND_MAX);
		k = 0; while(p[k] <= choix) {++k;}

		//construction pseudo aleatoire de la solution
		construireSolNNHrand(sol, dist, 1 - k*0.05 - 0.01); //on laisse toujour une par d'aleatoire car la solution constuite a deja ete explore

		//amelioration de la solution
		/*sol = deuxoptconverge(sol, dist);
		sol = troisoptconverge(sol, dist);
		sol = deuxoptPPDconverge(sol, dist);
		sol = troisoptPPDconverge(sol, dist);
		*/sol = vnd(sol, dist);/*
		sol = vndPPD(sol, dist);
		sol = vns(sol, dist);
		sol = vnsPPD(sol, dist);*/
		
		++compt;

		//mise a jour de best et zbest
		if ( (tmp = calculerLongueurCircuitSol(sol, dist)) < zbest) {
			delete(best);
			zbest = tmp;
			best = sol;
			nogood = 0;
		} else {
			delete(sol);
			++nogood;
		}

		//mise a jour de zworst
		if (tmp > zworst) {zworst = tmp;}

		//mise a jour de avg
		avg[k] = (double)((double)(avg[k] * (compt-1)) / (double)compt) + (double)((double)tmp / (double)compt);

		//calcul des nouvelles probabilites
		for (k = 0; k<20; ++k) {q[k] = (double)((double)(avg[k] - zworst) / (double)(zbest - zworst));}
		sumq = 0; for(k = 0; k<20; ++k) {sumq += q[k];}
		p[0] = q[0] / sumq;
		for(k = 1; k<20; ++k) {p[k] = p[k-1] + (q[k] / sumq);}

	} while (nogood < dist->getN()/5); //critère d'arret

	return best;
}