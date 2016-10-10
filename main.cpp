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
		cout<<"distancier : "<<endl;
		dist.afficher();
		
		//test du NNH
		cout<<"calcul NNH"<<endl;
		construireSolNNH(sol, &dist, &zsol);
		cout<<"solution de NNH : "<<endl;
		afficheSol(sol, &dist);
		
		//test du 2-opt
		cout<<"calcul 2-opt"<<endl;
		do{
			ameliorerSol2OPT(sol, &dist, &zsol, &improved);
    	} while (improved);
    	cout<<"solution amelioré par 2-opt : "<<endl;
    	afficheSol(sol, &dist);
		
	//fin
	delete(sol);
return 0;
}
