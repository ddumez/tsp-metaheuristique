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
	initialiserPreferences();
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
	afficherPreferences(this->iteration);
}

void RGSC::afficherPreferences(const int i) {
	int N = this->tailles[i];
	
	for (int i = 0; i < N; ++i) {
		cout << i << " :\t";
		for (int j = 0; j < N; ++j) {
			cout << "("<< preferences[i][j].extremiteDominante << "," << preferences[i][j].destination << ") | ";
		}
		cout << endl;
	}
}

void RGSC::afficherCouples() {
	afficherCouples(this->iteration);
}

void RGSC::afficherCouples(const int i) {
	int N = this->tailles[i];
	couple c;
	
	for (int j = 0; j < N; ++j) {
		c = this->couples[i][j];
		cout << j << ":\t" << c.v1 << " (" << c.c1 << "|" << c.c2 << ") " << c.v2 << endl;
	}
	
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
	int nIteration = this->nbMariage;
	
	this->couples = new couple * [nIteration];
	for (int i = 0; i < nIteration; ++i) {
		this->couples[i] = new couple [this->tailles[i]];
	}
	
	int N = getN();
	couple c;
	
	for (int i = 0; i < N; ++i) {
		c.c1 = i;
		c.c2 = -1;
		c.v1 = i;
		c.v2 = -1;
		this->couples[0][i] = c;
	}
}


/// ALLOUER MEMOIRE ET INITIALISER PREFERENCES (avant formation couples)
void RGSC::initialiserPreferences() {
	int N = this->D->getN();
	preference tmp;
	
	for (int i = 0; i < N; ++i) {
		preferences.push_back(vector<preference>());
		for (int j = 0; j < N; ++j) {
			tmp.destination = j;
			tmp.extremiteDominante = i;
			preferences.at(i).push_back(tmp);
		}
	}
	
	triPreferences();
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

bool RGSC::plusPres(const int depart, const int v1, const int v2) const {
	//~ cout << "dist("<<depart<<","<<v2<<")="<<getDistance(depart, v2) << " / ";
	//~ cout << "dist("<<depart<<","<<v1<<")="<<getDistance(depart, v1)<<endl;
	return (getDistance(depart, v1) < getDistance(depart, v2));
}

void RGSC::marier() {
	int nbCouple = this->tailles[iteration];
	bool **mariage;
	
	
	while (!fini) {
		
	}
	
	this->iteration = this->iteration+1;
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
