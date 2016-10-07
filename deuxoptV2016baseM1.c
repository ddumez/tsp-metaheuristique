// ==================================================================================================

/* Algorithmes NNH et 2-OPT sur biTSP didactique de 16 villes autour de Nantes
   Xavier.Gandibleux@univ-nantes.fr
   UFR Sciences et Techniques, Universite de Nantes -- IRCCyN UMR 6597
   2015-2016
   Rev Sept 2016

   Calcule :
    - un circuit realisable (permutation identite)
    - un circuit selon NNH au depart d'une ville donnee
    - un circuit selon 2-opt au depart d'une ville donnee
   pour 
    - distances reelles respectant l'inegalite triangulaire

*/

// ==================================================================================================

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define verbose 0

int main(void)

{

  // donnees des 16 villes autour de Nantes
    double xdata[16]={57.46, 57.12, 91.46, 57.8,  20.74, 59.84, 80.58, 26.52, 64.26, 11.22, 45.9,  42.16, 51,    81.94, 45.22, 7.82};
    double ydata[16]={65.28, 78.88,  73.1, 60.52, 52.02, 52.36, 44.54, 34.34, 31.96, 70.04, 61.54, 56.44, 55.08, 53.04, 38.42, 32.3};
    char   nCity[16][15]={"Carquefou", "Nort", "Ancenis", "St-Luce", " Rouans", "Vertou", "Clisson", "Machecoul", "Vieillevigne", "Savenay", "Orvault", "St-Herblain", "Reze", "Vallet", "St-Philbert", "Bouin"};
    
    int    xyData1[16][16]; // distanciers XY entre toutes les villes
    
    int    xSol[16][100]; // liste de toutes les solutions (tableau de solutions)
    int    iSol; // indice d'une solution dans le tableau
    int    z1=0; // performance d'une solution (longueur du circuit hamiltonien)

    int    vDep; // indice ville depart dans une solution (utilise dans NNH)
    int    i,j;
    
    int    improved; //predicat qui repere une amelioration lors d'un 2-OPT


  // proto de routines
    double calculerDistP1P2(double *xdata, int i, double *ydata, int j);
    int    calculerLongueurCircuitSol(int xSol[16][100], int iSol, int xyData[16][16]);
    void   construireSolNNH(int idepart, int xSol[16][100], int iSol, int xyData[16][16], int *zSol);
    void   ameliorerSol2OPT(int xSol[16][100], int iSol, int xyData[16][16], int *distance, int *improved);
    void   editerSolAvecNomVille(int xSol[16][100], int iSol, int zSol, char nCity[16][15]);
    void   editerSolSansNomVille(int xSol[16][100], int iSol, int zSol);
    void   editerSolutionPerfz1(int xSol[16][100], int iSol, int z1);
    
    
  //
  // POINT D ENTREE PRINCIPAL
  //

    printf("\nAlgorithmes NNH et 2-OPT sur TSP de 16 villes autour de Nantes\n");
    printf("X. Gandibleux, Univ. Nantes. 2016-2017\n\n");
    
  // Initialisations ===========================================================================

  // calcul du premier distancier (reel) en valeurs entieres
    for (i=0; i<16; i++) {
      for (j=0; j<16; j++) {
        xyData1[i][j]=round(calculerDistP1P2(xdata, i, ydata, j));
        printf("%3d ", xyData1[i][j]);
      }
      printf("\n");
    }
    printf("\n");

    
  // ==============================================================================================
  // Construction de solutions ====================================================================

  //initialise la solution avec un circuit qui correspond a la permutation identite

  // Pour la fonction objectif 1
    printf("Solution triviale utilisant la permutation identite sur xyData1 :\n");
    for (i=0; i<16; i++) {
      xSol[i][iSol=0]=i;
    }
    z1 = calculerLongueurCircuitSol(xSol, iSol=0, xyData1);
    editerSolAvecNomVille(xSol, iSol=0, z1, nCity);

    
  // ==============================================================================================
  // Calcul avec l'heuristique NNH une tournee a partir de l'indice d'une ville donnee ============
  // Depart de vDep=0 (Carquefou)

  // Pour la fonction objectif 1
    printf("Solution NNH Depart de vDep=0 sur xyData1 :\n");
    construireSolNNH(vDep=0, xSol, iSol=0, xyData1, &z1);
    z1 = calculerLongueurCircuitSol(xSol, iSol=0, xyData1);
    editerSolSansNomVille(xSol, iSol=0, z1);// nCity);

    
  // ==============================================================================================
  // Amelioration solution =======================================================================
  // 2-OPT sur z1 :

  //Solution apres recherche locale
    do{
       printf("Solution apres recherche locale :\n");
       ameliorerSol2OPT(xSol, iSol=0, xyData1, &z1, &improved);
       z1 = calculerLongueurCircuitSol(xSol, iSol=0, xyData1);
       editerSolutionPerfz1(xSol, iSol=0, z1);//, nCity);
       if (improved==1) printf("Restart suite amelioration\n");
    } while (improved==1);
 
	printf("\n");
    return(0);
	
}

