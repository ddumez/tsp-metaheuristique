/**
 * \file Distancier.hpp
 * \brief Donnees de base utiles à la résolution du TSP (Distancier)
 * \author Dorian D. & Jocelin C.
 */

#ifndef VND_HPP
#define VND_HPP

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"

/**
* \brief applique la meaheuristique vnd sur cette solution
*
* \param[in,out] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
*/
void vnd(int * sol, const Distancier * const dist);

/**
* \brief utilise 2-opt sur sol jusqu'a un min local
*
* \param[in,out] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return si la solution a ete ameliore
*/
bool deuxoptconverge(int * sol, const Distancier * const dist);

/**
* \brief utilise 3-opt sur sol jusqu'a un min local
*
* \param[in,out] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return si la solution a ete ameliore
*/
bool troisoptconverge(int * sol, const Distancier * const dist);

#endif