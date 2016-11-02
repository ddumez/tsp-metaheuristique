#include <iostream>

#include "3opt.hpp"
#include "../Distancier/Distancier.hpp"

#include "../code_fourni.hpp"

using namespace std;

void ameliorerSol3OPT(int * sol, const Distancier * const dist, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
		const int taille = dist->getN();
		double d[8];
		int i,j,n,k, min;
		int tmp1, tmp2, tmp3, tmp4;

	//debut
		*improved = false;

		for (i = 0; i < taille; ++i) {
			for (j = 0; j < taille-5; ++j) {
				for(n = 0; n < taille-6-j; ++n) {
					//calcul de iD, iF, jD, jF, nD, nF
					iD= i % taille;
					iF= (i+1) % taille;
					jD= (i+j+2) % taille;
					jF= (i+j+3) % taille;
					nD = (i+j+n+4) % taille;
					nF = (i+j+n+5) % taille; 

					//calcul des distances des diferents parcours
					d[0] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[1] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[2] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[3] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[iF],sol[nF]);
					d[4] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[jD]) + dist->getDistance(sol[iF],sol[nF]);
					d[5] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jF],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
					d[6] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[7] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);

					//choix du meilleur parcour
					min = 0;
					for(k = 1; k<8; ++k) {
						if(d[k] < d[min]) {min = k;}
					}

					//application du meilleur parcour
					switch(min) {
						case 0:
								//on ne change rien
							break;
						case 1: //2-opt
								tmp1 = sol[jD];
								sol[jD] = sol[iF];
								sol[iF] = tmp1;
								inverseSens(sol, iF, jD, taille);
								*improved = true;
							break;
						case 2: //2-opt
								tmp1 = sol[nD];
								sol[nD] = sol[jF];
								sol[jF] = tmp1;
								inverseSens(sol, jF, nD, taille);
								*improved = true;
							break;
						case 3: //2-opt
								tmp1 = sol[iD];
								sol[iD] = sol[nF];
								sol[nF] = tmp1;
								inverseSens(sol, nF, iD, taille);
								*improved = true;
							break;
						case 4:
								tmp1 = sol[nD];
								tmp2 = sol[iF];
								tmp3 = sol[jD];
								tmp4 = sol[jF];
								sol[iF] = tmp1;
								sol[jF] = tmp2;
								sol[nD] = tmp3;
								sol[jD] = tmp4;
								inverseSens(sol, jF, nD, taille);
								*improved = true;
							break;
						case 5:
								tmp1 = sol[iF];
								tmp2 = sol[jD];
								tmp3 = sol[jF];
								tmp4 = sol[nD];
								sol[nD] = tmp1;
								sol[jF] = tmp2;
								sol[iF] = tmp3;
								sol[jD] = tmp4;		
								inverseSens(sol, iF, jD, taille);
								*improved = true;
							break;
						case 6:
								tmp1 = sol[iD];
								tmp2 = sol[iF];
								tmp3 = sol[jD];
								tmp4 = sol[nF];
								sol[jD] = tmp1;
								sol[iD] = tmp2;
								sol[nF] = tmp3;
								sol[iF] = tmp4;		
								inverseSens(sol, iF, jD, taille);
								*improved = true;
							break;
						case 7:
								tmp1 = sol[iF];
								tmp2 = sol[jD];
								tmp3 = sol[jF];
								tmp4 = sol[nD];
								sol[jF] = tmp1;
								sol[nD] = tmp2;
								sol[iF] = tmp3;
								sol[jD] = tmp4;
								*improved = true;
							break;
					}
				}
			}
		}
	//fin
}


