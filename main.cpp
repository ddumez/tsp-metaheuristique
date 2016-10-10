#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"

using namespace std;

int main() {
	//variables
		Distancier dist ("./Datas/distancier20.dat");
		int * sol = new int[dist.getN()];
		int zsol;
		bool improved = false;
		
	//début
		//test du distancier
		dist.afficher();
		
		//test du NNH
		construireSolNNH(sol, &dist, &zsol);
		afficheSol(sol, &dist);
		
		//test du 2-opt
		do{
			ameliorerSol2OPT(sol, &dist, &zsol, &improved);
    	} while (improved);
    	afficheSol(sol, &dist);
		
	//fin
	delete(sol);
return 0;
}
