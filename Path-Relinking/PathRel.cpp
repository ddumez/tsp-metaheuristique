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

double deltaInsertion(int *sol, const Distancier * const dist, int i, int v) {
	int N = dist->getN();
	double delta;
	
	if (i == 0) {
		delta = dist->getDistance(sol[N-1], v)
				+ dist->getDistance(v, sol[1])
				- dist->getDistance(sol[N-1], sol[0])
				- dist->getDistance(sol[0], sol[1]);
	} else if (i == N-1) {
		delta = dist->getDistance(sol[N-2], v)
				+ dist->getDistance(v, sol[0])
				- dist->getDistance(sol[N-2], sol[N-1])
				- dist->getDistance(sol[N-1], sol[0]);
				
	} else {
		delta = dist->getDistance(sol[i-1], v)
				+ dist->getDistance(v, sol[i+1])
				- dist->getDistance(sol[i-1], sol[i])
				- dist->getDistance(sol[i], sol[i+1]);
	}
	
	return delta;
}

// On répare sol
// On renvoie la différence de longueur de la solution réparée
double reparerSolution(int *sol, int *solB, const Distancier *const dist, int *doubles, int *absents, int nb) {
	int N = dist->getN();
	double delta = 0;
	int debut;
	int i, j, k, ind, indSuiv, indMin;
	bool debutTrouve, fini;
	
	//~ afficheSol(solB, dist);
	ind = 0;
	while (nb > 0) {	// Tant qu'on a pas retiré tous les doubles ni ajouté tous les absents
		// On se place sur la première case trouvée de la solution qui n'est pas doublée
		while (sol[ind]!=solB[ind]) { // Par simplification, je prends la première case fixée (égale à celle de la solution d'arrivée)
			++ind;
			if (ind == N) {
				ind = 0;
			}
		}
		
		//~ afficheSol(sol, dist);
		//~ cout << "doublés=";
		//~ for (int i = 0; i < nb; ++i) {
			//~ cout<<(char)(doubles[i]+65)<<"|";
		//~ }
		//~ cout << endl << "disparus=";
		//~ for (int i = 0; i < nb; ++i) {
			//~ cout <<(char)(absents[i]+65)<<"|";
		//~ }
		//~ cout << endl << endl;
		
		// On cherche la première case doublée
		debutTrouve = false;
		while (!debutTrouve) {				// Tant qu'on a pas trouvé
			while (sol[ind]==solB[ind]) {		// On parcourt le chemin jusqu'à trouver une case fixée
				ind = (ind+1)%N;
			}
			//~ cout << "ind non fixé = " << ind << endl;
			
			// On cherche si sur la case non fixée est une ville en double
			i = 0;
			while ((i<nb) && (sol[ind] != doubles[i])) { 
				++i;
			}
			if (i<nb) {		// Si c'est le cas, alors on a trouvé le début
				debutTrouve = true;
				//~ cout << "est en double" << endl;
			} else {		// Sinon, alors on regarde le prochaine indice
				ind = (ind+1)%N;
				//~ cout << "n'est pas en double" << endl;
				//~ cout << "indice suivant : " << ind << endl;
			}
		}

		if (ind == 0) {
			debut = N-1;
		} else {
			debut = ind-1;
		}
		
		indSuiv = ind;
		ind = debut;
		fini = false;
		while (!fini) {
			
			// On cherche de manière gloutonne la meilleure ville à ajouter après
			indMin = 0;
			for (i = 1; i < nb; ++i) {
				if (dist->getDistance(sol[ind], absents[i]) < dist->getDistance(sol[ind], absents[indMin])) {
					indMin = i;
				}
			}
			
			// On shifte les villes doublees
			j = 0;
			while (doubles[j] != sol[indSuiv]) {
				++j;
			}
			for (j=j+1; j < nb; ++j) {
				doubles[j-1] = doubles[j];
			}
			
			// On change la ville
			delta = delta + deltaInsertion(sol, dist, indSuiv, absents[indMin]);
			sol[indSuiv] = absents[indMin];
			
			// On shifte les villes absentes
			for (i = indMin+1; i < nb; ++i) {
				absents[i-1] = absents[i];
			}
			
			nb = nb -1;
			
			// on se place sur la case suivante
			ind = indSuiv;
			indSuiv = (indSuiv+1)%N;
			
			if ((k<nb) && (sol[indSuiv] != solB[indSuiv])) {
				k = 0;
				while ((k<nb) && (doubles[k]!=sol[indSuiv])) {
					++k;
				}
				fini = k==nb;
			} else {
				fini = true;
			}
			
		}
		

	}
	
	return delta;
}

