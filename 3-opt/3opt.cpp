#include <iostream>
#include <cmath>

#include "3opt.hpp"
#include "../Distancier/Distancier.hpp"

#include "../code_fourni.hpp"

using namespace std;

int * ameliorerSol3OPT(int * sol, const Distancier * const dist, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
		const int taille = dist->getN();
		int i,j,n,k, min;
		int tmp1, tmp2, tmp3, tmp4;
		double d[8];
		int * sol7; //pour la recopie partielle du cas 7
		
	//debut

		*improved = false;

		for (i = 0; i < taille; ++i) {
			for (j = 0; j < taille-5; ++j) {
				for(n = 0; n < taille-6-j; ++n) {
					//calcul de iD, iF, jD, jF, nD, nF et autre
					iD = i % taille;
					iF = (i+1) % taille;
					jD = (i+j+2) % taille;
					jF = (i+j+3) % taille;
					nD = (i+j+n+4) % taille;
					nF = (i+j+n+5) % taille;

					//calcul des distances previsionelles
					d[0] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[1] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[2] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[3] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[iF],sol[nF]);
					d[4] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[jD]) + dist->getDistance(sol[iF],sol[nF]);
					d[5] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jF],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
					d[6] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[7] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);

					//recherche du min
					min = 0;
					for(k = 1; k<8; ++k) {
						if(d[k] < d[min]) {min = k;}
					}

					//application du mouvement
					switch(min) {
						case 0:
								//on ne change rien
							break;
						case 1: //2-opt //OK
								tmp1 = sol[jD];
								sol[jD] = sol[iF];
								sol[iF] = tmp1;
								inverseSens(sol, iF, jD, taille);
								*improved = true;
							break;
						case 2: //2-opt //Ok
								tmp1 = sol[nD];
								sol[nD] = sol[jF];
								sol[jF] = tmp1;
								inverseSens(sol, jF, nD, taille);
								*improved = true;
							break;
						case 3: //2-opt //modifie a reverifier : attention aux inversions
								tmp1 = sol[iD];
								sol[iD] = sol[nF];
								sol[nF] = tmp1;
								//inversion manuelle car differente des autres
								if (nF < iD) {
									for (int k=1; k<=(iD-(nF+1))/2; k++) {
										sol[iD-k] = sol[iD-k] + sol[nF+k];
										sol[nF+k] = sol[iD-k] - sol[nF+k];
										sol[iD-k] = sol[iD-k] - sol[nF+k];
									}
								} else { //iD > nF
									for (int k=1; k<=(nF-(iD+1))/2; k++) {
										sol[nF-k] = sol[nF-k] + sol[iD+k];
										sol[iD+k] = sol[nF-k] - sol[iD+k];
										sol[nF-k] = sol[nF-k] - sol[iD+k];
									}
								}
								*improved = true;
							break;
						case 4: //OK
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
						case 5: //OK
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
						case 6: //OK
								tmp1 = sol[iF];
								tmp2 = sol[jD];
								tmp3 = sol[jF];
								tmp4 = sol[nD];
								sol[jD] = tmp1;
								sol[iF] = tmp2;
								sol[nD] = tmp3;
								sol[jF] = tmp4;
								inverseSens(sol, iF, jD, taille);
								inverseSens(sol, jF, nD, taille);
								*improved = true;
							break;
						case 7: 
								sol7 = new int[dist->getN()];
								sol7[iD] = sol[iD];
								sol7[(iD+1) % dist->getN()] = sol[jF];
								//on place le segment jF-nD
								for(k = 1; k < abs(nD-jF); ++k ) {
									sol7[(k+1) % dist->getN()] = sol[(jF+k) % dist->getN()];
								}
								sol7[(k) % dist->getN()] = sol[nD];
								sol7[(k+1) % dist->getN()] = sol[iF];
								//on place le segment iF-jD
								tmp1 = k+1;
								for(k = tmp1; k < tmp1 + abs(iF-jD); ++k ) {
									sol7[(k+1) % dist->getN()] = sol[(iF+k) % dist->getN()];
								}
								sol7[(k) % dist->getN()] = sol[jD];
								sol7[(k+1) % dist->getN()] = sol[nF];
								//on place le segment nF-iD
								for(k = k+1; k < dist->getN(); ++k ) {
									sol7[(k+1) % dist->getN()] = sol[(nF+k) % dist->getN()];
								}
								delete(sol);
								sol = sol7;
								*improved = true;
							break;
					}
				}
			}
		}
	//fin
	return sol;
}

