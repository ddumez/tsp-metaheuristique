#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

#include "Distancier.hpp"

using namespace std;

//----------------------------------------------------------------------
// CONSTRUCTEURS
//----------------------------------------------------------------------

Distancier::Distancier(const string f) {	
	parser(f);
}

//----------------------------------------------------------------------
// DESTRUCTEUR
//----------------------------------------------------------------------

Distancier::~Distancier() {
	
}

//----------------------------------------------------------------------
// AFFICHAGE
//----------------------------------------------------------------------
void Distancier::afficher() const {
	
	for (int i = 0; i < this->N; ++i) {
		cout << this->villes[i] << "\t" << endl;
	}
	
	for (int i = 0; i < this->N; ++i) {
		cout << endl;
		for (int j = 0; j < this->N; ++j) {
			cout << d[i][j] << "\t";
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
				this->villes[i] = line;
				
				cout << x << endl;
				cout << y << endl;
				cout << this->villes[i] << endl << endl;
			}
		
		// Initialisation du distancier
	// Sinon on renvoie une erreur
		} else {
			cerr << "The file " << f << " couldn't be open" << endl;
		}
}

int main() {
	Distancier d(string("../ouest.txt"));
	return 0;
}
