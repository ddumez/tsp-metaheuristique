/**
 * \file grasp.hpp
 * \brief algorithme du GRASP
 * \author Dorian D. & Jocelin C.
 */

#ifndef GRASP_HPP
#define GRASP_HPP

#include "./../Distancier/Distancier.hpp"
#include "./../Path-Relinking/PathRel.hpp"
#include "./../code_fourni.hpp"
#include "./../2-opt/2opt.hpp"
#include "./../3-opt/3opt.hpp"
#include "./../vnd/vnd.hpp"
#include "./../vns/vns.hpp"

/**
* \brief construit une solution suivant le nnh avec l'acceptation a
*
* \param[in,out] sol tableau qui contien l'ordre de parcours des villes
* \param[in] dist le distancier
* \param[in] a le taux d'acceptation
*/
void construireSolNNHrand(int * sol, const Distancier * const dist, const double a);

/**
* \brief utilise l'algorithme de grasp
*
* \param[in] dist les informations sur l'instance
* \param[in] alpha la parametre de control de l'aleatoire de grasp
* \return la meilleure solution trouve
*/
int * grasp(const Distancier * const dist, const double alpha);

/**
* \brief utilise l'algorithme reactive grasp
*
* \param[in] dist les informations sur l'instance
* \return la meilleure solution trouve
*/
int * reacgrasp(const Distancier * const dist);


#endif