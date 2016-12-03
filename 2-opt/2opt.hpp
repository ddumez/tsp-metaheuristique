/**
 * \file 2opt.hpp
 * \brief algorithme 2opt et 2opt en plus profonde descente
 * \author Dorian D. & Jocelin C. par code de Xavier G.
 */

#ifndef DEUXOPT_HPP
#define DEUXOPT_HPP

#include "./../Distancier/Distancier.hpp"

/**
* \brief améliore la solution actuelle à l'aide du 2-opt
*
* \param[in] sol le tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \return la solution ameliore trouve
*/
int * ameliorerSol2OPT(int * sol, const Distancier * const dist, bool *improved);

/**
* \brief améliore la solution actuelle à l'aide du 2-opt en plus profonde descence
*
* \param[in] sol le tableau qui contien l'ordre de parcour des villes, après la meileure solution dans le voisinage
* \param[in] dist le distancier
* \param[out] improved indique si la solution a été amélioré
* \return la solution ameliore trouve
*/
int * ameliorerSol2OptPPD(int * sol, const Distancier * const dist, bool *improved);

#endif