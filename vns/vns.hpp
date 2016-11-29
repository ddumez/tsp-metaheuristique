/**
 * \file vns.hpp
 * \brief implementation du vns (en descente et plus profonde descente)
 * \author Dorian D. & Jocelin C.
 */

#ifndef VNS_HPP
#define VNS_HPP

#include "./../Distancier/Distancier.hpp"
#include "./../code_fourni.hpp"
#include "./../3-opt/3opt.hpp"
#include "./../2-opt/2opt.hpp"
#include "./../vnd/vnd.hpp"

/**
* \brief améliore sol en utilisant vns
*
* \param[in] sol la solution sur laquelle on travaille (attention elle n'existera sans doute plus à la fin)
* \param[in] dist les information sur l'instance
* \return la meilleure solution trouve
*/
int * vns(int * sol, const Distancier * const dist);

/**
* \brief selectionne aléatoirement un élément dans le voisinage 2opt de la solution courante
*
* \param[in] sol la solution courante
* \param[in] dist les informations sur l'instances
* \return le voisin selectionne
*/
int * voisindeuxopt(const int * const sol, const Distancier * const dist);

/**
* \brief selectionne aléatoirement un élément dans le voisinage 3opt de la solution courante
*
* \param[in] sol la solution courante
* \param[in] dist les informations sur l'instances
* \return le voisin selectionne
*/
int * voisintroisopt(const int * const sol, const Distancier * const dist);

/**
* \brief améliore sol en utilisant vns en plus profonde descente
*
* \param[in] sol la solution sur laquelle on travaille (attention elle n'existera sans doute plus à la fin)
* \param[in] dist les information sur l'instance
* \return la meilleure solution trouve
*/
int * vnsPPD(int * sol, const Distancier * const dist);

#endif