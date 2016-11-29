/**
 * \file vnd.hpp
 * \brief implemente le vnd et les methodes de descenete a un seul operateurs
 * \author Dorian D. & Jocelin C.
 */

#ifndef VND_HPP
#define VND_HPP

#include "./../Distancier/Distancier.hpp"
#include "./../code_fourni.hpp"
#include "./../3-opt/3opt.hpp"
#include "./../2-opt/2opt.hpp"

/**
* \brief applique la meaheuristique vnd sur cette solution
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \retunr la meilleure solution trouve par vnd
*/
int * vnd(int * sol, const Distancier * const dist);

/**
* \brief utilise 2-opt sur sol jusqu'a un min local
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return la meilleure solution trouve par une succession de 2opt
*/
int * deuxoptconverge(int * sol, const Distancier * const dist);

/**
* \brief utilise 3-opt sur sol jusqu'a un min local
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return la meillure solution trouve
*/
int * troisoptconverge(int * sol, const Distancier * const dist);

/**
* \brief applique la meaheuristique vnd sur cette solution
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return la meilleure solution trouve
*/
int * vndPPD(int * sol, const Distancier * const dist);

/**
* \brief utilise 2-opt sur sol jusqu'a un min local
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return la meillure solution trouve
*/
int * deuxoptPPDconverge(int * sol, const Distancier * const dist);

/**
* \brief utilise 3-opt sur sol jusqu'a un min local
*
* \param[in] sol la solution sur laquelle on travaille
* \param[in] dist le distancier
* \return la meilleure solution trouve
*/
int * troisoptPPDconverge(int * sol, const Distancier * const dist);

#endif
