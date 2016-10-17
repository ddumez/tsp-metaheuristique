#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"
#include "RGSC/RGSC.hpp"

using namespace std;

int main() {
	//variables
		Distancier dist ("./Datas/distancier20.dat");
		int * sol = new int[dist.getN()];
		bool improved = false;
		
	//début

		dist.afficher();
/*
		//test du NNH
		cout<<"calcul NNH"<<endl;
		construireSolNNH(sol, &dist);
		cout<<"solution de NNH : "<<endl;
		afficheSol(sol, &dist);
		 
		//test du 2-opt
		cout<<"calcul 2-opt"<<endl;
		do{
			ameliorerSol2OPT(sol, &dist, &improved);
    	} while (improved);
    	cout<<"solution ameliorée par 2-opt : "<<endl;
    	afficheSol(sol, &dist);

    	//test du 3-opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul 3-opt"<<endl;
		do{
			ameliorerSol3OPT(sol, &dist, &improved);
    	} while (improved);
    	cout<<"solution ameliorée par 3-opt : "<<endl;
    	afficheSol(sol, &dist);
*/




		RGSC rgsc(&dist);
		rgsc.afficherPreferences();
		cout << endl;
		rgsc.afficherCouples();
		rgsc.construireCircuit();
		cout << endl;
		//~ rgsc.afficherCouplesInt();cout << endl;
		cout << "COCORICO" << endl;
		rgsc.afficherCouplesRecursif();
		

	//fin
	delete(sol);

return 0;
}