// ==================================================================================================
// ==================================================================================================


// ==================================================================================================
// Calcul de la distance entre 2 points P1 et P2
double calculerDistP1P2(double *xdata, int i, double *ydata, int j)
{
  return(sqrt(pow(xdata[i]-xdata[j],2) + pow(ydata[i]-ydata[j],2)));
}


// ==================================================================================================
// calcule une tournee a partir de la ville idepart avec l'heuristique NNH
void construireSolNNH(int idepart, int xSol[16][100], int iSol, int xyData[16][16], int *distance)
{
  int i,j;
  int n=16;
  int min, jmin;
  int tmp;
  int zSol;
    
  zSol=0  ; // longueur du circuit hamiltonien

  //initialise la solution avec un circuit qui correspond a la permutation identite
  for (i=0; i<n; i++) {
    xSol[i][iSol]=i;
  }

  //ajuste les donnees du circuit pour la ville de depart demandee
    tmp = xSol[0][iSol];
    xSol[0][iSol] = xSol[idepart][iSol];
    xSol[idepart][iSol] = tmp;
    
  // calcule la distance min de la ville i a toutes les autres villes
  for (i=0; i<n-1; i++) {
    jmin = i+1;
    min = xyData[ xSol[i][iSol] ][ xSol[jmin][iSol] ];

     // printf("i : "); for (j=i+1; j<n; j++) {        printf("%2d ",xSol[j][0]);    };printf("\n");
     // printf("d : "); for (j=i+1; j<n; j++) {        printf("%2d ",xyData[ xSol[i][0] ][ xSol[j][0] ]);    };printf("\n");
      
    for (j=i+1; j<n; j++) {
    //localise le min sur une ligne de la matrice triangulaire superieure
       // printf("i:%d j:%d d:%d / min:%d\n",xSol[i][0], xSol[j][0], xyData[ xSol[i][0] ][ xSol[j][0] ], min);
       // if (xyData[ xSol[i][0] ][ xSol[j][0] ] == min) printf("!!!!!!!\n");
      if (xyData[ xSol[i][iSol] ][ xSol[j][iSol] ] < min) {
        min = xyData[ xSol[i][iSol] ][ xSol[j][iSol] ];
        jmin = j;
      }
    }
      //printf("xSol:%d jmin:%d min:%d\n\n",xSol[jmin][0], jmin, min);
      
    zSol+= min;
    // echange entre la ville i+1 et jmin dans la solution
    tmp = xSol[i+1][iSol];
    xSol[i+1][iSol] = xSol[jmin][iSol];
    xSol[jmin][iSol] = tmp;
  }

  // Ferme le chemin pour former un circuit
    zSol+=xyData[ xSol[jmin][iSol] ][ xSol[0][iSol] ];
    
    //for (i=0; i<n; i++) {
    //    printf("%d ", xSol[i][0]);
    //}

    //printf("\n zSol = %d\n", zSol);
    *distance = zSol;
}


// ==================================================================================================
// calcul de la longueur du circuit pour une solution
int calculerLongueurCircuitSol(int xSol[16][100], int iSol, int xyData[16][16])
{
  int  zSol=0  ; // longueur du circuit hamiltonien
  int  k;
  int  vDep, vArr; // indice ville depart et arrivee dans une solution

  // les distances i a j depuis ville depart
  printf(" sum(");
  for (k=0; k<15; k++) {
    vDep=xSol[k][iSol]; vArr=xSol[k+1][iSol];
    zSol+=xyData[vDep][vArr];
    printf("%4d ",xyData[vDep][vArr]);
  }

  // dernier segments qui revient a la ville de depart
  vDep=xSol[15][iSol]; vArr=xSol[0][iSol];
  zSol+=xyData[vDep][vArr];
  printf("%4d ) = %4d \n",xyData[vDep][vArr], zSol);
  return(zSol);
}


// ==================================================================================================
// Edition d'une solution
void editerSolAvecNomVille(int xSol[16][100], int iSol, int zSol, char nCity[16][15])
{
  int k;

  printf("x = (");
  for (k=0; k<16; k++) {
    printf("%2d ", xSol[k][iSol]);
  }

  // dernier segments qui revient a la ville de depart
  printf("%2d ) | " , xSol[0][iSol]);
  printf(" length = %4d\n", zSol);

  for (k=0; k<16; k++) {
        printf("%15s \n", nCity[ xSol[k][iSol] ]);
  }

  // dernier segments qui revient a la ville de depart
  printf("%15s \n\n" , nCity[ xSol[0][iSol] ]);
}

// ==================================================================================================
// Edition d'une solution bis
void editerSolSansNomVille(int xSol[16][100], int iSol, int zSol)
{
  int k;

  printf("x = (");
  for (k=0; k<16; k++) {
    printf("%2.2d ", xSol[k][iSol]);
  }

  // dernier segments qui revient a la ville de depart
  printf("%2.2d ) \n\n" , xSol[0][iSol]);
}

