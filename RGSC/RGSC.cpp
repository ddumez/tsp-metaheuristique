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
	cout << "PREFERENCES" << endl;
	
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
	cout << "COUPLES" << endl;
	
	//~ int i = this->iteration;
	int N = this->tailles[0];
	couple c;
	
	/*for (int i = 0; i < this->nbMariage; ++i) {
		cout << "tailles["<<i<<"]="<<this->tailles[i]<<endl;
	}*/
	
	for (int i = 0; i <= this->iteration; ++i) {
		cout << i << "->" << endl;
		N = this->tailles[i];
		for (int j = 0; j < N; ++j) {
			c = this->couples[i][j];
			cout<<j<<": [c1="<<c.c1<<"|c2="<<c.c2<<"|comp="<<c.compagnon<<"|v1="<<(char)(65+c.v1)<<"|v2="<<(char)(65+c.v2)<<"|ext1="<<(char)(65+c.ext1)<<"|ext2="<<(char)(65+c.ext2)<<"|vDom="<<(char)(65+c.vDom)<<"|indPref="<<c.indPref<<"|longueur="<<c.longueur<<"]"<<endl;
		}
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
	this->nbMariage = 2; // = 0;
	
	this->tailles.push_back(N);
	while (N > 1) {
		this->tailles.push_back(N);
		cout << "N="<<N<<endl;
		if (N%2==0) {
			N = N / 2;
		} else {
			N = (N+1) / 2;
		}
		this->nbMariage = this->nbMariage + 1;
	}
	this->tailles.push_back(N);
	cout << "nbMariage="<< this->nbMariage << endl;
}

