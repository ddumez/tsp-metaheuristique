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
		int tmp, lim;
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
								tmp = sol[jD];
								sol[jD] = sol[iF];
								sol[iF] = tmp;
								inverseSens(sol, iF, jD, taille);
								*improved = true;
							break;
						case 2: //2-opt //Ok
								tmp = sol[nD];
								sol[nD] = sol[jF];
								sol[jF] = tmp;
								inverseSens(sol, jF, nD, taille);
								*improved = true;
							break;
						case 3: //2-opt
								tmp = sol[iD];
								sol[iD] = sol[nF];
								sol[nF] = tmp;
								//inversion manuelle car differente des autres
									//calcul du nombre de case entre iD et nF divise par 2
								if (nF < iD) {
									lim = (iD-nF) / 2;
								} else { //iD > nF
									lim = (dist->getN() - nF + iD) / 2;
								}
									//inversion
								for(k = 1; k<lim; ++k) {
									tmp = sol[(iD-k+dist->getN()) % dist->getN()];
									sol[(iD-k+dist->getN()) % dist->getN()] = sol[(nF+k) % dist->getN()];
									sol[(nF+k) % dist->getN()] = tmp;
								}
								*improved = true;
							break;
						case 4: 
								sol7 = new int[dist->getN()]; //allocation pour la recopie
								k = iD; //k est l'indice du tableau sol7 auquel on est rendu

								sol7[k] = sol[iD]; //le point de depart
								++k;
								
								//on place le segment jF-nD
								sol7[k % dist->getN()] = sol[jF];
								++k;
								for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}
								sol7[k % dist->getN()] = sol[nD];
								++k;

								
								//on place le segment jD-iF
								sol7[k % dist->getN()] = sol[jD];
								++k;
								for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp + dist->getN()) % dist->getN() != iF; --tmp ) {
									sol7[k % dist->getN()] = sol[(tmp + dist->getN()) % dist->getN()];
									++k;							
								}
								sol7[k % dist->getN()] = sol[iF];
								++k;

								//on place le segment nF-iD, on revien au point de depard
								sol7[k % dist->getN()] = sol[nF];
								++k;
								for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}

								//mise a jour de la solution
								delete(sol);
								sol = sol7;
								
								*improved = true;
							break;
						case 5:
								sol7 = new int[dist->getN()]; //allocation pour la recopie
								k = iD; //k est l'indice du tableau sol7 auquel on est rendu

								sol7[k] = sol[iD]; //le point de depart
								++k;
								
								//on place le segment nD-jF
								sol7[k % dist->getN()] = sol[nD];
								++k;
								for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
									sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
									++k;
								}
								sol7[k % dist->getN()] = sol[jF];
								++k;

								
								//on place le segment iF-jD
								sol7[k % dist->getN()] = sol[iF];
								++k;
								for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;							
								}
								sol7[k % dist->getN()] = sol[jD];
								++k;

								//on place le segment nF-iD, on revien au point de depard
								sol7[k % dist->getN()] = sol[nF];
								++k;
								for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}

								//mise a jour de la solution
								delete(sol);
								sol = sol7;
								
								*improved = true;
							break;
						case 6:
								sol7 = new int[dist->getN()]; //allocation pour la recopie
								k = iD; //k est l'indice du tableau sol7 auquel on est rendu

								sol7[k] = sol[iD]; //le point de depart
								++k;
								
								//on place le segment jD-iF
								sol7[k % dist->getN()] = sol[jD];
								++k;
								for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != iF; --tmp ) {
									sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
									++k;							
								}
								sol7[k % dist->getN()] = sol[iF];
								++k;

								//on place le segment nD-jF
								sol7[k % dist->getN()] = sol[nD];
								++k;
								for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
									sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
									++k;
								}
								sol7[k % dist->getN()] = sol[jF];
								++k;

								//on place le segment nF-iD, on revien au point de depard
								sol7[k % dist->getN()] = sol[nF];
								++k;
								for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}

								//mise a jour de la solution
								delete(sol);
								sol = sol7;
								
								*improved = true;
							break;
						case 7: 
								sol7 = new int[dist->getN()]; //allocation pour la recopie
								k = iD; //k est l'indice du tableau sol7 auquel on est rendu

								sol7[k] = sol[iD]; //le point de depart
								++k;
								
								//on place le segment jF-nD
								sol7[k % dist->getN()] = sol[jF];
								++k;
								for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}
								sol7[k % dist->getN()] = sol[nD];
								++k;

								
								//on place le segment iF-jD
								sol7[k % dist->getN()] = sol[iF];
								++k;
								for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;							
								}
								sol7[k % dist->getN()] = sol[jD];
								++k;
	
								//on place le segment nF-iD, on revien au point de depard
								sol7[k % dist->getN()] = sol[nF];
								++k;
								for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
									sol7[k % dist->getN()] = sol[tmp % dist->getN()];
									++k;
								}

								//mise a jour de la solution
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
 		int tmp, lim;
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

			//application du mouvement
			switch(mbest) {
				case 0:
						//on ne change rien
					break;
				case 1: //2-opt
						tmp = sol[jD];
						sol[jD] = sol[iF];
						sol[iF] = tmp;
						inverseSens(sol, iF, jD, taille);
						*improved = true;
					break;
				case 2: //2-opt
						tmp = sol[nD];
						sol[nD] = sol[jF];
						sol[jF] = tmp;
						inverseSens(sol, jF, nD, taille);
						*improved = true;
					break;
				case 3: //2-opt
						tmp = sol[iD];
						sol[iD] = sol[nF];
						sol[nF] = tmp;
						//inversion manuelle car differente des autres
							//calcul du nombre de case entre iD et nF divise par 2
						if (nF < iD) {
							lim = (iD-nF) / 2;
						} else { //iD > nF
							lim = (dist->getN() - nF + iD) / 2;
						}
							//inversion
						for(k = 1; k<lim; ++k) {
							tmp = sol[(iD-k+dist->getN()) % dist->getN()];
							sol[(iD-k+dist->getN()) % dist->getN()] = sol[(nF+k) % dist->getN()];
							sol[(nF+k) % dist->getN()] = tmp;
						}
						*improved = true;
					break;
				case 4: 
						sol7 = new int[dist->getN()]; //allocation pour la recopie
						k = iD; //k est l'indice du tableau sol7 auquel on est rendu

						sol7[k] = sol[iD]; //le point de depart
						++k;
						
						//on place le segment jF-nD
						sol7[k % dist->getN()] = sol[jF];
						++k;
						for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}
						sol7[k % dist->getN()] = sol[nD];
						++k;

						
						//on place le segment jD-iF
						sol7[k % dist->getN()] = sol[jD];
						++k;
						for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp + dist->getN()) % dist->getN() != iF; --tmp ) {
							sol7[k % dist->getN()] = sol[(tmp + dist->getN()) % dist->getN()];
							++k;							
						}
						sol7[k % dist->getN()] = sol[iF];
						++k;

						//on place le segment nF-iD, on revien au point de depard
						sol7[k % dist->getN()] = sol[nF];
						++k;
						for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}

						//mise a jour de la solution
						delete(sol);
						sol = sol7;
						
						*improved = true;
					break;
				case 5:
						sol7 = new int[dist->getN()]; //allocation pour la recopie
						k = iD; //k est l'indice du tableau sol7 auquel on est rendu

						sol7[k] = sol[iD]; //le point de depart
						++k;
						
						//on place le segment nD-jF
						sol7[k % dist->getN()] = sol[nD];
						++k;
						for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
							sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
							++k;
						}
						sol7[k % dist->getN()] = sol[jF];
						++k;

						
						//on place le segment iF-jD
						sol7[k % dist->getN()] = sol[iF];
						++k;
						for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;							
						}
						sol7[k % dist->getN()] = sol[jD];
						++k;

						//on place le segment nF-iD, on revien au point de depard
						sol7[k % dist->getN()] = sol[nF];
						++k;
						for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}

						//mise a jour de la solution
						delete(sol);
						sol = sol7;
						
						*improved = true;
					break;
				case 6:
						sol7 = new int[dist->getN()]; //allocation pour la recopie
						k = iD; //k est l'indice du tableau sol7 auquel on est rendu

						sol7[k] = sol[iD]; //le point de depart
						++k;
						
						//on place le segment jD-iF
						sol7[k % dist->getN()] = sol[jD];
						++k;
						for(tmp = (jD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != iF; --tmp ) {
							sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
							++k;							
						}
						sol7[k % dist->getN()] = sol[iF];
						++k;

						//on place le segment nD-jF
						sol7[k % dist->getN()] = sol[nD];
						++k;
						for(tmp = (nD-1+dist->getN()) % dist->getN(); (tmp+dist->getN()) % dist->getN() != jF; --tmp ) {
							sol7[k % dist->getN()] = sol[(tmp+dist->getN()) % dist->getN()];
							++k;
						}
						sol7[k % dist->getN()] = sol[jF];
						++k;

						//on place le segment nF-iD, on revien au point de depard
						sol7[k % dist->getN()] = sol[nF];
						++k;
						for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}

						//mise a jour de la solution
						delete(sol);
						sol = sol7;
						
						*improved = true;
					break;
				case 7:
						sol7 = new int[dist->getN()]; //allocation pour la recopie
						k = iD; //k est l'indice du tableau sol7 auquel on est rendu

						sol7[k] = sol[iD]; //le point de depart
						++k;
						
						//on place le segment jF-nD
						sol7[k % dist->getN()] = sol[jF];
						++k;
						for(tmp = (jF+1) % dist->getN(); tmp % dist->getN() != nD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}
						sol7[k % dist->getN()] = sol[nD];
						++k;

						
						//on place le segment iF-jD
						sol7[k % dist->getN()] = sol[iF];
						++k;
						for(tmp = (iF+1) % dist->getN(); tmp % dist->getN() != jD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;							
						}
						sol7[k % dist->getN()] = sol[jD];
						++k;

						//on place le segment nF-iD, on revien au point de depard
						sol7[k % dist->getN()] = sol[nF];
						++k;
						for(tmp = (nF+1) % dist->getN(); tmp % dist->getN() != iD; ++tmp ) {
							sol7[k % dist->getN()] = sol[tmp % dist->getN()];
							++k;
						}

						//mise a jour de la solution
						delete(sol);
						sol = sol7;
						
						*improved = true;
					break;
			}
		}

	//fin
	return sol;
}

void inverseSens(int * sol, const int j, const int i, const int n) {
	int tmp1;
	double tmp2;
	if (j < i) {
		tmp2 = (double)(i-j) / 2.0;
	} else { //i > j
		tmp2 = (double)(n - j + i) / 2.0;
	}
		//inversion
	for(int k = 1; k<tmp2; ++k) {
		tmp1 = sol[(i-k+n) % n];
		sol[(i-k+n) % n] = sol[(j+k) % n];
		sol[(j+k) % n] = tmp1;
	}
}