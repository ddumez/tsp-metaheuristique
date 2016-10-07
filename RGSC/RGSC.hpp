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

typedef struct couple {
	int v1;
	int v2;
}

using namespace std;

class RGSC {
	// Attributs
		private :
			int nbGroupe;
			couple *couples; /**Les indices des villes qui sont dans le même groupe**/
			// On ne tient compte que des extrémités pour lier les groupes ? (version simple)
			// On tient compte de tous les points de chaque groupe et on peut lier n'importe quels points ?
			//	(version compliquée et pas forcément plus pertinente => nécessite de reconstruire les groupes car on ne revient pas sur ses pas, potentiellement coûteux si sélection du meilleur trajet)
			int **preferences; /**Les préférences des groupes (dans l'ordre décroissant)**/
				// Bien mettre à jour les préférences en fonction de la formation des groupes
};

#endif //RGSC_HPP
