#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>

#include "./Distancier/Distancier.hpp"
#include "code_fourni.hpp"
#include "./3-opt/3opt.hpp"
#include "RGSC/RGSC.hpp"
#include "vnd.hpp"

using namespace std;

int main() {
	//variables
		clock_t t;
		Distancier dist ("./Datas/distancier20.dat");
		int * sol = new int[dist.getN()];
		bool improved = false;
		
	//début

		/*dist.afficher();

		//test du NNH
		cout<<"calcul NNH"<<endl;
		t = clock();
		construireSolNNH(sol, &dist);
		t = clock() - t;
		cout<<"solution de NNH (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
		afficheSol(sol, &dist);
		 
		//test du 2-opt
		cout<<"calcul 2-opt"<<endl;
		t = clock();
		do{
			ameliorerSol2OPT(sol, &dist, &improved);
    	} while (improved);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//test du 3-opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul 3-opt"<<endl;
    	t = clock();
		do{
			ameliorerSol3OPT(sol, &dist, &improved);
    	} while (improved);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//test du 2-opt plus profonde descente
		construireSolNNH(sol, &dist);
		cout<<"calcul 2-opt PPD"<<endl;
		t = clock();
		do{
			ameliorerSol2OptPPD(sol, &dist, &improved);
    	} while (improved);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//test du 2-opt plus profonde descente
		construireSolNNH(sol, &dist);
		cout<<"calcul 3-opt PPD"<<endl;
		t = clock();
		do{
			ameliorerSol3OptPPD(sol, &dist, &improved);
    	} while (improved);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//test du vnd avec 2 et 3 opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vnd"<<endl;
    	t = clock();
		vnd(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vnd (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//test du vnd avec 2 et 3 opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vndPPD"<<endl;
    	t = clock();
		vndPPD(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vndPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);

    	//dist.affichepourglpk();*/



		RGSC rgsc(&dist);
		rgsc.construireCircuit();

	//fin
	delete(sol);

return 0;
}
