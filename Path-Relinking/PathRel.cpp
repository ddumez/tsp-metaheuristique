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
	
	for (int i = 0; i < N; ++i) {	// On part de solA
		solCourante[i] = solA[i];
	}
	
	if (zCourant < zBest) {			// Si solA est meilleure que solB
		zBest = zCourant;				// solA est la meilleure solution
		for (int i = 0; i < N; ++i) {
			bestSol[i] = solA[i];
		}
	} else {							// sinon solB est la meilleure solution
		for (int i = 0; i < N; ++i) {
			bestSol[i] = solB[i];
		}
	}
	
	// Tant qu'il existe une permutation permettant d'aprocher solCourante de solB
	do {
		termine = true;
		for (i = 0; i < N; ++i) {	// Tester toutes les permutations possibles
			for (j = i+1; j < N; ++j) {
				// Si 
				if ((solCourante[i] != solB[i]) && (solCourante[j] != solB[j])) {
					if ((solCourante[i] == solB[j]) || (solCourante[j] == solB[i])) {
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
						
						cout << "------------------------------------------" << endl;
						cout << "SOL A : ";
						afficheSol(solA, dist);
						cout << endl;
						
						cout << "SOL C : ";
						afficheSol(solCourante, dist);
						cout << " zCour  : " << zCourant << endl;
						cout << " zBest  : " << zBest << endl;
						cout << endl;
						
						cout << "SOL B : ";
						afficheSol(solB, dist);
						cout << "------------------------------------------" << endl;
					}
				}
			}
		}
	} while(!termine);
	
	return bestSol;
}
