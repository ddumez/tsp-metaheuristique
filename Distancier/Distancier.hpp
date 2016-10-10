/**
 * \file Distancier.hpp
 * \brief Donnees de base utiles à la résolution du TSP (Distancier)
 * \author Dorian D. & Jocelin C.
 */

#ifndef DISTANCIER_HPP
#define DISTANCIER_HPP

#include <string>
#include <cmath>

using namespace std;

typedef struct point {
	double x;
	double y;
} point;

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
			
	// Affichages
		public :
			/**
			 * \brief Affiche le distancier
			 */
			void afficher() const;
			
	// Methodes
		public :
			/**
			* \brief donne la distance entre la ville i et la ville j
			*
			* \param[in] i l'indice de la première ville
			* \param[in] j l'indice de la deuxieme ville
			* \return la distance euclidienne entre i et j
			*/
			double getdistance(const int i, const int j) const;

			/**
			* \brief donne le nombre de ville
			*
			* \return le nombre de ville dans le distancier
			*/
			int getN() const;
			
			/**
			* \brief affiche le nom de la i eme ville
			*
			* \param[in] i le numero de la ville a afficher
			*/
			void affichevillei (const int i) const;
		private :
			/**
			 * \brief Lit un fichier pour initialiser les coordonnées du
			 * distancier et le nom des villes (utilisé dans le constructeur)
			 * \param f Le nom du fichier dans lequel les données sont lues
			 * \ref Distancier::Distancier()
			 */
			void parser(const string f);
			
			/**
			* \brief calcule la distance euclidienne entre a et b
			*
			* \param[in] a le premier point
			* \param[in] b le deuxieme point
			* \return la distance euclidienne entre a et b
			*/
			static double pythagore(const point a, const point b);

};

#endif //DISTANCIER_HPP
