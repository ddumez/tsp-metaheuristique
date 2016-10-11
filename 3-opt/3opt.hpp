/**
 * \file 3opt.hpp
 * \brief fonction pour l'operateur 3-opt
 * \author Dorian D. & Jocelin C.
 */

#ifndef 3OPT_HPP
#define 3OPT_HPP

#include "./Distancier/Distancier.hpp"

/**
* \brief améliore la solution actuelle à l'aide du 3-opt
*
* \param[in,out] sol le tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[in,out] zSol la taille de la solution
* \param[out] improved indique si la solution a été amélioré
*/
void ameliorerSol3OPT(int * sol, const Distancier * const dist, int *zSol, bool *improved);

#endif //3OPT_HPP
