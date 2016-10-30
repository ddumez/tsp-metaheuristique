/**
 * \file 3opt.hpp
 * \brief fonction pour l'operateur 3-opt
 * \author Dorian D. & Jocelin C.
 */

#ifndef TROISOPT_HPP
#define TROISOPT_HPP

#include "../Distancier/Distancier.hpp"

/**
* \brief améliore la solution actuelle à l'aide du 3-opt
*
* \param[in,out] sol le tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[in,out] zSol la taille de la solution
* \param[out] improved indique si la solution a été amélioré
*/
void ameliorerSol3OPT(int * sol, const Distancier * const dist, bool *improved);

/**
* \brief améliore la solution actuelle à l'aide du 3-opt en plus profonde descente
*
* \param[in,out] sol le tableau qui contien l'ordre de parcour des villes
* \param[in] dist le distancier
* \param[in,out] zSol la taille de la solution
* \param[out] improved indique si la solution a été amélioré
*/
void ameliorerSol3OptPPD(int * sol, const Distancier * const dist, bool *improved);


/**
* \brief inverse le sens du parcour entre les etapes i et j
*
* \param[in,out] sol la solution a modifie
* \param[in] i le debut de la portion a inverser
* \param[in] j la fin de la portion a inverser
* \param[in] n le nombre de ville
*/
void inverseSens(int * sol, const int i, const int j, const int n);

#endif //3OPT_HPP
