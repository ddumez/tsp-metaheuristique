#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>

#include "./2-opt/2opt.hpp"
#include "./3-opt/3opt.hpp"
#include "./Distancier/Distancier.hpp"
#include "./GRASP/grasp.hpp"
#include "Path-Relinking/PathRel.hpp"
#include "RGSC/RGSC.hpp"
#include "vnd/vnd.hpp"
#include "vns/vns.hpp"
#include "code_fourni.hpp"

using namespace std;

#define NBITER 10

int main() {
	//variables
		clock_t t, sumt, maxt, mint;
		
		Distancier dist ("./Datas/distancier20.dat"); int zbest = 1; //pas de test de perf possible car valeur optimale inconnue
		//Distancier dist ("./Datas/ouest.dat"); int zbest = 1;//pas de test de perf possible car valeur optimale inconnue
        //Distancier dist ("./Datas/att48.dat"); int zbest = 10628;
		//Distancier dist ("./Datas/berlin52.dat"); int zbest = 7542;
		//Distancier dist ("./Datas/ch130.dat"); int zbest = 6110;
        //Distancier dist ("./Datas/ch150.dat"); int zbest = 6528;
        //Distancier dist ("./Datas/a280.dat"); int zbest = 2579;
        int * sol = new int[dist.getN()];
        bool improved = false;
        double sumz, maxz, minz, zsol;

        srand(0);
        		
        //dist.afficher();
/*
		//test du RGSC
		cout<<"calcul RGSC"<<endl;
		t = clock();
		RGSC rgsc(&dist);
		rgsc.construireCircuit(sol);
		t = clock() - t;
        afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
		cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;

		//test du NNH
		cout<<"calcul NNH"<<endl;
		t = clock();
		construireSolNNH(sol, &dist);
		t = clock() - t;
		cout<<"solution de NNH (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
		//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;

		//test du 2-opt
		cout<<"calcul 2-opt"<<endl;
		t = clock();
		sol = deuxoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
       	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

    	//test du 3-opt
        sol = new int[dist.getN()];
//    	construireSolNNH(sol, &dist);
    	rgsc.construireCircuit(sol);
    	cout<<"calcul 3-opt"<<endl;
    	t = clock();
		sol = troisoptconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

    	//test du 2-opt plus profonde descente
        sol = new int[dist.getN()];
//		construireSolNNH(sol, &dist);
		rgsc.construireCircuit(sol);
		cout<<"calcul 2-opt PPD"<<endl;
		t = clock();
		sol = deuxoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 2-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

    	//test du 3-opt plus profonde descente
        sol = new int[dist.getN()];
//		construireSolNNH(sol, &dist);
		rgsc.construireCircuit(sol);
		cout<<"calcul 3-opt PPD"<<endl;
		t = clock();
		sol = troisoptPPDconverge(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par 3-opt PPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

    	//test du vnd avec 2 et 3 opt
        sol = new int[dist.getN()];
//		construireSolNNH(sol, &dist);
		rgsc.construireCircuit(sol);
    	cout<<"calcul vnd"<<endl;
    	t = clock();
		sol = vnd(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vnd (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

    	//test du vnd avec 2 et 3 opt plus profonde descente
        sol = new int[dist.getN()];
//		construireSolNNH(sol, &dist);
		rgsc.construireCircuit(sol);
    	cout<<"calcul vndPPD"<<endl;
    	t = clock();
		sol = vndPPD(sol, &dist);
    	t = clock() - t;
    	cout<<"solution ameliorée par vndPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
    	//afficheSol(sol, &dist);
        cout<<"taille de la solution : "<<calculerLongueurCircuitSol(sol, &dist)<<endl;
        cout<<"temps : "<< (double)((double)t/(double)(CLOCKS_PER_SEC)) <<" difference proportionnelle de valeur : "<<(double)( calculerLongueurCircuitSol(sol, &dist) * 100)/(double)(zbest) - 100<<"\n"<<endl;
        delete(sol);

        //test du vns avec 2 et 3 opt
        sumt = 0; sumz = 0; maxz = 0; maxt = 0;
        cout<<"calcul vns"<<endl;
        for(int i = 0; i<NBITER; ++i) {
            sol = new int[dist.getN()];
			construireSolNNH(sol, &dist);
//			rgsc.construireCircuit(sol);
            t = clock();
            sol = vns(sol, &dist);
            t = clock() - t;
//            cout<<"solution ameliorée par vns (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
//            afficheSol(sol, &dist);
//            cout<<"\n"<<endl;

            zsol = calculerLongueurCircuitSol(sol, &dist);
            if (0 == sumt) { //premiere iteration
                minz = zsol;
                mint = t;
            }
            if (mint > t) {mint = t;}
            if (maxt < t) {maxt = t;}
            if (minz > zsol) {minz = zsol;}
            if (maxz < zsol) {maxz = zsol;}
            sumt += t;
            sumz += zsol;

            delete(sol);
        }
        sumz = (double)((double)sumz/(double)NBITER);
        cout<<"taille minimale : "<<minz<<" et maximale : "<<maxz<<endl;
        cout<<"temps minimal : "<<(double)((double)((double)mint/(double)(CLOCKS_PER_SEC)))<<" et maximal : "<<(double)((double)((double)maxt/(double)(CLOCKS_PER_SEC)))<<endl;
        cout<<"différence proportionelle moyenne de la valeur trouve par vns : "<<(double)( sumz * 100)/(double)(zbest) - 100<<" en "<<(double)((double)sumt/(double)(CLOCKS_PER_SEC*NBITER))<<endl;
        cout<<"difference proportionelle de temps : "<< (double)((double)((double)maxt/(double)(CLOCKS_PER_SEC)) * 100)/(double)((double)((double)mint/(double)(CLOCKS_PER_SEC))) - 100 <<" et de valeur : "<<(double)(maxz * 100)/(double)(minz) - 100<<"\n"<<endl;

        //test du vns avec 2 et 3 opt plus profonde descente
        sumt = 0; sumz = 0; maxz = 0; maxt = 0;
        cout<<"calcul vnsPPD"<<endl;
        for(int i = 0; i<NBITER; ++i) {
            sol = new int[dist.getN()];
			construireSolNNH(sol, &dist);
//			rgsc.construireCircuit(sol);
            t = clock();
            sol = vnsPPD(sol, &dist);
            t = clock() - t;
//            cout<<"solution ameliorée par vnsPPD (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
//            afficheSol(sol, &dist);
//            cout<<"\n"<<endl;
            
            zsol = calculerLongueurCircuitSol(sol, &dist);
            if (0 == sumt) { //premiere iteration
                minz = zsol;
                mint = t;
            }
            if (mint > t) {mint = t;}
            if (maxt < t) {maxt = t;}
            if (minz > zsol) {minz = zsol;}
            if (maxz < zsol) {maxz = zsol;}
            sumt += t;
            sumz += zsol;

            delete(sol);
        }
        sumz = (double)((double)sumz/(double)NBITER);
        cout<<"taille minimale : "<<minz<<" et maximale : "<<maxz<<endl;
        cout<<"temps minimal : "<<(double)((double)((double)mint/(double)(CLOCKS_PER_SEC)))<<" et maximal : "<<(double)((double)((double)maxt/(double)(CLOCKS_PER_SEC)))<<endl;
        cout<<"différence proportionelle moyenne de la valeur trouve par vnsPPD : "<<(double)( sumz * 100)/(double)(zbest) - 100<<" en "<<(double)((double)sumt/(double)(CLOCKS_PER_SEC*NBITER))<<endl;       
        cout<<"difference proportionelle de temps : "<< (double)((double)((double)maxt/(double)(CLOCKS_PER_SEC)) * 100)/(double)((double)((double)mint/(double)(CLOCKS_PER_SEC))) - 100 <<" et de valeur : "<<(double)(maxz * 100)/(double)(minz) - 100<<"\n"<<endl;

        //test du grasp
        sumt = 0; sumz = 0; maxz = 0; maxt = 0;
        cout<<"calcul reactive grasp"<<endl;
        for(int i = 0; i<NBITER; ++i) {
            t = clock();
            sol = reacgrasp(& dist);
            t = clock() - t;
//            cout<<"solution ameliorée par grasp (en "<<(double)((double)t/(double)(CLOCKS_PER_SEC))<<" sc) : "<<endl;
//            afficheSol(sol, &dist);
//            cout<<"\n"<<endl;
            
            zsol = calculerLongueurCircuitSol(sol, &dist);
            if (0 == sumt) { //premiere iteration
                minz = zsol;
                mint = t;
            }
            if (mint > t) {mint = t;}
            if (maxt < t) {maxt = t;}
            if (minz > zsol) {minz = zsol;}
            if (maxz < zsol) {maxz = zsol;}
            sumt += t;
            sumz += zsol;

            delete(sol);
cout<<i<<endl;
        }
        sumz = (double)((double)sumz/(double)NBITER);
        cout<<"taille minimale : "<<minz<<" et maximale : "<<maxz<<endl;
        cout<<"temps minimal : "<<mint<<" et maximal : "<<maxt<<endl;
        cout<<"différence proportionelle moyenne de la valeur trouve par grasp : "<<(double)( sumz * 100)/(double)(zbest) - 100<<" en "<<(double)((double)sumt/(double)(CLOCKS_PER_SEC*NBITER))<<endl;       
        cout<<"difference proportionelle de temps : "<< (double)((double)((double)maxt/(double)(CLOCKS_PER_SEC)) * 100)/(double)((double)((double)mint/(double)(CLOCKS_PER_SEC))) - 100 <<" et de valeur : "<<(double)(maxz * 100)/(double)(minz) - 100<<"\n"<<endl;




*/

/// Tests de Jojo :



		int *solA = new int [dist.getN()];
		int *solB = new int [dist.getN()];
		int *resultat1, *resultat2;// = new int [dist.getN()];
		//~ cout<<"calcul NNH"<<endl;
		//~ construireSolNNH(solA, &dist);
		//~ 
		//~ for (int i = 0; i < dist.getN(); ++i) {
			//~ solB[i] = solA[i];
			//~ //cout << solB[i] << endl;
		//~ }
		//~ 
        //~ cout<<"amelioration"<<endl;
		//~ solB = troisoptconverge(solB, &dist);
		
		srand(0);
		cout << "creation solA aléatoire" << endl;
		construireSolAleatoire(solA, &dist);
		afficheSol(solA, &dist);
		cout << "creation solB aléatoire" << endl;
		construireSolAleatoire(solB, &dist);
		afficheSol(solB, &dist);
		//~ cout << "creation solA NNH" << endl;
		//~ construireSolNNH(solA, &dist);
		//~ afficheSol(solA, &dist);
		//~ cout << "creation solB NNH" << endl;
		//~ construireSolNNH(solB, &dist);
		//~ afficheSol(solB, &dist);
		
		//~ cout << "Optimisation solA VND PPD" << endl;
		//~ solA = vndPPD(solA, &dist);
		//~ cout << "Optimisation solA 2-opt" << endl;
		//~ solA = deuxoptconverge(solA, &dist);
		//~ cout << "Optimisation solA 3-opt" << endl;
		//~ solA = troisoptconverge(solA, &dist);
		
		cout << "Optimisation solB VND PPD" << endl;
		solA = vndPPD(solB, &dist);
		cout << "Optimisation solB 2-opt" << endl;
		solB = deuxoptconverge(solB, &dist);
		//~ cout << "Optimisation solB 3-opt" << endl;
		//~ solB = troisoptconverge(solB, &dist);
		
		cout<<"calcul pathRelinking"<<endl;
		//~ resultat1 = pathRelinkingReconstrSelect(solA, solB, &dist, &improved, 10);
		//~ resultat2 = pathRelinkingReconstrSelect(solB, solA, &dist, &improved, 10);
		resultat1 = pathRelinkingSelect(solA, solB, &dist, &improved);
		//~ resultat2 = pathRelinkingSelect(solB, solA, &dist, &improved);
		cout << endl << "SOLUTION A : " << endl;
		afficheSol(solA, &dist);
		cout << endl << "SOLUTION B : " << endl;
		afficheSol(solB, &dist);
		cout << endl << "RESULTAT A->B : " << endl;
		afficheSol(resultat1, &dist);
		//~ cout << endl << "RESULTAT B->A : " << endl;
		//~ afficheSol(resultat2, &dist);



	//fin
return 0;
}
