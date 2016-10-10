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
	
	allouerCouples();
	initialiserPreferences();
}

//----------------------------------------------------------------------
// DESTRUCTEUR
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
// AFFICAHGES
//----------------------------------------------------------------------

void RGSC::afficherPreferences() {
	for (int i = 0; i < getN(); ++i) {
		cout << i << " :\t";
		for (int j = 0; j < getN(); ++j) {
			cout << preferences[i][j] << " | ";
		}
		cout << endl;
	}
}

//----------------------------------------------------------------------
// METHODES
//----------------------------------------------------------------------

void RGSC::allouerCouples() {
	int N = getN();
	
	// Variables pour taille précise du tableau de couples
	int *tailles = new int[N/2];	// Nombre de couples à chaque itération
	int nbIteration = 0;			// Nombre d'itération du mariage stable
	
	// Calcul du nombre de couples à chaque itération
	while (N > 2) {
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
	
	//~ cout << "nbIteration : " << nbIteration << endl;
	for (int i = 0; i < nbIteration; ++i) {
		this->couples[i] = new couple [tailles[i]];
		//~ cout << i << " : taille : " << tailles[i] << endl;
	}
	
	// Suppression du tableau stockant le nombre de couples à chaque itération
	delete[] tailles;	/// Ou les conserver pour les utiliser ?
}

void RGSC::initialiserPreferences() {
	int N = getN();
	
	// Allocation mémoire du tableau des préférences
	this->preferences = new int * [N];
	
	for (int i = 0; i < N; ++i) {
		this->preferences[i] = new int [N];
	}
	
	// TRIBULLE OU TRI-INSERTION ?
	for (int i = 0; i < N; ++i) { ///	TODO
		for (int j = 0; j < N; ++j) {
			this->preferences[i][j] = 0;	// tribulle je suppose
		}
	}
}

int RGSC::getN() {
	return this->D->getN();
}
