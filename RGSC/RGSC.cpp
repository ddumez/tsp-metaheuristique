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
	for (int i = 0; i < this->tailles[this->iteration-1]; ++i) {
		c = this->couplesInt[i];
		cout << i <<":\t"<<c.c1<< " | "<<c.c2<<"\tpref="<<c.indPref<<"\taDemande="<<c.aDemande<<" aCopie="<<c.estCopie<<endl;
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
		c.longueur = 0;
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

void RGSC::creerPreferencesCouples() {
	//int N = this->D
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
		cInt.estCopie = false;
		this->couplesInt[i] = cInt;
	}
}

void RGSC::desallouerCouplesInt() {
	delete [] this->couplesInt;
}

bool RGSC::accepteUnion(const coupleInt c1, const coupleInt c2) const {
	int mariActuel = c2.c2;
	
	if ((mariActuel == -1) || (mariActuel == c1.c1)) {
		return true;
	} else {
		bool fini = false;
		bool accepte = false;
		int indC2Gauche = c2.c1;
		int indC1Gauche = c1.c1;
		int i = 1;
		int prefCourante;
		
		while (!fini) {
			//cout << "preferences["<<indC2Gauche<<"]["<<i<<"].destination"<<endl;
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
	
	c1.aDemande = true;

	if (c2.c2 == c1.c1) {	// S'ils sont déjà mariés ensemble on passe
		c1.aDemande = 1;
	} else {				// Sinon on regarde comment les marier
		if (c1.c2 != -1) {	// Si c1 est déjà en couple
			this->couplesInt[c1.c2].c2 = -1;
			this->couplesRestant = this->couplesRestant + 1;
		} else {
			this->couplesRestant = this->couplesRestant - 1;
		}
		c1.c2 = indC2;

		if (c2.c2 != -1) {
			this->couplesInt[c2.c2].c2 = -1;
			this->couplesRestant = this->couplesRestant + 1;
		} else {
			this->couplesRestant = this->couplesRestant - 1;
		}
		c2.c2 = indC1;
	}
	
	this->couplesInt[indC1] = c1;
	this->couplesInt[indC2] = c2;
}

// Place les couples temporaires dans les nouveaux couples
void RGSC::sauvegarderCouples() { cout << "COCO" <<endl;
	int iter = this->iteration;				// L'itération qui vient d'être calculée
	int nbCouple = this->tailles[iter];		// Le nombre de couples créés
	int i = 0;
	int n = 0;
	coupleInt cInt;
	couple c;
	int v1, v2, v11, v12, v21, v22;
	double dist, dist2;
	
	while (n < nbCouple) {
		cInt = this->couplesInt[i];
		
		if (cInt.c2 == -1) {
			this->couples[iter][i] = this->couples[iter-1][i];
			n = n + 1;
		} else if (cInt.c1 < cInt.c2) {
			c.c1 = cInt.c1;
			c.c2 = cInt.c2;
			
			
			// Debut truc dégueulasse à faire dans sa propre fonction ou trouver un autre moyen de le faire
			v11 = this->couples[iter-1][c.c1].v1;
			v12 = this->couples[iter-1][c.c1].v2;
			v21 = this->couples[iter-1][c.c2].v1;
			v22 = this->couples[iter-1][c.c2].v2;
			v1 = v11;
			v2 = v21;
			
			cout << "v11 "<<v11<<"\tv12 "<<v12<<"\tv21 "<<v21<<"\tv22 "<<v22<<endl;
			
			dist = getDistance(v11, v21);
			
			if ((v22 != -1) && (getDistance(v11, v22) < dist)) {	// Si d(v11, v22) < d(v11, v21)
				dist = getDistance(v11, v22);
				v2 = v22;
			}
			
			if ((v12 != -1) && (getDistance(v12, v21) < dist)) { // Si d(v12, v21) < MIN(d(v11, v21), d(v11, v22))
				dist = getDistance(v12, v21);
				v1 = v12;
				v2 = v21;
			}
			
			if ((v12 != -1) && (v22 != -1) && (getDistance(v12, v22) < dist)) {	// Si d(v12, v22) est inférieure aux autres
				dist = getDistance(v12, v22);
				v1 = v12;
				v2 = v22;
			}
			// Fin truc dégueulasse
			
			
			c.v1 = v1;
			c.v2 = v2;
			c.longueur = dist + this->couples[iter-1][c.c1].longueur + this->couples[iter-1][c.c2].longueur;
			
			this->couples[iter][n] = c;
			
			n = n + 1;
		}
		i = i + 1;
	}
	delete [] this->couplesInt;
}

void RGSC::construireCircuit() {
	marier();
	sauvegarderCouples();
	//~ marier();
	//~ sauvegarderCouples();
}

void RGSC::marier() {
	this->iteration = this->iteration + 1;
	initialiserCouplesInt();
	
	int i, j;
	int indC2;
	coupleInt cInt1, cInt2;
	
	int nbCouple = this->tailles[this->iteration-1];
	//~ bool **mariage;
	bool fini = false;
	
	/// Tout le monde fait une demande
	for (i = 0; i < nbCouple; ++i) {
		afficherCouplesInt();
		cInt1 = this->couplesInt[i];
		j = 1;
		indC2 = this->preferences[i][j].destination;
		cInt2 = this->couplesInt[indC2];
		while (!accepteUnion(cInt1, cInt2) && (j < nbCouple)) {
			cout << "pas d'union " << cInt1.c1 << " - " << cInt2.c1 << endl;
			
			j = j + 1;
			indC2 = this->preferences[i][j].destination;
			cInt2 = this->couplesInt[indC2];
		}
		if (j < nbCouple) {
			cout << "unir " << cInt1.c1 << " - " << cInt2.c1 << endl;
			unir(i, this->preferences[i][j].destination);
			this->couplesInt[i].indPref = j;
		}
		
		//~ afficherCouplesInt();
	}
	
	cout << endl << "SECOND PART : " << this->couplesRestant << endl;
	
	/// Ceux qui ont perdu leur couple font une nouvelle demande jusqu'à ce qu'un couple au plus soit non uni
	while (this->couplesRestant > 1) {	// On recommence s'il reste plus d'un couple
		i = 0;
		
		while (i < nbCouple) {	// On les marie dans l'ordre tant qu'il reste plus d'un couple
		cInt1 = this->couplesInt[i];
		cout << i << ": couplesRestant = " << this->couplesRestant << endl;
			
			if (cInt1.c2 == -1) {	// unir c1 avec le prochain de sa lite s'il n'est pas déjà en couple
				j = cInt1.indPref + 1;
				indC2 = this->preferences[i][j].destination;
				cInt2 = this->couplesInt[indC2];
				
				while (!accepteUnion(cInt1, cInt2) && (j < nbCouple)) {
					cout << "pas d'union " << cInt1.c1 << " - " << cInt2.c1 << endl;
					
					j = j + 1;
					indC2 = this->preferences[i][j].destination;
					cInt2 = this->couplesInt[indC2];
				}
				if (j < nbCouple) {
					cout << "unir " << cInt1.c1 << " - " << cInt2.c1 << endl;
					afficherCouplesInt();
					unir(i, this->preferences[i][j].destination);
					cInt1.indPref = j;
				}
			}
			i = i + 1;
		}
	}
}

int RGSC::getN() const {
	return this->D->getN();
}

double RGSC::getDistance(const int v1, const int v2) const {
	return D->getDistance(v1, v2);
}
