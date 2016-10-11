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

typedef struct couple {
	int c1;
	int c2;
	int v1;	// Extremitée de C1 qui n'est pas reliée
	int v2;	// Extremitée de C2 qui n'est pas reliée
	double longueur;
} couple;

using namespace std;

class RGSC {
	// Attributs
		private :
			int nbMariage;
			int iteration;
			Distancier *D;
			couple **couples; /**Des couples d'indices, les indices correspondant à ceux de l'itération précédente**/
			int **preferences; /**Les préférences des groupes (dans l'ordre décroissant)**/
			int **extremiteDominante;
			int *tailles;
	
	// Constructeurs
		public :
			RGSC(Distancier *D);
			
	// Destructeur
		public :
			~RGSC();
			
	// AffichageS
		public :
			void afficherPreferences();
	
	// Methodes
		private :
			void allouerCouples();
			void initialiserPreferences();
			void triFusionPreferences(const int i);
			void trierPreferences();
			
		public :
			int getN() const;
			int getDistance(const int v1, const int v2) const;
};



#endif //RGSC_HPP
