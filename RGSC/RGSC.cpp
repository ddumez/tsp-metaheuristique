#include <iostream>
#include <cstdlib>

#include "../Distancier/Distancier.hpp"
#include "RGSC.hpp"

using namespace std;

//----------------------------------------------------------------------
// CONSTRUCTEURS
//----------------------------------------------------------------------

RGSC::RGSC(Distancier *D) {
	this->D = D;
	int N = D->getN();
	
	// Allocation mémoire du tableau des préférences
	this->preferences = new int * [N];	//
	
	for (int i = 0; i < N; ++i) {
		preferences[i] = new int [N];
	}
	
	// Variables pour taille précise du tableau de couples
	int *tailles = new int[N/2];	// Nombre de couples à chaque itération
	int nbIteration = 0;			// Nombre d'itération du mariage stable
	
	// Calcule du nombre de couples à chaque itération
	while (N > 1) {
		if (N%2 == 0) {
			N = N/2;
		} else {
			N = (N+1)/2;
		}
		tailles[nbIteration] = N;
		nbIteration = nbIteration + 1;
	}
	tailles[nbIteration] = 1;
	nbIteration = nbIteration + 1;
	
	//Allocation mémoire du tableau des couples
	this->nbMariage = nbIteration;
	this->couples = new couple * [nbIteration];
	
	for (int i = 0; i < nbIteration; ++i) {
		this->couples[i] = new couple [tailles[i]];
	}
	
	// Suppression du tableau stockant le nombre de couples à chaque itération
	delete[] tailles;	/// Ou les conserver pour les utiliser ?
	
	// Initialisation du tableau des préférences
	//~ for (int i = 0; i < D.N; ++i) {
		//~ 
	//~ }
}

RGSC::~RGSC() {
	for (int i = 0; i < this->nbMariage; ++i) {
		delete[] this->couples[i];
	}
	delete[] this->couples;
	
	for (int i = 0; i < this->D->getN(); ++i) {
		delete[] this->preferences[i];
	}
	delete[] this->preferences;
}
