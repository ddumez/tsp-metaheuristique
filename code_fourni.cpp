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

void ameliorerSol2OPT(int * sol, const Distancier * const dist, bool *improved) {
	int i,j,k,tmp;
	int iD, iF, jD, jF;
	double d1, d2;
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

void ameliorerSol2OptPPD(int * sol, const Distancier * const dist, bool *improved) {	
	int i,j,k,tmp;
	int iD, iF, jD, jF;
	int d1, d2;
	const int taille = dist->getN();

	double zdiff = 0; 
	int ibest, jbest;

	*improved = false;

	for (i=0; i< taille; i++) {
		for (j=0; j< taille-3; j++) {
			//calcul des indices
			iD=i%taille;
			iF=(i+1)%taille;
			jD=(i+j+2) % taille;
			jF=(i+j+3) % taille;
			        
			//calcul de la distance du nouveau parcours
			d1 = dist->getDistance( sol[iD] , sol[iF] ) + dist->getDistance( sol[jD] , sol[jF] );
			d2 = dist->getDistance( sol[iD] , sol[jD] ) + dist->getDistance( sol[iF] , sol[jF] );

			if (- d1 + d2 < zdiff) {
				// amelioration detectee
				*improved = true; // notifie que une amelioration est detectee
				 
				//on note la modification
				ibest = i; jbest = j;
				zdiff = - d1 + d2; //on calcule le nouveau score relativement a celui de sol
			} // Fin traitement suite amelioration detectee
		}
	}

	//application de la meilleure modification trouvee
	if (*improved) {
double zSol = calculerLongueurCircuitSol(sol, dist);      
		//re-calcul des indices
		iD=ibest %taille;
		iF=(ibest+1)%taille;
		jD=(ibest+jbest+2) % taille;
		jF=(ibest+jbest+3) % taille;
		
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

cout<<"compare : "<<zSol + zdiff<<" et "<<calculerLongueurCircuitSol(sol, dist)<<endl; 
	}
}

void afficheSol(const int * const sol, const Distancier * const dist) {
	for(int i = 0; i<dist->getN(); ++i) {
		dist->afficheVillei(sol[i]);
		cout<<" - ";
	}
	dist->afficheVillei(sol[0]);
	cout<<"\n taille : "<<calculerLongueurCircuitSol(sol, dist)<<endl;

}


