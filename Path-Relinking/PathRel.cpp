#include <cstdlib>
#include <iostream>
#include "PathRel.hpp"
#include "../Distancier/Distancier.hpp"
#include "../code_fourni.hpp"

using namespace std;

double deltaSwap(int *sol, const Distancier * const dist, int i, int j) {
	double delta = 0;
	int N, Si, Sj;
	Si = sol[i];
	Sj = sol[j];
	N = dist->getN();
	
	//~ cout << "i=" << i << " j="<<j<<endl;
	if (i > j) {
		//~ cout << "Harricot" << endl;
		i = i - j;
		j = i + j;
		i = j - i;
	}
	
	if (i==j-1) {
		if (i==0) {
			delta = delta - dist->getDistance(sol[N-1], Si) + dist->getDistance(sol[N-1], Sj);
			delta = delta - dist->getDistance(Sj, sol[2]) + dist->getDistance(Si, sol[2]);
		} else if (j==N-1) {
			delta = delta - dist->getDistance(sol[N-3], Si) + dist->getDistance(sol[N-3], Sj);
			delta = delta - dist->getDistance(Sj, sol[0]) + dist->getDistance(Si, sol[0]);
		} else {
			delta = delta - dist->getDistance(sol[i-1], Si) + dist->getDistance(sol[i-1], Sj);
			delta = delta - dist->getDistance(Sj, sol[j+1]) + dist->getDistance(Si, sol[j+1]);
		}
	} else if ((i==0) && (j==N-1)) {
		delta = delta - dist->getDistance(sol[N-2], Sj) + dist->getDistance(sol[N-2], Si);
		delta = delta - dist->getDistance(Si, sol[1]) + dist->getDistance(Sj, sol[1]);
	} else {
		if (i == 0) {
			delta = delta - dist->getDistance(sol[N-1], Si) + dist->getDistance(sol[N-1], Sj);
			delta = delta - dist->getDistance(Si, sol[1]) + dist->getDistance(Sj, sol[1]);
			delta = delta - dist->getDistance(sol[j-1], Sj) + dist->getDistance(sol[j-1], Si);
			delta = delta - dist->getDistance(Sj, sol[j+1]) + dist->getDistance(Si, sol[j+1]);
		} else if (j == N-1) {
			delta = delta - dist->getDistance(sol[i-1], Si) + dist->getDistance(sol[i-1], Sj);
			delta = delta - dist->getDistance(Si, sol[i+1]) + dist->getDistance(Sj, sol[i+1]);
			delta = delta - dist->getDistance(sol[N-2], Sj) + dist->getDistance(sol[N-2], Si);
			delta = delta - dist->getDistance(sol[0], Sj) + dist->getDistance(sol[0], Si);
		} else {
			delta = delta - dist->getDistance(sol[i-1], Si) + dist->getDistance(sol[i-1], Sj);
			delta = delta - dist->getDistance(Si, sol[i+1]) + dist->getDistance(Sj, sol[i+1]);
			delta = delta - dist->getDistance(sol[j-1], Sj) + dist->getDistance(sol[j-1], Si);
			delta = delta - dist->getDistance(Sj, sol[j+1]) + dist->getDistance(Si, sol[j+1]);
		}
	}
	
	return delta;
}

