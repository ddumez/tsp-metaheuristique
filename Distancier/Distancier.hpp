/**
 * \file Distancier.hpp
 * \brief Donnees de base utiles à la résolution du TSP (Distancier)
 * \author Dorian D. & Jocelin C.
 */

#ifndef DISTANCIER
#define DISTANCIER

using namespace std;

typedef struct point {
	double x;
	double y;
} point;

class Distancier {
	// Attributs
		private :
			int N;				// Le nombre de villes
			string *villes;		// Les noms des villes
			point *c;			// Les coordonnées des villes
			int **d;			// Les distances entre chaque paire de villes
			
	// Constructeurs
		public :
			Distancier(const string f);
			
	// Deconstructeur
		public :
			~Distancier();
			
	// Affichage
		public :
			void afficher() const;
			
	// Methodes
		public :
			
		private :
			void parser(const string f);
};

#endif //DISTANCIER