//~ // On répare sol
//~ // On renvoie la différence de longueur de la solution réparée
//~ double reparerSolution(int *sol, int *solB, const Distancier *const dist, int *doubles, int *absents, int nb) {
	//~ int N = dist->getN();
	//~ double delta = 0;
	//~ int debut, fin, tailleSection;
	//~ int i, ind;
	//~ int *section = new int [nb+2];
	//~ double zCourant = 0;
	//~ int *bestSection = new int [nb+2];
	//~ double zBest;
	//~ bool debutTrouve;
	//~ bool finTrouvee;
	//~ 
	//~ ind = 0;
	//~ while (nb > 0) {	// Tant qu'on a pas retiré tous les doubles ni ajouté tous les absents
		//~ // On se place sur la première case trouvée de la solution qui n'est pas doublée
		//~ while (sol[ind]!=solB[ind]) { // Par simplification, je prends la première case fixée (égale à celle de la solution d'arrivée)
			//~ ++ind;
			//~ if (ind == N) {
				//~ ind = 0;
			//~ }
		//~ }
		//~ 
		//~ // On cherche la première case doublée
		//~ debutTrouve = false;
		//~ while (!debutTrouve) {
			//~ while (sol[ind]==solB[ind]) {
				//~ ++ind;
			//~ }
			//~ i = 0;
			//~ while ((i<nb) && (sol[ind] != doubles[i])) {
				//~ ++i;
			//~ }
			//~ if (i<nb) {
				//~ debutTrouve = true;
			//~ } else {
				//~ ++ind;
			//~ }
		//~ }
		//~ if (ind == 0) {
			//~ debut = N-1;
		//~ } else {
			//~ debut = ind-1;
		//~ }
		//~ 
		//~ // On met la première ville fixée au début de la section (pour les futurs calculs)
		//~ section[0] = sol[debut];
		//~ 
		//~ // On cherche la dernière case doublée
		//~ finTrouvee = false;
		//~ while (!finTrouvee) {
			//~ i = 0;
			//~ while ((i<nb) && (sol[ind] != doubles[i])) {
				//~ ++i;
			//~ }
			//~ finTrouvee = (i==nb);
		//~ }
		//~ fin = ind;
		//~ 
		//~ // On met la dernière ville fixée à la fin de la section
		//~ section[nb+1] = sol[fin];
		//~ tailleSection = fin-debut;
		//~ if (tailleSeciont < 0) {
			//~ tailleSection = -tailleSection;
		//~ }
		//~ 
		//~ // On a maintenant une section dans laquelle il n'y a que des villes doublées
		//~ // On optimise de manière gloutonne la solution (amélioration en exact plus tard ?)
		//~ for (i = 1; i < tailleSection-1; ++i) {
			//~ section[i] = doubles
		//~ }
	//~ }
	//~ 
	//~ free(section);
	//~ return delta;
//~ }

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
	int *absents = new int [n];
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
	
	//~ afficheSol(solCourante, dist);
	//~ cout << "zCalculé=" << zCourant << endl;
	
	
	nb = 0;
	for (i = 0; i < N; ++i) {			// Pour chaque
		sortant = solCourante[i];
		entrant = solB[i];
		if (sortant != entrant) {
			//~ cout << "entrant="<<(char)(solB[i]+65)<<endl;
			//~ cout << "sortant="<<(char)(solCourante[i]+65)<<endl;
			
			zCourant = zCourant + deltaInsertion(solCourante, dist, i, entrant);
			
			solCourante[i] = entrant;
			
			// On cherche si le sortant etait en double
			indE = 0;
			while ((indE < nb) && (doubles[indE] != sortant)) {
				++indE;
			}
			estDouble = (indE < nb);	// Vrai si le sortant était en double (il disparaît alors des listes)
			
			// On cherche si l'entrant etait sorti
			indS = 0;
			while ((indS < nb) && (absents[indS] != entrant)) {
				++indS;
			}
			estSorti = (indS < nb);		// Vrai si l'entrant etait sorti (il disparaît alors des listes)
			
			if (!(estSorti || estDouble)) {	// Cas général, on ajoute les deux
				absents[nb] = sortant;
				doubles[nb] = entrant;
				++nb;
			} else if (estSorti && estDouble) {	// Sinon, ils s'annulent mutuellement
				for (j = indS+1; j < nb; ++j) {	// On shifte les listes
					absents[j-1] = absents[j];
				}
				for (j = indE+1; j < nb; ++j) {
					doubles[j-1] = doubles[j];
				}
				--nb;
			} else if (estSorti) {			// Si seul l'entrant est à retirer des absents
				absents[indS] = sortant;			// Sa case est occupée par celui qui vient de sortir
			} else if (estDouble) {			// Sinon si seul le sortant était en double
				doubles[indE] = entrant;		// Sa case est occupée par celui qui vient d'entrer
			}
			
			//~ afficheSol(solCourante, dist);
			//~ cout << "zCalculé=" << zCourant << endl;
			//~ 
			//~ cout << "doublés=";
			//~ for (int i = 0; i < nb; ++i) {
				//~ cout<<(char)(doubles[i]+65)<<"|";
			//~ }
			//~ cout << endl << "disparus=";
			//~ for (int i = 0; i < nb; ++i) {
				//~ cout <<(char)(absents[i]+65)<<"|";
			//~ }
			//~ cout << endl << endl;
		}
		
		if (nb == n) {
			cout << "REPARATION ||||||||||||||| "  << endl;
			zCourant = zCourant + reparerSolution(solCourante, solB, dist, doubles, absents, nb);
			nb = 0;
			
			//~ afficheSol(solCourante, dist);
			//~ cout << "zCalculé=" << zCourant << endl;
			//~ 
			//~ cout << "doublés=";
			//~ for (int i = 0; i < nb; ++i) {
				//~ cout<<(char)(doubles[i]+65)<<"|";
			//~ }
			//~ cout << endl << "disparus=";
			//~ for (int i = 0; i < nb; ++i) {
				//~ cout <<(char)(absents[i]+65)<<"|";
			//~ }
			//~ cout << endl << endl;
		}
		if ((nb == 0) && (zCourant < zBest)) {
			zBest = zCourant;
			for (i = 0; i < N; ++i) {
				bestSol[i] = solCourante[i];
			}
		}
	}
	
	
	free(absents);
	free(doubles);

	return bestSol;
}