int * pathRelinking(int *solA, int *solB, const Distancier * const dist, bool *improved) {
	bool termine;
	int Si, Sj;
	int i, j, k;
	int N = dist->getN();
	double zCourant = calculerLongueurCircuitSol(solA, dist);
	double zBest = calculerLongueurCircuitSol(solB, dist);
	int *solCourante = new int [N];
	int *bestSol = new int [N];
	
	for (i = 0; i < N; ++i) {	// On part de solA
		solCourante[i] = solA[i];
	}
	
	if (zCourant < zBest) {			// Si solA est meilleure que solB
		zBest = zCourant;				// solA est la meilleure solution
		for (i = 0; i < N; ++i) {
			bestSol[i] = solA[i];
		}
	} else {							// sinon solB est la meilleure solution
		for (i = 0; i < N; ++i) {
			bestSol[i] = solB[i];
		}
	}
	
	// Tant qu'il existe une permutation permettant d'aprocher solCourante de solB
	do {
		termine = true;
		for (i = 0; i < N; ++i) {	// Tester toutes les permutations possibles
			for (j = i+1; j < N; ++j) {
						//~ if (solCourante[i]==solB[j] || solCourante[j]==solB[i]) {
						if ((solCourante[i]==solB[j]) || (solCourante[j]==solB[i]) || ((solCourante[i]!=solB[i]) && (solCourante[j]!=solB[j]))) {
						// Alors on swap
						
						Si = solCourante[i];
						Sj = solCourante[j];
						
						termine = false;						
						zCourant = zCourant + deltaSwap(solCourante, dist, i, j);
						
						solCourante[i] = Sj;
						solCourante[j] = Si;
						
						if (zCourant < zBest) {	// Si la solution trouvée est meilleure
							//Alors on l'enregistre;
							for (k = 0; k < N; ++k) {
								zBest = zCourant;
								bestSol[k] = solCourante[k];
							}
						}
						
						//~ cout << "------------------------------------------" << endl;
						//~ cout << "SOL A : ";
						//~ afficheSol(solA, dist);
						//~ cout << endl;
						//~ 
						//~ cout << "SOL C : ";
						//~ afficheSol(solCourante, dist);
						//~ cout << " zCour  : " << zCourant << endl;
						//~ cout << " zBest  : " << zBest << endl;
						//~ cout << endl;
						//~ 
						//~ cout << "SOL B : ";
						//~ afficheSol(solB, dist);
						//~ cout << "------------------------------------------" << endl;
				}
			}
		}
	} while(!termine);
	
	return bestSol;
}


int * pathRelinkingReconstr(int *solA, int *solB, const Distancier * const dist, bool *improved, int n) {
	int i, j, nb, sortant, entrant, indS, indE;
	bool estSorti, estDouble;
	int N = dist->getN();
	double zCourant = calculerLongueurCircuitSol(solA, dist);
	double zBest = calculerLongueurCircuitSol(solB, dist);
	int *solCourante = new int [N];
	int *bestSol = new int [N];
	int *sortis = new int [n];
	int *doubles = new int [n];
	
	for (i = 0; i < N; ++i) {	// On part de solA
		solCourante[i] = solA[i];
	}
	
	if (zCourant < zBest) {			// Si solA est meilleure que solB
		zBest = zCourant;				// solA est la meilleure solution
		for (i = 0; i < N; ++i) {
			bestSol[i] = solA[i];
		}
	} else {							// sinon solB est la meilleure solution
		for (i = 0; i < N; ++i) {
			bestSol[i] = solB[i];
		}
	}
	
	nb = 0;
	for (i = 0; i < N; ++i) {			// Pour chaque
		sortant = solCourante[i];
		entrant = solB[i];
		if (sortant != entrant) {
			solCourante[i] = entrant;
			
			// On cherche si le sortant etait en double
			indE = 0;
			while ((indE < nb) && (doubles[indE] != sortant)) {
				++indE;
			}
			estDouble = (indE < nb);
			
			// On cherche si l'entrant etait sorti
			indS = 0;
			while ((indS < nb) && (sortis[indS] != entrant)) {
				++indS;
			}
			estSorti = (indS < nb);
			
			if (!(estSorti || estDouble)) {
				sortis[nb] = sortant;
				doubles[nb] = entrant;
				++nb;
			} else if (!estSorti) {
				sortis[indS] = sortant;
			} else if (!estDouble) {
				doubles[indE] = entrant;
			} else {
				for (j = indS+1; j < nb; ++j) {
					sortis[j-1] = sortis[j];
				}
				for (j = indE+1; j < nb; ++j) {
					doubles[j-1] = doubles[j];
				}
				--nb;
			}
			afficheSol(solCourante, dist);
		}
		
		if (nb == n) {
			for (j = 0; j < nb; ++j) {
				//~ if (
			}
			nb = 0;
		}
	}
	
	
	delete sortis;
	delete doubles;
	
	return solCourante;
}










