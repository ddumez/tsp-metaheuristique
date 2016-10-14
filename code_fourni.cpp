#include <iostream>

#include "code_fourni.hpp"
#include "./Distancier/Distancier.hpp"

using namespace std;

void construireSolNNH(int * sol, const Distancier * const dist) {
	int i,j;
	int n = dist->getN();
	int min, jmin;
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

int calculerLongueurCircuitSol(const int * sol, const Distancier * const dist) {
	int  zSol = 0; // longueur du circuit hamiltonien

	// les distances i a j depuis ville depart
	for (int k = dist->getN(); k > 0; --k) {
		zSol += dist->getDistance( sol[k] , sol[k-1]);
	}

	// dernier segments qui revient a la ville de depart à la ville d'arrivé
	zSol += dist->getDistance( sol[dist->getN()-1] , sol[0]);

	return zSol;
}

void ameliorerSol2OPT(int * sol, const Distancier * const dist, bool *improved) {
	int i,j,k,tmp;
	int iD, iF, jD, jF;
	int d1, d2;
	const int taille = dist->getN();

	*improved = false;

	for (i=0; i< taille; i++) {
		for (j=0; j< taille-3; j++) {

		  iD=i%taille;
		  iF=(i+1)%taille;
		  jD=(i+j+2) % taille;
		  jF=(i+j+3) % taille;
		        
		  d1 = dist->getDistance( sol[iD] , sol[iF] ) + dist->getDistance( sol[jD] , sol[jF] );
		  d2 = dist->getDistance( sol[iD] , sol[jD] ) + dist->getDistance( sol[iF] , sol[jF] );

			if (d1>d2) {
				// amelioration detectee
				*improved = true; // notifie que une amelioration est detectee
				       
				//application du changement 
				tmp = sol[iF];
				sol[iF] = sol[jD];
				sol[jD] = tmp;
				        
				// Inversion des segments du chemin entre les 2 segments traites
				if (iD < jD) {
				    for (k=1; k<=(jD-(iD+2))/2; k++) {
					    tmp = sol[iD+1+k];
					    sol[iD+1+k] = sol[jD-k];
					    sol[jD-k] = tmp;
				    }
				} else {
					for (k=1; k<=(taille-(iD-jD)-2)/2; k++) {
						tmp = sol[(iD+1+k)%taille];
						sol[(iD+1+k)%taille] = sol[(taille+jD-k)%taille];
						sol[(taille+jD-k)%taille] = tmp;
					}
				}
			} // Fin traitement suite amelioration detectee
		}
	}
}

void afficheSol(const int * const sol, const Distancier * const dist) {
	for (int k=0; k<dist->getN(); ++k) {
		cout<<sol[k]<<" : ";
		dist->afficheVillei(sol[k]);		
		cout<<" - ";
	}
	
	// dernier segments qui revient a la ville de depart
	cout<<sol[0]<<" : ";
	dist->afficheVillei(0);

	//longueur totale
	cout<<"\n longueur : "<<calculerLongueurCircuitSol(sol, dist)<<endl;

}