void ameliorerSol3OptPPD(int * sol, const Distancier * const dist, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
		const int taille = dist->getN();
		double d[8];
		int i,j,n,k, min;
		int tmp1, tmp2, tmp3, tmp4;
		int ibest, jbest, nbest, mbest;
		double zdiff = 0;
	
	//debut
		*improved = false;

		for (i = 0; i < taille; ++i) {
			for (j = 0; j < taille-5; ++j) {
				for(n = 0; n < taille-6-j; ++n) {

					//calcul de iD, iF, jD, jF, nD, nF
					iD = i % taille;
					iF = (i+1) % taille;
					jD = (i+j+2) % taille;
					jF = (i+j+3) % taille;
					nD = (i+j+n+4) % taille;
					nF = (i+j+n+5) % taille; 

					//calcul des distances des diferents parcours
					d[0] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[1] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[2] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[3] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[iF],sol[nF]);
					d[4] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[jD]) + dist->getDistance(sol[iF],sol[nF]);
					d[5] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jF],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
					d[6] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[7] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);

					//choix du meilleur parcour
					min = 0;
					for(k = 1; k<8; ++k) {
						if(d[k] < d[min]) {min = k;}
					}

					//test si c'est un meilleur mouvement
					if (- d[0] + d[min] < zdiff) {
						*improved = true;

						//enregistrement de la meilleure solution actuele
						zdiff = - d[0] + d[min];
						ibest = i;
						jbest = j;
						nbest = n;
						mbest = min;
					}
				}
			}
		}

		//application du meilleur movement trouve
		if(*improved) {
			//re-calcul des indices
			iD = ibest % taille;
			iF = (ibest+1) % taille;
			jD = (ibest+jbest+2) % taille;
			jF = (ibest+jbest+3) % taille;
			nD = (ibest+jbest+nbest+4) % taille;
			nF = (ibest+jbest+nbest+5) % taille;

			//application du meilleur parcour
			switch(mbest) {
				case 1: //2-opt
						tmp1 = sol[jD];
						sol[jD] = sol[iF];
						sol[iF] = tmp1;
						inverseSens(sol, iF, jD, taille);
					break;
				case 2: //2-opt
						tmp1 = sol[nD];
						sol[nD] = sol[jF];
						sol[jF] = tmp1;
						inverseSens(sol, jF, nD, taille);
					break;
				case 3: //2-opt
						tmp1 = sol[iD];
						sol[iD] = sol[nF];
						sol[nF] = tmp1;
						inverseSens(sol, nF, iD, taille);
					break;
				case 4:
						tmp1 = sol[nD];
						tmp2 = sol[iF];
						tmp3 = sol[jD];
						tmp4 = sol[jF];
						sol[iF] = tmp1;
						sol[jF] = tmp2;
						sol[nD] = tmp3;
						sol[jD] = tmp4;
						inverseSens(sol, jF, nD, taille);
					break;
				case 5:
						tmp1 = sol[iF];
						tmp2 = sol[jD];
						tmp3 = sol[jF];
						tmp4 = sol[nD];
						sol[nD] = tmp1;
						sol[jF] = tmp2;
						sol[iF] = tmp3;
						sol[jD] = tmp4;		
						inverseSens(sol, iF, jD, taille);
					break;
				case 6:
						tmp1 = sol[iD];
						tmp2 = sol[iF];
						tmp3 = sol[jD];
						tmp4 = sol[nF];
						sol[jD] = tmp1;
						sol[iD] = tmp2;
						sol[nF] = tmp3;
						sol[iF] = tmp4;		
						inverseSens(sol, iF, jD, taille);
					break;
				case 7:
						tmp1 = sol[iF];
						tmp2 = sol[jD];
						tmp3 = sol[jF];
						tmp4 = sol[nD];
						sol[jF] = tmp1;
						sol[nD] = tmp2;
						sol[iF] = tmp3;
						sol[jD] = tmp4;
					break;
			}
		}
	//fin
}

void inverseSens(int * sol, const int i, const int j, const int n) {
	int tmp;
	if (i-1 < j) {
		for (int k=1; k<=(j-(i+1))/2; k++) {
			tmp = sol[i+k];
			sol[i+k] = sol[j-k];
			sol[j-k] = tmp;
		}
	} else {
		for (int k=1; k<=((i-1)-(j+2))/2; k++) {
			tmp = sol[j+1+k];
			sol[j+1+k] = sol[i-1-k];
			sol[i-1-k] = tmp;
		}
	}
}