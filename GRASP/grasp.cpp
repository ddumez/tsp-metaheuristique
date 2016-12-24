#include <cstdlib>
#include <stdlib.h>
#include <math.h>
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

//jamais utilisé depuis reacgrasp
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
	int nogood = 0; // Nombre de tours consécutifs sans amélioration de la solution
	int * sol; double tmp; // diverses variables de calcul
	
	int *pathRel; double tmpPath; bool improved;
	
	int * best = new int[dist->getN()]; construireSolNNH(best, dist); //initialisation du best
	//amelioration de la solution
	/*best = deuxoptconverge(best, dist);
	best = troisoptconverge(best, dist);
	best = deuxoptPPDconverge(best, dist);
	best = troisoptPPDconverge(best, dist);
	*/best = vnd(best, dist); //choix de celle ci car elle plutot rapide et de bonne qualite
	/*best = vndPPD(best, dist);
	best = vns(best, dist);
	best = vnsPPD(best, dist);*/

	int k; //compteur de boucle des diverse boucles internes
	int compt = 0; //compte le nombre de tour de grasp
	double p[20]; for (k = 0; k<20; ++k){p[k] = k*0.05 + 0.05;} //probabilite de chaque alpha_k = 1 - k*0.05 -0.01
	double q[20]; double sumq; //pour le calcul iteratif des p
	double zbest = calculerLongueurCircuitSol(best, dist); //initialisation de zbest
	double zworst = zbest; //pour l'instant seule une solution est disponible
	double avg[20]; for (k = 0; k<20; ++k){avg[k] = zbest;} //initialisation des moyennes
	double choix; //valeur aleatoire du choix de la valeur de alpha
/*
	//variable pour l'arret probabiliste
	double sumXk = 0; //somme des valeur de la taille des solutions
	double sumXk2 = 0; //somme des valeur de la taille des solutions au carre
	double mu, sigma2; //estimateur des moments de la loi normale
*/
	do {
		sol = new int[dist->getN()];
		
		//choix de la valeur de alpha
		choix = (double)((double)rand() / (double)RAND_MAX);
		k = 0; while(p[k] <= choix) {++k;}

		//construction pseudo aleatoire de la solution
		construireSolNNHrand(sol, dist, 1 - k*0.05 - 0.01); //on laisse toujour une part d'aleatoire car la solution constuite a deja ete explore

		//amelioration de la solution
		sol = deuxoptconverge(sol, dist);
		//~ sol = troisoptconverge(sol, dist);
		//~ sol = deuxoptPPDconverge(sol, dist);
		//~ sol = troisoptPPDconverge(sol, dist);
		//~ sol = vnd(sol, dist);
		//~ sol = vndPPD(sol, dist);
		//~ sol = vns(sol, dist);
		//~ sol = vnsPPD(sol, dist);
		
		tmp = calculerLongueurCircuitSol(sol, dist);
		
		++compt; //compteur du nombre de tours
		//mise a jour de best et zbest
		if (tmp + 0.000001 < zbest) { //ajout d'un epsilon pour eviter les imprecisions de calcul
			pathRel = pathRelinkingSelect(sol, best, dist, &improved);
		//	pathRel = pathRelinking(sol, best, dist, &improved);
			if (tmp < calculerLongueurCircuitSol(pathRel, dist)) {
				cout << "PATH REL EST MEILLEUR" << endl;
				tmpPath = calculerLongueurCircuitSol(pathRel, dist);
				delete(best);
				delete(sol);
				zbest = tmpPath;
				best = pathRel;
				//~ nogood = 0;
			} else {
				cout << "SOL EST MEILLEUR" << endl;
				delete(best);
				delete(pathRel);
				zbest = tmp;
				best = sol;
				nogood = 0;
			}
		} else {
			pathRel = pathRelinkingSelect(best, sol, dist, &improved);
		//	pathRel = pathRelinking(sol, best, dist, &improved);
			if (improved) {
				cout << "PATH REL EST MEILLEUR" << endl;
				tmpPath = calculerLongueurCircuitSol(pathRel, dist);
				delete(best);
				delete(sol);
				zbest = tmpPath;
				best = pathRel;
				//~ nogood = 0;
			} else {
				delete(sol);
				delete(pathRel);
				++nogood;
			}
		}

/*
		//mise a jour des estimateur
		sumXk += tmp;
		sumXk2 += tmp*tmp;
		mu = (double)(sumXk / (double)(compt));
		sigma2 = (sumXk2 / (double)(compt-1)) - ( (sumXk * sumXk) / (double)(compt*(compt-1)));
*/
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
	//} while( (compt == 1) || ( tmp > mu - sqrt(sigma2)*2.06 ) ); //la proba d'avoir une meilleure solution est trop faible 2% ->2.06 ; 5% ->1.65 ; 7% ->1.46 ; 10% ->1.29

	return best;
}
