/**
 * \file PathRel.hpp
 * \brief Classe implémentant le path relinking
 * 
 * \author Dorian D. & Jocelin C.
 */
 
#ifndef PATHREL_HPP
#define PATHREL_HPP

#include "../Distancier/Distancier.hpp"

/**
* \brief Cherche une meilleure solution en comparant les voisinages entre deux solutions
*
* \param[in] solA le tableau qui contient l'ordre de parcours des villes de la solution de départ
* \param[in] solB le tableau qui contient l'ordre de parcours des villes de la solution d'arivée
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \return la solution a laquelle on a aboutit
*/
int * pathRelinking(int *solA, int *solB, const Distancier * const dist, bool *improved);

/**
* \brief Cherche une meilleure solution en comparant les voisinages entre deux solutions
* Cet algorithme se permet de construire des solutions non réalisables pour les reconstruire
* \param[in] solA le tableau qui contient l'ordre de parcours des villes de la solution de départ
* \param[in] solB le tableau qui contient l'ordre de parcours des villes de la solution d'arivée
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \param[in] n, nombre de permutations avant reconstruction de la solution
* \return la solution a laquelle on a aboutit
*/
int * pathRelinkingReconstr(int *solA, int *solB, const Distancier * const dist, bool *improved, int N);

/** 
 */
double deltaSwap(int *sol, const Distancier * const dist, int i, int j);

#endif //PATHREL_HPP
