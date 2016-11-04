#include <iostream>

#include "3opt.hpp"
#include "../Distancier/Distancier.hpp"

#include "../code_fourni.hpp"

using namespace std;

int * ameliorerSol3OPT(int * sol, const Distancier * const dist, bool *improved) {
	//variable
		int iD, iF, jD, jF, nD, nF; //indice dans la solution des arretes consideres
		const int taille = dist->getN();
		int i,j,n,k;
		int tmp1, tmp2, tmp3, tmp4;
		int * restmp;
		double zrestmp;
		double zsol = calculerLongueurCircuitSol(sol, dist);
		
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

					//cas 1
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[jD];
						restmp[jD] = restmp[iF];
						restmp[iF] = tmp1;
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 2
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[nD];
						restmp[nD] = restmp[jF];
						restmp[jF] = tmp1;
						inverseSens(restmp, jF, nD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}
					//cas 3
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iD];
						restmp[iD] = restmp[nF];
						restmp[nF] = tmp1;
						inverseSens(restmp, nF, iD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 4
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[nD];
						tmp2 = restmp[iF];
						tmp3 = restmp[jD];
						tmp4 = restmp[jF];
						restmp[iF] = tmp1;
						restmp[jF] = tmp2;
						restmp[nD] = tmp3;
						restmp[jD] = tmp4;
						inverseSens(restmp, jF, nD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 5
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iF];
						tmp2 = restmp[jD];
						tmp3 = restmp[jF];
						tmp4 = restmp[nD];
						restmp[nD] = tmp1;
						restmp[jF] = tmp2;
						restmp[iF] = tmp3;
						restmp[jD] = tmp4;
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 6
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iD];
						tmp2 = restmp[iF];
						tmp3 = restmp[jD];
						tmp4 = restmp[nF];
						restmp[jD] = tmp1;
						restmp[iD] = tmp2;
						restmp[nF] = tmp3;
						restmp[iF] = tmp4;		
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 7
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iF];
						tmp2 = restmp[jD];
						tmp3 = restmp[jF];
						tmp4 = restmp[nD];
						restmp[jF] = tmp1;
						restmp[nD] = tmp2;
						restmp[iF] = tmp3;
						restmp[jD] = tmp4;
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zsol) {
							delete(sol);
							sol = restmp;
							zsol = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
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
		int i,j,n,k;
		int tmp1, tmp2, tmp3, tmp4;
		int * restmp;
		double zrestmp;
		int * best = new int[1]; //juste pour avoir un truc a delete et ne pas avoir de cas particulier
		double zbest = calculerLongueurCircuitSol(sol, dist);
		
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

					//cas 1
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[jD];
						restmp[jD] = restmp[iF];
						restmp[iF] = tmp1;
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 2
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[nD];
						restmp[nD] = restmp[jF];
						restmp[jF] = tmp1;
						inverseSens(restmp, jF, nD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}
					//cas 3
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iD];
						restmp[iD] = restmp[nF];
						restmp[nF] = tmp1;
						inverseSens(restmp, nF, iD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 4
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[nD];
						tmp2 = restmp[iF];
						tmp3 = restmp[jD];
						tmp4 = restmp[jF];
						restmp[iF] = tmp1;
						restmp[jF] = tmp2;
						restmp[nD] = tmp3;
						restmp[jD] = tmp4;
						inverseSens(restmp, jF, nD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 5
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iF];
						tmp2 = restmp[jD];
						tmp3 = restmp[jF];
						tmp4 = restmp[nD];
						restmp[nD] = tmp1;
						restmp[jF] = tmp2;
						restmp[iF] = tmp3;
						restmp[jD] = tmp4;
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 6
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iD];
						tmp2 = restmp[iF];
						tmp3 = restmp[jD];
						tmp4 = restmp[nF];
						restmp[jD] = tmp1;
						restmp[iD] = tmp2;
						restmp[nF] = tmp3;
						restmp[iF] = tmp4;		
						inverseSens(restmp, iF, jD, taille);
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}

					//cas 7
						restmp = new int[taille];
						for(k = 0; k<taille; ++k) {restmp[k] = sol[k];}
						tmp1 = restmp[iF];
						tmp2 = restmp[jD];
						tmp3 = restmp[jF];
						tmp4 = restmp[nD];
						restmp[jF] = tmp1;
						restmp[nD] = tmp2;
						restmp[iF] = tmp3;
						restmp[jD] = tmp4;
						if (( zrestmp = calculerLongueurCircuitSol(restmp, dist) ) < zbest) {
							delete(best);
							best = restmp;
							zbest = zrestmp;
							*improved = true;
						} else {
							delete(restmp);
						}
				}
			}
		}
	//fin
	if (*improved) {
		delete(sol);
		return best;
	} else {
		delete(best);
		return sol;
	}
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