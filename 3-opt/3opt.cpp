#include <iostream>

#include "3opt.hpp"
#include "./Distancier/Distancier.hpp"

using namespace std;

void ameliorerSol3OPT(int * sol, const Distancier * const dist, int *zSol, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
		const int taille = dist->getN();
		int d[8];
		int i,j,n,k, min;
		int tmp1, tmp2, tmp3, tmp4;

	//debut
		for(i = 0; i<taille; ++i) {
			for(j = 0; j<taille-3; ++j) {
				for(n = 0; n<taille-5; ++n) {
					//calcul de iD, iF, jD, jF, nD, nF

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
								*improved = false;
							break;
						case 1: //2-opt
								tmp1 = sol[jD];
								sol[jD] = sol[iF];
								sol[iF] = tmp1;
								*improved = true;
							break;
						case 2: //2-opt
								tmp1 = sol[nD];
								sol[nD] = sol[jF];
								sol[jF] = tmp1;
								*improved = true;
							break;
						case 3: //2-opt
								tmp1 = sol[iD];
								sol[iD] = sol[nF];
								sol[nF] = tmp1;
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
								*improved = true;
							break;
						case 6:
								tmp1 = sol[];
								tmp2 = sol[];
								tmp3 = sol[];
								tmp4 = sol[];
								sol[] = tmp1;
								sol[] = tmp2;
								sol[] = tmp3;
								sol[] = tmp4;
								*improved = true;
							break;
						case 7:
								tmp1 = sol[];
								tmp2 = sol[];
								tmp3 = sol[];
								tmp4 = sol[];
								sol[] = tmp1;
								sol[] = tmp2;
								sol[] = tmp3;
								sol[] = tmp4;
								*improved = true;
							break;
					}
				}
			}
		}

	//fin
}
