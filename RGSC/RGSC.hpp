/**
 * \file RGSC.hpp
 * \brief Données utilisées pour la résolution à l'aide de l'heuristique RGSC
 * La méthode RGSC est une méthode que nous avons imaginée en nous inspirant de
 * "l'algorithme des mariages stables" proposé par David Gale et Lloyd Shapley
 * Nous avons ainsi nommé l'algorithme en leur honneur :
 * "Recursive Gale-Shapley Circuit"
 * 
 * Cet algorithme créé des couples de points à l'aide de l'algorithme du mariage
 * stable dont les préférences sont triées selon les distances entre les points
 * Nous répétons ensuite l'opération pour lier les couples de points entre eux
 * (ou un couple avec un éventuel point isolé dans le cas de N impair)
 * Puis nous répétons l'opération avec les quadruplets (ou triplets ou couples potentiellement)
 * Et ainsi de suite jusqu'à complètement fermer le circuit
 * 
 * \author Dorian D. & Jocelin C.
 */

#ifndef RGSC_HPP
#define RGSC_HPP

#include "../Distancier/Distancier.hpp"
#include <vector>

typedef struct couple {
	int c1;	// Premier couple marié
	int c2; // Deuxième couple marié
	int v1;	// Extremitée de C1 qui n'est pas reliée
	int v2;	// Extremitée de C2 qui n'est pas reliée
	double longueur;
} couple;

typedef struct preference {
	int destination;		// indice du couple vers lequel on se dirige
	int extremiteDominante;
} preference;

using namespace std;

class RGSC {
	// Attributs
		private :
			int nbMariage;
			int iteration;
			Distancier *D;
			couple **couples; /**Des couples d'indices, les indices correspondant à ceux de l'itération précédente**/
			vector<vector<preference> > preferences; /**Les préférences des groupes (dans l'ordre décroissant)**/
			vector<int> tailles;
			
			int iterationSort;
	
	// Constructeurs
		public :
			RGSC(Distancier *D);
			
	// Destructeur
		public :
			~RGSC();
			
	// AffichageS
		public :
			void afficherPreferences();
			void afficherPreferences(const int i);
			void afficherCouples();
			void afficherCouples(const int i);
	
	// Methodes
		private :
			void calculerTailles();
			void initialiserCouples();
			void initialiserPreferences();
			void triPreferences();
			bool plusPres(const int depart, const int v1, const int v2) const;
			void marier();
			
		public :
			int getN() const;
			double getDistance(const int v1, const int v2) const;
};



#endif //RGSC_HPP
