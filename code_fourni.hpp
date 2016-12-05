/**
 * \file code_fourni.hpp
 * \brief algorithmes fournit : nnh et utilitaires
 * \author Dorian D. & Jocelin C. par code de Xavier G.
 */

#ifndef FOURNI_HPP
#define FOURNI_HPP

#include "./Distancier/Distancier.hpp"

/**
* \brief utilise l'heuristique NNH pour construire une solution initiale
*
* \param[in,out] sol tableau qui contien l'ordre de parcours des villes
* \param[in] dist le distancier
*/
void construireSolNNH(int * sol, const Distancier * const dist);

/**
* \brief construit une solution aléatoire
*
* \param[in,out] sol tableau qui contien l'ordre de parcours des villes
* \param[in] dist le distancier
*/
void construireSolAleatoire(int * sol, const Distancier * const dist);

/**
* \brief calcule la taille du circuit
*
* \param[in] sol la solution
* \param[in] dist le distancier
*/
double calculerLongueurCircuitSol(const int * const sol, const Distancier * const dist);

/**
* \brief affiche la solution dans le terminal
*
* \param[in] sol la solution a afficher
* \param[in] dist le distancier (sui contien aussi le nom des villes)
*/
void afficheSol(const int * const sol, const Distancier * const dist);


#endif //FOURNI_HPP
