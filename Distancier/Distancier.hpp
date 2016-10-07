/**
 * \file Distancier.hpp
 * \brief Donnees de base utiles à la résolution du TSP (Distancier)
 * \author Dorian D. & Jocelin C.
 */

#ifndef DISTANCIER_HPP
#define DISTANCIER_HPP

using namespace std;

typedef struct point {
	double x;
	double y;
} point;

double pythagore(const point a, const point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

class Distancier {
	// Attributs
		private :
			int N;				/**Le nombre de villes*/
			string *villes;		/**Les noms des villes*/
			point *c;			/**Les coordonnées des villes*/
			double **d;			/**Les distances entre chaque paire de villes*/
			
	// Constructeurs
		public :
			/**
			 * \brief Construit et initialise les données du problème
			 * \ref Distancier::parser()
			 * \param f Le nom du fichier dans lequel les données sont lues
			 */
			Distancier(const string f);
			
	// Deconstructeur
		public :
			/**
			 * \brief Désalloue toute la mémoire allouée
			 */
			~Distancier();
			
	// Affichage
		public :
			/**
			 * \brief Affiche le distancier
			 */
			void afficher() const;
			
	// Methodes
		public :
			
		private :
			/**
			 * \brief Lit un fichier pour initialiser les coordonnées du
			 * distancier et le nom des villes (utilisé dans le constructeur)
			 * \param f Le nom du fichier dans lequel les données sont lues
			 * \ref Distancier::Distancier()
			 */
			void parser(const string f);
};

#endif //DISTANCIER_HPP