int * ameliorerSol3OptPPD(int * sol, const Distancier * const dist, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
 		const int taille = dist->getN();
		double d[8];
		int i,j,n,k, min;
 		int tmp1, tmp2, tmp3, tmp4;
		int ibest, jbest, nbest, mbest;
		double zdiff = 0;
		int * sol7; //pour la recopie partielle du cas 7

		
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

					//distances previsiosnnelles
					//calcul des distances previsionelles
					d[0] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[1] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
					d[2] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[3] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[iF],sol[nF]);
					d[4] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[jD]) + dist->getDistance(sol[iF],sol[nF]);
					d[5] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jF],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
					d[6] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
					d[7] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);

					//recherche du min
					min = 0;
					for(k = 1; k<8; ++k) {
						if(d[k] < d[min]) {min = k;}
					}

					//test si meilleure modification
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

		//application de la meilleure modification
		if(*improved) {
			//re-calcul des indices
			iD = ibest % taille;
			iF = (ibest+1) % taille;
			jD = (ibest+jbest+2) % taille;
			jF = (ibest+jbest+3) % taille;
			nD = (ibest+jbest+nbest+4) % taille;
			nF = (ibest+jbest+nbest+5) % taille;

d[0] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
d[1] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[jF]) + dist->getDistance(sol[nD],sol[nF]);
d[2] = dist->getDistance(sol[iD],sol[iF]) + dist->getDistance(sol[jD],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
d[3] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jD],sol[jF]) + dist->getDistance(sol[iF],sol[nF]);
d[4] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[jD]) + dist->getDistance(sol[iF],sol[nF]);
d[5] = dist->getDistance(sol[iD],sol[nD]) + dist->getDistance(sol[jF],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
d[6] = dist->getDistance(sol[iD],sol[jD]) + dist->getDistance(sol[iF],sol[nD]) + dist->getDistance(sol[jF],sol[nF]);
d[7] = dist->getDistance(sol[iD],sol[jF]) + dist->getDistance(sol[nD],sol[iF]) + dist->getDistance(sol[jD],sol[nF]);
if (7 == mbest) {
	cout<<iD<<" "<<iF<<" "<<jD<<" "<<jF<<" "<<nD<<" "<<nF<<endl;
	cout<<dist->getvillei(sol[iD])<<" "<<dist->getvillei(sol[iF])<<" "<<dist->getvillei(sol[jD])<<" "<<dist->getvillei(sol[jF])<<" "<<dist->getvillei(sol[nD])<<" "<<dist->getvillei(sol[nF])<<endl;
	cout<<d[7]<<" "<<d[0]<<" "<<d[0]-d[7]<<endl;
	afficheSol(sol, dist);
}

			//application du mouvement
			switch(mbest) {
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
						//inversion manuelle car differente des autres
						if (nF < iD) {
							for (int k=1; k<=(iD-(nF+1))/2; k++) {
								sol[iD-k] = sol[iD-k] + sol[nF+k];
								sol[nF+k] = sol[iD-k] - sol[nF+k];
								sol[iD-k] = sol[iD-k] - sol[nF+k];
							}
						} else { //iD > nF
							for (int k=1; k<=(nF-(iD+1))/2; k++) {
								sol[nF-k] = sol[nF-k] + sol[iD+k];
								sol[iD+k] = sol[nF-k] - sol[iD+k];
								sol[nF-k] = sol[nF-k] - sol[iD+k];
							}
						}
						*improved = true;
					break;
				case 4: 
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
				case 5:
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
				case 6:
						tmp1 = sol[iF];
						tmp2 = sol[jD];
						tmp3 = sol[jF];
						tmp4 = sol[nD];
						sol[jD] = tmp1;
						sol[iF] = tmp2;
						sol[nD] = tmp3;
						sol[jF] = tmp4;
						inverseSens(sol, iF, jD, taille);
						inverseSens(sol, jF, nD, taille);
						*improved = true;
					break;
				case 7:
						sol7 = new int[dist->getN()];
						sol7[iD] = sol[iD];
						sol7[(iD+1) % dist->getN()] = sol[jF];
						//on place le segment jF-nD
						for(k = 1; k < abs(nD-jF); ++k ) {
							sol7[(k+1) % dist->getN()] = sol[(jF+k) % dist->getN()];
						}
						sol7[(k) % dist->getN()] = sol[nD];
						sol7[(k+1) % dist->getN()] = sol[iF];
						//on place le segment iF-jD
						tmp1 = k+1;
						for(k = tmp1; k < tmp1 + abs(iF-jD); ++k ) {
							sol7[(k+1) % dist->getN()] = sol[(iF+k) % dist->getN()];
						}
						sol7[(k) % dist->getN()] = sol[jD];
						sol7[(k+1) % dist->getN()] = sol[nF];
						//on place le segment nF-iD
						for(k = k+1; k < dist->getN(); ++k ) {
							sol7[(k+1) % dist->getN()] = sol[(nF+k) % dist->getN()];
						}
						delete(sol);
						sol = sol7;
						*improved = true;
					break;
			}
if (7 == mbest) {
	afficheSol(sol, dist);
	cout<<"\n"<<endl;
}
		}

	//fin
	return sol;
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