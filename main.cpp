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
#include "vns.hpp"

using namespace std;

#define NBITER 10

int main() {
	//variables
		clock_t t, sumt;
		//Distancier dist ("./Datas/distancier20.dat");
		//Distancier dist ("./Datas/ouest.dat");
        //Distancier dist ("./Datas/att48.dat"); //z best sol : 10628
        Distancier dist ("./Datas/berlin52.dat"); //z best sol : 7542
        //Distancier dist ("./Datas/ch130.dat"); //z best sol : 6110
        //Distancier dist ("./Datas/ch150.dat"); //z best sol : 6528
        //Distancier dist ("./Datas/a280.dat"); //z best sol : 2579
        int * sol = new int[dist.getN()];
		bool improved = false;
        double sumz;
		
	//début

		//dist.afficher();
/*
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
		sol = deuxoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

    	//test du 3-opt
        sol = new int[dist.getN()];
    	construireSolNNH(sol, &dist);
    	cout<<"calcul 3-opt"<<endl;
    	t = clock();
		sol = troisoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

    	//test du 2-opt plus profonde descente
        sol = new int[dist.getN()];
		construireSolNNH(sol, &dist);
		cout<<"calcul 2-opt PPD"<<endl;
		t = clock();
		sol = deuxoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

    	//test du 3-opt plus profonde descente
        sol = new int[dist.getN()];
		construireSolNNH(sol, &dist);
		cout<<"calcul 3-opt PPD"<<endl;
		t = clock();
		sol = troisoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

    	//test du vnd avec 2 et 3 opt
        sol = new int[dist.getN()];
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vnd"<<endl;
    	t = clock();
		sol = vnd(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vnd (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

    	//test du vnd avec 2 et 3 opt plus profonde descente
        sol = new int[dist.getN()];
    	construireSolNNH(sol, &dist);
    	cout<<"calcul vndPPD"<<endl;
    	t = clock();
		sol = vndPPD(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vndPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	afficheSol(sol, &dist);
        cout<<"\n"<<endl;
        delete(sol);

        //test du vns avec 2 et 3 opt
        sumt = 0; sumz = 0;
        cout<<"calcul vns"<<endl;
        for(int i = 0; i<NBITER; ++i) {
            sol = new int[dist.getN()];
            construireSolNNH(sol, &dist);
            t = clock();
            sol = vns(sol, &dist);
            t = clock() - t;
//            cout<<"solution ameliorée par vns (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
//            afficheSol(sol, &dist);
//            cout<<"\n"<<endl;

            sumt += t;
            sumz += calculerLongueurCircuitSol(sol, &dist);

            delete(sol);
        }
        cout<<"moyenne de la valeur trouve par vns : "<<(double)((double)sumz/(double)NBITER)<<" en "<<(double)((double)sumt/(double)(CLOCKS_PER_SEC*NBITER))<<"\n"<<endl;

        //test du vns avec 2 et 3 opt plus profonde descente
        sumt = 0; sumz = 0;
        cout<<"calcul vnsPPD"<<endl;
        for(int i = 0; i<NBITER; ++i) {
            sol = new int[dist.getN()];
            construireSolNNH(sol, &dist);
            t = clock();
            sol = vnsPPD(sol, &dist);
            t = clock() - t;
//            cout<<"solution ameliorée par vnsPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
//            afficheSol(sol, &dist);
//            cout<<"\n"<<endl;
            
            sumt += t;
            sumz += calculerLongueurCircuitSol(sol, &dist);

            delete(sol);   
        }
        cout<<"moyenne de la valeur trouve par vns : "<<(double)((double)sumz/(double)NBITER)<<" en "<<(double)((double)sumt/(double)(CLOCKS_PER_SEC*NBITER))<<"\n"<<endl;        
*/



		RGSC rgsc(&dist);
		rgsc.construireCircuit(sol);
		afficheSol(sol, &dist);
		//~ dist.afficher();

	//fin

return 0;
}
