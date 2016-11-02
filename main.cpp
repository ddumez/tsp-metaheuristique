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
//#include "RGSC/RGSC.hpp"
#include "vnd.hpp"
#include "vns.hpp"

using namespace std;

int main() {
	//variables
		clock_t t;
		Distancier dist ("./Datas/distancier20.dat");
		//Distancier dist ("./Datas/ouest.dat");
        int * sol = new int[dist.getN()];
		bool improved = false;
		
	//début
		//dist.afficher();

		//test du NNH
		cout<<"calcul NNH"<<endl;
		t = clock();
		construireSolNNH(sol, &dist);
		t = clock() - t;
		cout<<"solution de NNH (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
		afficheSol(sol, &dist);
		cout<<"\n"<<endl;

		//test du 2-opt
		cout<<"calcul 2-opt"<<endl;
		t = clock();
		deuxoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
/*
    	//test du 3-opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul 3-opt"<<endl;
    	t = clock();
		troisoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
*/
    	//test du 2-opt plus profonde descente
		construireSolNNH(sol, &dist);
		cout<<"calcul 2-opt PPD"<<endl;
		t = clock();
		deuxoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
/*
    	//test du 3-opt plus profonde descente
		construireSolNNH(sol, &dist);
		cout<<"calcul 3-opt PPD"<<endl;
		t = clock();
		troisoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;

    	//test du vnd avec 2 et 3 opt
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vnd"<<endl;
    	t = clock();
		vnd(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vnd (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;

    	//test du vnd avec 2 et 3 opt plus profonde descente
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vndPPD"<<endl;
    	t = clock();
		vndPPD(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vndPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;

        //test du vns avec 2 et 3 opt
        construireSolNNH(sol, &dist);
        cout<<"calcul vns"<<endl;
        t = clock();
        sol = vns(sol, &dist);
        t = clock() - t;
        cout<<"solution ameliorée par vns (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
        afficheSol(sol, &dist);
        cout<<"\n"<<endl;

        //test du vns avec 2 et 3 opt plus profonde descente
        construireSolNNH(sol, &dist);
        cout<<"calcul vnsPPD"<<endl;
        t = clock();
        sol = vnsPPD(sol, &dist);
        t = clock() - t;
        cout<<"solution ameliorée par vnsPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
        afficheSol(sol, &dist);
        cout<<"\n"<<endl;
*/


/*
		RGSC rgsc(&dist);
		rgsc.construireCircuit();
*/
	//fin
	delete(sol);

return 0;
}
