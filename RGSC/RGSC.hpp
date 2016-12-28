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
	int c1;	/*!<Indice du premier couple marié dans l'itération précédente */
	int c2; /*!<Indice du deuxième couple marié dans l'itération précédente */
	int compagnon; /*!<Indice dans l'itération actuelle (en cours de construction) du couple avec lequel il est uni*/
	int v1;	/*!<Ville de C1 qui est reliée */
	int v2;	/*!<Ville de C2 qui est reliée */
	int ext1; /*!<Extremitée de C1 qui n'est pas reliée */
	int ext2; /*!<Extremitée de C2 qui n'est pas reliée */
	int vDom; /*!<Ville la plus proche du compagnon */
	int indPref; /*!<L'indice de la dernière préférence de sa liste à laquelle il a fait une demande d'union. */
	double longueur;
} couple;

typedef struct preference {
	int destination;			/*!<indice du couple vers lequel on se dirige */
	double distance;
	int v1;		/*!<indice de la ville de C1 la plus proche du couple C2*/
	int v2;		/*!<indice de la ville de C2 la plus proche du couple C1*/
} preference;

typedef struct voisins {
	int v1;
	int v2;
} voisins;

using namespace std;

class RGSC {
	// Attributs
		private :
			int nbMariage;
			int iteration;
			int couplesRestant;
			Distancier *D;
			couple **couples; /*!<Des couples d'indices, les indices correspondant à ceux de l'itération précédente**/
			vector<vector<preference> > preferences; /*!<Les préférences des groupes (dans l'ordre décroissant)**/
			vector<int> tailles;
	
	// Constructeurs
		public :
			RGSC(Distancier *D);
			
	// Destructeur
		public :
			~RGSC();
			
	// Affichages
		public :
			void afficherPreferences();
			void afficherPreferences(const int i);
			void afficherCouplesRecursif();
			void afficherCouples();
			void afficherCouples(const int i);
			void afficherVoisinages();
	
	// Methodes
		private :
			/*! Calcule la liste des tailles (nombre de couples) de chaque itération */
			void calculerTailles();
			/*! Alloue la mémoire et initialise la première itération*/
			void initialiserCouples();
			/*! Crée la liste triée par ordre croissant des distances de chaque sous-couple avec les autres*/
			void genererPreferences();
			/*! Trie la liste des préférences */
			void trierPreferences();
			/*! Renvoie vrai si dist(depart,v1) < dist(depart,v2)*/
			bool plusPres(const int depart, const int v1, const int v2) const;
			/*! Calcule la distance de c1 à c2 et insère dans v1 et v2 les villes les plus proches des deux sous-couples*/
			void plusProchesV1V2(const couple c1, const couple c2, int *v1, int *v2, double *dist) const;
			/*! Relie les deux sous-couples aux indices indC1 et indC2 par les villes v1 et v2*/
			void unir(int indC1, int indC2, int v1, int v2, double dist);
			/*! Une fois tous les sous-couples liés, initialise l'itération suivante*/
			void initNextIter();
			/*! Ferme le circuit trouvé de manière à créer une solution tsp-admissible*/
			void fermerCircuit();
			/*! Relie les sous-couples selon l'algorithme décrit dans le rapport*/
			void marier();
			/*! Insère dans sol la solution trouvée par l'algorithme*/
			void deroulerSolution(int *sol) const;
			/*! Désalloue les couples*/
			void deleteCouples();
			
		public :
			int getN() const;
			double getDistance(const int v1, const int v2) const;
			/*! Appelle la méthode marier() jusqu'à ce qu'il n'y ai plus qu'un couple et ferme le circuit*/
			void construireCircuit(int *sol);
			double getDistance(const couple c1, const couple c2) const;
};



#endif //RGSC_HPP
