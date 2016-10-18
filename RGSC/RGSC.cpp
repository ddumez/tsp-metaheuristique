#include <iostream>
#include <cstdlib>

#include "../Distancier/Distancier.hpp"
#include "RGSC.hpp"
#include <algorithm>
#include <vector>

using namespace std;

//----------------------------------------------------------------------
// CONSTRUCTEURS
//----------------------------------------------------------------------

RGSC::RGSC(Distancier *D) {
	this->D = D;
	this->iteration = 0;
	
	calculerTailles();
	initialiserCouples();
	genererPreferences();
}

//----------------------------------------------------------------------
// DESTRUCTEUR
//----------------------------------------------------------------------

RGSC::~RGSC() {
	/// DETRUIRE int**couples
}

//----------------------------------------------------------------------
// AFFICAHGES
//----------------------------------------------------------------------
void RGSC::afficherPreferences() {
	int nbCouple = this->tailles[this->iteration];
	preference p;
	
	for (int i = 0; i < nbCouple; ++i) {
		cout<<i<<": ";
		for (int j = 0; j < nbCouple; ++j) {
			p = this->preferences[i][j];
			cout<<"[destination="<<p.destination<<"|distance="<<p.distance<<"|v1="<<p.v1<<"|v2="<<p.v2<<"]"<<endl;
		}
	}
}

void RGSC::afficherPreferences(const int i) {
}

void RGSC::afficherCouplesRecursif() {
}

void RGSC::afficherCouples() {
	int i = this->iteration;
	int N = this->tailles[i];
	couple c;
	
	cout << "tailles["<<this->iteration<<"]="<<this->tailles[this->iteration]<<endl;
	for (int j = 0; j < N; ++j) {
		c = this->couples[i][j];
		cout<<i<<": [c1="<<c.c1<<"|c2="<<c.c2<<"|v1="<<c.v1<<"|v2="<<c.v2<<"|ext1="<<c.ext1<<"|ext2="<<c.ext2<<"|indPref="<<c.indPref<<"|longueur="<<c.longueur<<"]"<<endl;
	}
	cout << endl;
}

void RGSC::afficherCouples(const int i) {
}

//----------------------------------------------------------------------
// METHODES
//----------------------------------------------------------------------

/// ALLOUER MEMOIRE COUPLES
void RGSC::calculerTailles() {
	int N = this->D->getN();
	this->nbMariage = 0;
	
	while (N >= 2) {
		tailles.push_back(N);
		if (N%2==0) {
			N = N / 2;
		} else {
			N = (N+1) / 2;
		}
		this->nbMariage = this->nbMariage + 1;
	}
	tailles.push_back(N);
}

void RGSC::initialiserCouples() {
	int nbMariage = this->nbMariage;
	int taille;
	
	// On alloue toute la mémoire nécessaire
	this->couples = new couple * [nbMariage];
	for (int i = 0; i < nbMariage; ++i) {
		taille = this->tailles[i];
		this->couples[i] = new couple [taille];
	}
	
	// Initialisation de la première ligne du tableau
	int N = D->getN();
	couple c;
	for (int i = 0; i < N; ++i) {
		c.c1 = i;
		c.c2 = -1;
		c.v1 = -1;
		c.v2 = -1;
		c.ext1 = i;
		c.ext2 = -1;
		c.indPref = 0;
		c.longueur = 0;
		this->couples[0][i] = c;
	}
}

void RGSC::genererPreferences() {
	
}

void RGSC::triPreferences() {
	int N = this->tailles[iteration];
	preference prefJ1, prefJ0;
	
	// Pour chaque ville
	for (int i = 0; i < N; ++i) {
		bool fini = false;
		// Tant que le tableau n'est pas trié
		while (!fini) {
			//~ afficherPreferences(); cout << endl;
			prefJ0 = this->preferences.at(i).at(0);
			fini = true;
			for (int j = 1; j < N; ++j) {
				prefJ1 = this->preferences.at(i).at(j);
				if (plusPres(i, prefJ1.destination, prefJ0.destination)) {
					fini = false;
					this->preferences.at(i).at(j-1) = prefJ1;
					this->preferences.at(i).at(j) = prefJ0;
				} else {
					prefJ0 = prefJ1;
				}
			}
		}
	}
}

void RGSC::plusProchesV1V2(const couple c1, const couple c2, int *v1, int *v2) const {
	int v11, v12, v21, v22;
	//~ v11 = ext1.
}

bool RGSC::plusPres(const int depart, const int v1, const int v2) const {
	return (getDistance(depart, v1) < getDistance(depart, v2));
}

bool RGSC::accepteUnion(const couple c1, const couple c2) const {
}

void RGSC::unir(int indC1, int indC2) { // c1 demande à s'unir avec c2
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
