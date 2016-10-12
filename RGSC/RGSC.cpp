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

void RGSC::afficherCouplesInt() const {
	coupleInt c;
	for (int i = 0; i < this->tailles[this->iteration]; ++i) {
		c = this->couplesInt[i];
		cout << i << ":\t(" << c.c1 << ","<<c.c2<<") "<<c.indPref<<"-"<<c.aDemande<<endl;
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

void RGSC::initialiserCouplesInt() {
	int iter = this->iteration - 1;
	int taille = this->tailles[iter];
	coupleInt cInt;
	this->couplesRestant = taille;
	
	this->couplesInt = new coupleInt [taille];
	cout << "taille["<<iter<<"]=" << taille << endl;
	for (int i = 0; i < taille; ++i) {
		cInt.c1 = i;
		cInt.c2 = -1;
		cInt.indPref = 0;
		cInt.aDemande = false;
		this->couplesInt[i] = cInt;
	}
}

void RGSC::desallouerCouplesInt() {
	delete [] this->couplesInt;
}

bool RGSC::accepteUnion(const coupleInt c1, const coupleInt c2) const {
	int mariActuel = c2.c2;
	
	if (mariActuel == -1) {
		return true;
	} else {
		bool fini = false;
		bool accepte = false;
		int indC2Gauche = c2.c1;
		int indC1Gauche = c1.c1;
		int i = 1;
		int prefCourante;
		
		while (!fini) {
			//~ cout << "preferences["<<indC2Gauche<<"]["<<i<<"].destination"<<endl;
			prefCourante = this->preferences[indC2Gauche][i].destination;
			if (prefCourante == mariActuel) {
				fini = true;
			} else if (prefCourante ==  indC1Gauche) {
				fini = true;
				accepte = true;
			}
			i = i + 1;
		}
		
		return accepte;
	}
}

void RGSC::unir(int indC1, int indC2) { // c1 demande à s'unir avec c2
	coupleInt c1 = this->couplesInt[indC1];
	coupleInt c2 = this->couplesInt[indC2];
	
	if (accepteUnion(c1, c2)) {
		c1.aDemande = true;
		
		if (c1.c2 != -1) {
			this->couplesInt[c1.c2].c2 = -1;
			this->couplesRestant = this->couplesRestant + 2;
		}
		c1.c2 = indC2;
		
		if (c2.c2 != -1) {
			this->couplesInt[c2.c1].c2 = -1;
			this->couplesRestant = this->couplesRestant + 2;
		}
		c2.c1 = indC1;	
		
		this->couplesRestant = this->couplesRestant - 2;
	}
}

void RGSC::marier() {
	this->iteration = this->iteration + 1;
	initialiserCouplesInt();
	
	int i, j;
	int indC2;
	coupleInt cInt1, cInt2;
	
	int nbCouple = this->tailles[this->iteration];
	bool **mariage;
	bool fini = false;
	
	for (i = 0; i < nbCouple; ++i) {
		cInt1 = this->couplesInt[i];
		j = 1;
		indC2 = this->preferences[i][j].destination;
		cInt2 = this->couplesInt[indC2];
		while (!accepteUnion(cInt1, cInt2)) {
			j = j + 1;
		}
		unir(i, this->preferences[i][j].destination);
		cInt1.indPref = j;
	}
	
	//~ this->iteration = this->iteration+1;
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
