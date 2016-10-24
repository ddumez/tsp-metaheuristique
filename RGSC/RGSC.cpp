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
	//~ genererPreferences();
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
		cout<<i<<": "<<endl;
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
	
	for (int i = 0; i < this->nbMariage; ++i) {
		cout << "tailles["<<i<<"]="<<this->tailles[i]<<endl;
	}
	
	for (int j = 0; j < N; ++j) {
		c = this->couples[i][j];
		cout<<j<<": [c1="<<c.c1<<"|c2="<<c.c2<<"|v1="<<c.v1<<"|v2="<<c.v2<<"|ext1="<<c.ext1<<"|ext2="<<c.ext2<<"|indPref="<<c.indPref<<"|longueur="<<c.longueur<<"]"<<endl;
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
	
	while (N > 1) {
		tailles.push_back(N);
		if (N%2==0) {
			N = N / 2;
		} else {
			N = (N+1) / 2;
		}
		this->nbMariage = this->nbMariage + 1;
	}
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
	this->preferences.clear();
	
	int nbSC = this->tailles[this->iteration];	// nombre de sous-couple
	couple c1, c2;
	preference p;
	int v1, v2;
	double distance;
	
	for (int i = 0; i < nbSC; ++i) {
		c1 = this->couples[this->iteration][i];
		this->preferences.push_back(vector<preference>());
		for (int j = 0; j < nbSC; ++j) {
			//~ if (i != j) {
				c2 = this->couples[this->iteration][j];
				plusProchesV1V2(c1, c2, &v1, &v2, &distance);
				p.distance = distance;
				p.v1 = v1;
				p.v2 = v2;
				p.destination = j;
				this->preferences.at(i).push_back(p);
			//~ }
		}
	}
	trierPreferences();
}

void RGSC::trierPreferences() {
	int nbSC = this->tailles[iteration];	// nombre de sous-couple
	preference prefJ1, prefJ0;
	bool fini;
	
	// Pour chaque ville
	for (int i = 0; i < nbSC; ++i) {
		// Tant que le tableau n'est pas trié
		do {
			fini = true;
			prefJ0 = this->preferences.at(i).at(0);
			for (int j = 0; j < nbSC; j++) {
				prefJ1 = this->preferences.at(i).at(j);
				if (prefJ1.distance < prefJ0.distance) {
					this->preferences.at(i).at(j-1) = prefJ1;
					this->preferences.at(i).at(j) = prefJ0;
					fini = false;
				} else {
					prefJ0 = prefJ1;
				}
			}
		} while (!fini);
	}
}

// Renvoie le nombre de sous-couples à marier en plus ou en moins si union (-2, -1, 0, 1, 2)
int RGSC::plusProchesV1V2(const couple c1, const couple c2, int *v1, int *v2, double *shortest) const {
	int cas = -2;
	int v11, v12, v21, v22;
	double dist;
	v11 = c1.ext1;
	v12 = c1.ext2;
	v21 = c2.ext1;
	v22 = c2.ext2;
	
	*v1 = v11;
	*v2 = v21;
	*shortest = getDistance(v11, v21);
	
	if (v22 != -1) {
		cas = cas + 2;
		dist = getDistance(v11, v22);
		if (dist < *shortest) {
			*v2 = v22;
			*shortest = dist;
		}
		
		if (v12 != -1) {
			dist = getDistance(v12, v22);
			if (dist < *shortest) {
				*v1 = v12;
				*v2 = v22;
				*shortest = dist;
			}
		}
	}
	
	if (v12 != -1) {
		cas = cas + 2;
		dist = getDistance(v12, v21);
		if (dist < *shortest) {
			*v1 = v12;
			*v2 = v21;
			*shortest = dist;
		}
	}
	return cas;
}

double RGSC::getDistance(const couple c1, const couple c2) const {
	int v1, v2, v11, v12, v21, v22;
	double dist, shortest;
	v11 = c1.ext1;
	v12 = c1.ext2;
	v21 = c2.ext1;
	v22 = c2.ext2;
	
	v1 = v11;
	v2 = v21;
	shortest = getDistance(v11, v21);
	
	if (v22 != -1) {
		dist = getDistance(v11, v22);
		if (dist < shortest) {
			v2 = v22;
			shortest = dist;
		}
		
		if (v12 != -1) {
			dist = getDistance(v12, v22);
			if (dist < shortest) {
				v1 = v12;
				v2 = v22;
				shortest = dist;
			}
		}
	}
	
	if (v12 != -1) {
		dist = getDistance(v12, v21);
		if (dist < shortest) {
			v1 = v12;
			v2 = v21;
			shortest = dist;
		}
	}
	return shortest;
}

bool RGSC::plusPres(const int depart, const int v1, const int v2) const {
	return (getDistance(depart, v1) < getDistance(depart, v2));
}

bool RGSC::accepteUnion(const couple c1, const couple c2) const {
	// c1 n'est pas marié ou alors c2 est plus proche que son sous-couple actuel
	bool accepte = (c1.c2 == -1);
	
	if (!accepte) {
		couple c3 = this->couples[this->iteration][c1.c2];
		accepte = getDistance(c1,c2) < getDistance(c1,c3);
	}
	
	return accepte;
}

void RGSC::unir(int indC1, int indC2) {
	couple c1 = this->couples[this->iteration][indC1];
	couple c2 = this->couples[this->iteration][indC2];
	
}

void RGSC::unir(int indC1, int indC2, int v1, int v2, double dist) {
	cout << "iter = " << this->iteration << endl;
	couple c1 = this->couples[this->iteration][indC1];
	couple c2 = this->couples[this->iteration][indC2];
	
	// RENDU ICI
	
	if (c1.v2 == -1) {
		
	}
	c1.v2 = v1;
	c1.v2 = v2;
}

void RGSC::marier() {
	genererPreferences();
	int nbSC = this->tailles[this->iteration];
	int cas;
	this->couplesRestant = nbSC;
	int indPref, indC2;
	int *v1, *v2;
	double *dist;
	couple c1, c2, c3;
	bool fini;
	
	// Tout le monde fait une première demande
	for (int i = 0; i < nbSC; ++i) {
		c1 = this->couples[this->iteration][i];
		indPref = 0;
		
		while ((indPref < nbSC) && (!fini)){	// Si on a pas tout testé et qu'on a pas trouvé de solution
			indC2 = this->preferences[i][indPref].destination;
			c2 = this->couples[this->iteration][indC2];
			cas = plusProchesV1V2(c1, c2, v1, v2, dist);
			if ((c1.v2 == -1) || (*dist < getDistance(c1.v1, c1.v2))) {
				unir(i, indC2, *v1, *v2, *dist);
				this->couplesRestant = this->couplesRestant + cas;
			} else {
				indPref = indPref + 1;
			}
		}
	}
	
	this->iteration = this->iteration + 1;
}

void RGSC::construireCircuit() {
	marier();
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
