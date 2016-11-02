#include <iostream>

#include "vnd.hpp"

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"

using namespace std;

void vnd(int * sol, const Distancier * const dist) {
	bool improved = true;
	do {
		deuxoptconverge(sol, dist);
		ameliorerSol3OPT( sol, dist, &improved);
	} while (improved);
}

bool deuxoptconverge(int * sol, const Distancier * const dist) {
	bool improved = true;
	int k = 0;
	do{
		ameliorerSol2OPT(sol, dist, &improved);
    	++k;
    } while (improved);
    return 1 != k; //on n'a rien ameliore car on s'esta rreter des la premire iteration
}

bool troisoptconverge(int * sol, const Distancier * const dist) {
	bool improved = true;
	int k = 0;
	do{
		ameliorerSol3OPT(sol, dist, &improved);
		++k;
    } while (improved);
	return 1 != k; //on n'a rien ameliore car on s'esta rreter des la premire iteration
}

void vndPPD(int * sol, const Distancier * const dist) {
	bool improved = true;
	do {
		deuxoptPPDconverge(sol, dist);
		cout<<"avant 3optPPD : "<<calculerLongueurCircuitSol(sol, dist)<<endl;
		ameliorerSol3OptPPD( sol, dist, &improved);
		cout<<"après 3optPPD : "<<calculerLongueurCircuitSol(sol, dist)<<endl;
	} while (improved);
}

bool deuxoptPPDconverge(int * sol, const Distancier * const dist) {
cout<<"deuxoptPPDconverge : "<<calculerLongueurCircuitSol(sol, dist)<<endl;
	bool improved = true;
	int k = 0;
	do{
		ameliorerSol2OptPPD(sol, dist, &improved);
cout<<calculerLongueurCircuitSol(sol, dist)<<endl;
    	++k;
    } while (improved);
    return 1 != k; //on n'a rien ameliore car on s'esta rreter des la premire iteration
}

bool troisoptPPDconverge(int * sol, const Distancier * const dist) {
cout<<"troisoptPPDconverge : "<<calculerLongueurCircuitSol(sol, dist)<<endl;
	bool improved = true;
	int k = 0;
	do{
		ameliorerSol3OptPPD(sol, dist, &improved);
		++k;
    } while (improved);
	return 1 != k; //on n'a rien ameliore car on s'esta rreter des la premire iteration
}