void RGSC::initialiserCouples() {
	int nbMariage = this->nbMariage;
	int taille;
	int N = D->getN();
	couple c;
	
	// On alloue toute la mémoire nécessaire
	this->couples = new couple * [nbMariage];
	for (int i = 0; i < nbMariage; ++i) {
		taille = this->tailles[i];
		this->couples[i] = new couple [taille];
		
		// Initialisation des valeurs par défaut
		for (int j = 0; j < taille; ++j) {
			c.c1 = -1;
			c.c2 = -1;
			c.compagnon = -1;
			c.v1 = -1;
			c.v2 = -1;
			c.ext1 = -1;
			c.ext2 = -1;
			c.vDom = -1;
			c.indPref = -1;
			c.longueur = 0;
			this->couples[i][j] = c;
		}
	}
	
	// Initialisation de la première ligne du tableau
	for (int i = 0; i < N; ++i) {
		c.c1 = -1;
		c.c2 = -1;
		c.compagnon = -1;
		c.v1 = -1;
		c.v2 = -1;
		c.ext1 = i;
		c.ext2 = -1;
		c.vDom = -1;
		c.indPref = -1;
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
				//~ cout << "pluProchesV1V2("<<i<<","<<j<<")"<<endl;
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

void RGSC::plusProchesV1V2(const couple c1, const couple c2, int *v1, int *v2, double *shortest) const {
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
		dist = getDistance(v12, v21);
		if (dist < *shortest) {
			*v1 = v12;
			*v2 = v21;
			*shortest = dist;
		}
	}
}

bool RGSC::plusPres(const int depart, const int v1, const int v2) const {
	return (getDistance(depart, v1) < getDistance(depart, v2));
}

void RGSC::unir(int indC1, int indC2, int v1, int v2, double dist) {
	couple c1 = this->couples[this->iteration][indC1];
	couple c2 = this->couples[this->iteration][indC2];
	couple compagnon;
	int avancement = -2; // nombre de sous-couples solitaires ajoutés ou retirés
	
	int c11 = c1.c1;
	int c12 = c1.c2;
	int c21 = c2.c1;
	int c22 = c2.c2;
	
	if (c1.compagnon != -1) {	// si c1 est déjà uni
		compagnon = this->couples[this->iteration][c1.compagnon];
		//~ c1.longueur = c1.longueur - getDistance(c1.vDom, compagnon.vDom);
		compagnon.compagnon = -1;
		compagnon.vDom = -1;
		this->couples[this->iteration][c1.compagnon] = compagnon;
		avancement = avancement + 2;
	}
	if (c2.compagnon != -1) {	// si c2 est déjà uni
		compagnon = this->couples[this->iteration][c2.compagnon];
		//~ c2.longueur = c2.longueur - getDistance(c2.vDom, compagnon.vDom);
		compagnon.compagnon = -1;
		compagnon.vDom = -1;
		this->couples[this->iteration][c2.compagnon] = compagnon;
		avancement = avancement + 2;
	}
	
	c1.compagnon = indC2;
	c2.compagnon = indC1;
	c1.vDom = v1;
	c2.vDom = v2;
	
	this->couples[this->iteration][indC1] = c1;
	this->couples[this->iteration][indC2] = c2;
	this->couplesRestant = this->couplesRestant + avancement;
}

void RGSC::fermerCircuit() {
	couple c1 = this->couples[this->iteration][0];
	couple c2 = this->couples[this->iteration][1];
	int v11, v12, v21, v22;
	v11 = c1.ext1;
	v12 = c1.ext2;
	v21 = c2.ext1;
	v22 = c2.ext2;
	long dist11 = getDistance(c1.ext1, c2.ext1);
	long dist12 = getDistance(c1.ext1, c2.ext2);
	long dist21 = getDistance(c1.ext2, c2.ext1);
	long dist22 = getDistance(c1.ext2, c2.ext2);
	
	if (dist11+dist22 < dist12+dist21) {
		unir(0, 1, v11, v21, dist11);
	} else {
		unir(0, 1, v11, v22, dist12);
	}
	
	initNextIter();
	
	if (dist11+dist22 < dist12+dist21) {
		unir(0, 0, v12, v22, dist22);
	} else {
		unir(0, 0, v12, v21, dist21);
	}
}

void RGSC::marier() {
	int iter = this->iteration;
	int nbSC = this->tailles[iter];
	int indPref, indC1, indC2, v1, v2;
	double dist;
	couple c1, c2;
	bool uni;
	
	while (this->couplesRestant > 1) {
		indC1 = 0;
		while (indC1 < nbSC) {
			c1 = this->couples[iter][indC1];
			indPref = c1.indPref;
			uni = false;
			
			//~ afficherPreferences();
			afficherCouples();

			while ((!uni) && (indPref < nbSC)) {	// Tant que c1 n'est pas relié et qu'on a pas tout essayé
				
				indC2 = this->preferences[indC1][indPref].destination;
				c2 = this->couples[iter][indC2];
				plusProchesV1V2(c1, c2, &v1, &v2, &dist);
				if (c2.compagnon == indC1) {
					uni = true;
				} else if ((c2.compagnon == -1) || (dist < getDistance(c2.vDom, this->couples[iter][c2.compagnon].vDom))) {
					unir(indC1, indC2, v1, v2, dist);
					uni = true;
				} else {
					indPref = indPref + 1;
				}
			}
			if (indPref == nbSC) {
				this->couples[iter][indC1].indPref = 1;
			} else {
				this->couples[iter][indC1].indPref = indPref;
			}
			indC1 = indC1 + 1;
		}
	}
}
void RGSC::initNextIter() {
	int iter = this->iteration;
	int nbSc = this->tailles[iter];
	int j = 0;
	couple c, nouv, compagnon;
	
	for (int i = 0; i < nbSc; ++i) {
		c = this->couples[iter][i];
		if (c.compagnon == -1) {
			//~ cout << "ajout comp -1" << endl;
			//~ cout << "("<<i<<","<<j<<")"<<endl;
			nouv.c1 = i;
			//~ cout << "nouv.c1="<<nouv.c1<<endl;
			nouv.c2 = -1;
			nouv.compagnon = -1;
			nouv.v1 = c.vDom;	/// Ou -1 ?
			nouv.v2 = -1;
			nouv.ext1 = c.ext1;
			nouv.ext2 = c.ext2;
			nouv.vDom = -1;
			nouv.indPref = 1;
			nouv.longueur = c.longueur;
			this->couples[iter+1][j] = nouv;
			j = j + 1;
		} else if (i < c.compagnon) {
			//~ cout << "ajout comp " << c.compagnon << endl;
			//~ cout << "("<<i<<","<<j<<")"<<endl;
			compagnon = this->couples[iter][c.compagnon];
			nouv.c1 = i;
			//~ cout << "nouv.c1="<<nouv.c1<<endl;
			nouv.c2 = c.compagnon;
			nouv.compagnon = -1;
			nouv.v1 = c.vDom;
			nouv.v2 = compagnon.vDom;
			if ((c.ext1 != c.vDom) || (c.ext2 == -1)) {
				nouv.ext1 = c.ext1;
			} else {
				nouv.ext1 = c.ext2;
			}
			if ((compagnon.ext1 != compagnon.vDom) || (compagnon.ext2 == -1)) {
				nouv.ext2 = compagnon.ext1;
			} else {
				nouv.ext2 = compagnon.ext2;
			}
			nouv.vDom = -1;
			nouv.indPref = 1;
			nouv.longueur = c.longueur + compagnon.longueur + getDistance(nouv.v1, nouv.v2);
			this->couples[iter+1][j] = nouv;
			j = j + 1;
		}
	}
	this->couplesRestant = this->tailles[iter+1];
	this->iteration = iter + 1;
}

void RGSC::construireCircuit() {
	for (int i = 3; i < nbMariage; ++i) {
		cout << i << endl;
		initNextIter();
		genererPreferences();
		//~ afficherPreferences();
		marier();
	}
	initNextIter();
	fermerCircuit();
	
	afficherCouples();
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
