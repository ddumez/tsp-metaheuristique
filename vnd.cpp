#include <iostream>

#include "vnd.hpp"

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"

using namespace std;

int * vnd(int * sol, const Distancier * const dist) {
	bool improved;
	do {
		sol = deuxoptconverge(sol, dist);
		sol = ameliorerSol3OPT( sol, dist, &improved);
	} while (improved);
	return sol;
}

int * deuxoptconverge(int * sol, const Distancier * const dist) {
	bool improved;
	do{
		sol = ameliorerSol2OPT(sol, dist, &improved);
	} while (improved);
    return sol;
}

int * troisoptconverge(int * sol, const Distancier * const dist) {
	bool improved;
	do{
		sol = ameliorerSol3OPT(sol, dist, &improved);
    } while (improved);
	return sol;
}

int * vndPPD(int * sol, const Distancier * const dist) {
	bool improved;
	do {
		sol = deuxoptPPDconverge(sol, dist);
		sol = ameliorerSol3OptPPD(sol, dist, &improved);
	} while (improved);
	return sol;
}

int * deuxoptPPDconverge(int * sol, const Distancier * const dist) {
	bool improved;
	do{
		sol = ameliorerSol2OptPPD(sol, dist, &improved);
    } while (improved);
    return sol; 
}

int * troisoptPPDconverge(int * sol, const Distancier * const dist) {
	bool improved;
	do{
		sol = ameliorerSol3OptPPD(sol, dist, &improved);
    } while (improved);
	return sol;
}