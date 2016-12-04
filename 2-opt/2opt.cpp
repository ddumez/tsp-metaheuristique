#include "2opt.hpp"
#include "./../Distancier/Distancier.hpp"

using namespace std;

int * ameliorerSol2OPT(int * sol, const Distancier * const dist, bool *improved) {
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

			if (d1>d2 + 0.000001) { //epsilon pour eviter les imprecisions numeriques
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
	return sol;
}

int * ameliorerSol2OptPPD(int * sol, const Distancier * const dist, bool *improved) {	
	int i,j,k,tmp;
	int iD, iF, jD, jF;
	double d1, d2;
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

			if (- d1 + d2 + 0.000001 < zdiff) { //epsilon pour eviter les imprecisions numeriques
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
	}
	return sol;
}