// ==================================================================================================
// Edition d'une solution (z1 z2)
void editerSolutionPerfz1(int xSol[16][100], int iSol, int z1)
{
  int k;

  printf("x = (");
  for (k=0; k<16; k++) {
        printf("%2.2d ", xSol[k][iSol]);
  }

  // dernier segments qui revient a la ville de depart
  printf("%2.2d ) | " , xSol[0][iSol]);

  // performances
  printf("z(x)= (%4d)\n\n",z1);
}

// ==================================================================================================
// amelioration 2-OPt

void ameliorerSol2OPT(int xSol[16][100], int iSol, int xyData[16][16], int *distance, int *improved)
{
  int i,j,k, k1, tmp;
  int iD, iF, jD, jF;
    
  int debSgm1, debSgm2, finSgm1, finSgm2;
  int d1, d2;
    
  int zSol=0  ; // longueur du circuit hamiltonien
    
  /*    if (verbose==1) {
        
        for (i=0; i<8; i++) {
            for (j=0; j<8-3; j++) {
                // k1 = (j+2) % 16;
                printf("%d-%d %d-%d \n", i%8, (i+1)%8, (i+j+2) % 8, (i+j+3) % 8);
            }
            // exit(0);
        }
    }
  */

  *improved=0;
    
  for (i=0; i<16; i++) {
    for (j=0; j<13; j++) {

      iD=i%16;
      iF=(i+1)%16;
      jD=(i+j+2) % 16;
      jF=(i+j+3) % 16;

      if (verbose==1) printf("%2d-%2d %2d-%2d :: ", iD, iF, jD, jF);
            
      d1 = xyData[ xSol[iD][iSol] ][ xSol[iF][iSol] ] + xyData[ xSol[jD][iSol] ][ xSol[jF][iSol] ];
      d2 = xyData[ xSol[iD][iSol] ][ xSol[jD][iSol] ] + xyData[ xSol[iF][iSol] ][ xSol[jF][iSol] ];
            
      if (verbose==1)  printf(" (%2d - %2d) (%2d - %2d) | d1=%2d d2=%2d", xSol[iD][iSol],xSol[iF][iSol], xSol[jD][iSol], xSol[jF][iSol], d1, d2);

      if (d1>d2) {
        // amelioration detectee
 
        if (verbose==1) {
                    
          printf(" yes.  Avant : \n\n");
                    
          zSol = calculerLongueurCircuitSol(xSol, iSol, xyData);
          for (k1=0; k1<16; k1++) {
            printf("%2d ", xSol[k1][iSol]);
          };printf("\n");
                    
        }

        *improved=1; // notifie que une amelioration est detectee
                
        debSgm1 = xSol[iD][iSol];
        finSgm1 = xSol[iF][iSol];
                
        debSgm2 = xSol[jD][iSol];
        finSgm2 = xSol[jF][iSol];
                
        if (verbose==1) printf(" (%2d %2d) and (%2d %2d) ", debSgm1, finSgm1, debSgm2, finSgm2);

        xSol[iF][iSol] = debSgm2;
        xSol[jD][iSol] = finSgm1;
                
        // Inversion des segments du chemin entre les 2 segments traites
        if (iD < jD) {
          if (verbose==1) printf("iD%2d  iF%2d", iD, iD);
          for (k=1; k<=(jD-(iD+2))/2; k++) {
            if (verbose==1) printf("========= %d %d   ", xSol[iD+1+k][iSol], xSol[jD-k][iSol]);
            tmp = xSol[iD+1+k][iSol];
            xSol[iD+1+k][iSol] = xSol[jD-k][iSol];
            xSol[jD-k][iSol] = tmp;
          }
        }
        else
        {
          if (verbose==1) printf("\n >>>> %d \n", (16-(iD-jD)-2)/2);
          for (k=1; k<=(16-(iD-jD)-2)/2; k++) {
            if (verbose==1) printf("========= %d %d   ", xSol[(iD+1+k)%16][iSol], xSol[(16+jD-k)%16][iSol]);
            tmp = xSol[(iD+1+k)%16][iSol];
            xSol[(iD+1+k)%16][iSol] = xSol[(16+jD-k)%16][iSol];
            xSol[(16+jD-k)%16][iSol] = tmp;
          }
                    
          //  printf("halt---------iD=%d jD=%d \n",iD,jD);//exit(0);
          //   tmp = iD;
          //   iD = jD;
          //   jD = tmp;
          //printf("apres iD=%d jD=%d \n",iD,jD);exit(0);
        } // sinon iD< jD et donc rien a faire
                
                
        // Boucle a refaire !!!! calculer a plat, sans le modulo pour etablir le nbre d'els concernes entre fin 1er segment et deb 2e segn
                
                
        if (verbose==1) printf(" Permutation modifiee finalisee :\n");
        
        zSol = calculerLongueurCircuitSol(xSol, iSol, xyData);
        if (verbose==1) {
          for (k1=0; k1<16; k1++) {
            printf("%2d ", xSol[k1][iSol]);
          };printf("\n\n");
          editerSolSansNomVille(xSol, iSol, zSol);//, nCity);
        }
      } // Fin traitement suite amelioration detectee

      if (verbose==1) printf("\n");
            
    }
  }
}

