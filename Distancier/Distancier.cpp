#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Distancier.hpp"

using namespace std;

//----------------------------------------------------------------------
// CONSTRUCTEURS
//----------------------------------------------------------------------

Distancier::Distancier(const string f) {	
	parser(f);
	
	this->d = new double *[this->N];
	
	for (int i = 0; i < this->N; ++i) {
		this->d[i] = new double[this->N];
		for (int j = 0; j < this->N; ++j) {
			if (i == j) {
				this->d[i][j] = 0;
			} else {
				this->d[i][j] = pythagore(this->c[i], this->c[j]);
			}
		}
	}
}

//----------------------------------------------------------------------
// DESTRUCTEUR
//----------------------------------------------------------------------

Distancier::~Distancier() {
	for (int i = 0; i < this->N; ++i) {
		delete[] this->d[i];
	}
	delete[] this->d;
	delete[] this->c;
	delete[] this->villes;
}

//----------------------------------------------------------------------
// AFFICHAGE
//----------------------------------------------------------------------
void Distancier::afficher() const {
	
	//~ for (int i = 0; i < this->N; ++i) {
		//~ cout << this->villes[i] << "\t";
	//~ }
	
	for (int i = 0; i < this->N; ++i) {
		cout << endl;
		for (int j = 0; j < this->N; ++j) {
			cout << this->d[i][j] << "\t";
		}
	}
	cout << endl;
}

//----------------------------------------------------------------------
// METHODES
//----------------------------------------------------------------------

void Distancier::parser(const string f) {
	// Ouverture du fichier
		ifstream file(f.c_str());
	
	// Si le fichier a pu être ouvert
		if (file.is_open()) {
			string line;
			stringstream sline;
			
		// Connaissance du nombre de villes à visiter
			getline(file, line);
			sline.clear();
			sline.str(line);
			sline >> this->N;
		
		// Initialisation des coordonnées (et des noms des villes)
			this->c = new point[this->N];
			this->villes = new string[this->N];
			
			string x, y;
			int size;
			for (int i = 0; i < this->N; ++i) {
				getline(file, line);
				sline.clear();
				sline.str(line);
				
				sline >> x;
				sline >> y;
				size = x.length() + y.length() + 2;
				line.erase(0, size);
				
				this->c[i].x = atof(x.c_str());
				this->c[i].y = atof(y.c_str());
				this->villes[i] = line;
			}
	// Sinon on renvoie une erreur
		} else {
			cerr << "The file \"" << f << "\" could not be open" << endl;
		}
}

int main() {
	Distancier d(string("../Datas/distancier20.dat"));
	d.afficher();
	return 0;
}
