/**
 * \file code fournit.hpp
 * \brief algorithmes fournit : nnh et 2-opt
 * \author Dorian D. & Jocelin C. par code de Xavier G.
 */

#include "./Distancier/Distancier.hpp"

#ifndef FOURNIT_HPP
#define FOURNIT_HPP

/**
* \brief utilise l'heuristique NNH pour construire une solution initiale
*
* \param[in,out] sol tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[out] zSol taille de la solution trouvé
*/
void construireSolNNH(int * sol, const Distancier const * dist, int *zSol);

/**
* \brief calcule la taille du circuit
*
* \param[in] sol la solution
* \param[in] dist le distancier
*/
int calculerLongueurCircuitSol(const int * sol, const Distancier const * dist);

/**
* \brief améliore la solution actuelle à l'aide du 2-opt
*
* \param[in,out] sol le tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[in,out] zSol la taille de la solution
* \param[out] improved indique si la solution a été amélioré
*/
void ameliorerSol2OPT(int * sol, const Distancier const * dist, int *zSol, bool *improved);


#endif //FOURNIT_HPP