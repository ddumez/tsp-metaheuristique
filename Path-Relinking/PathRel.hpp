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
* \brief Cherche une meilleure solution en comparant le voisinage (tous les swaps possibles) entre deux solutions
* Il exclue les swaps nous éloignant de la solution objectif.
* \param[in] solA le tableau qui contient l'ordre de parcours des villes de la solution de départ
* \param[in] solB le tableau qui contient l'ordre de parcours des villes de la solution d'arivée
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \return la solution a laquelle on a aboutit
*/
int * pathRelinking(int *solA, int *solB, const Distancier * const dist, bool *improved);

/**
* \brief Cherche une meilleure solution en comparant le voisinage (tous les swaps possibles) entre deux solutions
* Il favorise les swaps qui améliore le plus la solution ou empire le moins la solution courante.
* \param[in] solA le tableau qui contient l'ordre de parcours des villes de la solution de départ
* \param[in] solB le tableau qui contient l'ordre de parcours des villes de la solution d'arivée
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \return la solution a laquelle on a aboutit
*/
int * pathRelinkingSelect(int *solA, int *solB, const Distancier * const dist, bool *improved);

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
* \brief Cherche une meilleure solution en comparant les voisinages entre deux solutions
* Cet algorithme se permet de construire des solutions non réalisables pour les reconstruire
* Il favorise les insertions qui diminuent le plus distance de la solution sans regarder la faisabilité
* \param[in] solA le tableau qui contient l'ordre de parcours des villes de la solution de départ
* \param[in] solB le tableau qui contient l'ordre de parcours des villes de la solution d'arivée
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \param[in] n, nombre de permutations avant reconstruction de la solution
* \return la solution a laquelle on a aboutit
*/
int * pathRelinkingReconstrSelect(int *solA, int *solB, const Distancier * const dist, bool *improved, int N);

/**
 * \brief Calcule la différence de la longueur de la solution après un échange
 * \param[in] sol le tableau qui contient l'ordre de parcours des villes de la solution
 * \param[in] dist le distancier
 * \param[in] i la position de la première ville à échanger
 * \param[in] j la position de la seconde ville à échanger
 * \return la différence de z de la solution après l'échange
 */
double deltaSwap(int *sol, const Distancier * const dist, int i, int j);


/**
 * \brief Calcule la différence de la longueur de la solution après insertion d'une ville à l'indice i
 * Souvent, après une insertion la solution n'est plus admissible
 * \param[in] sol le tableau qui contient l'ordre de parcours des villes de la solution
 * \param[in] dist le distancier
 * \param[in] i la position de l'insertion à effectuer
 * \param[in] v la ville à insérer à l'emplacement i
 * \return la différence de z de la solution après insertion
 */
double deltaInsertion(int *sol, const Distancier * const dist, int i, int v);

/**
 * \brief Répare la solution non admissible
 */
double reparerSolution( int *sol, int *solB, const Distancier *const dist, int *doubles, int * absents, int nb);

#endif //PATHREL_HPP
