#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "RempAff.h"
#include "calcul.h"
#include "ProjetFonctions.h"

#define dim 4 			// soit on utilise le define soit on demande à l'utilisateur d'entrer la taille du système 
#define eps pow(10,-11) // Precision de la puissance inverse
#define pi 3.14159265358 //
#define sig 110 		// Tension de la corde
#define roh 0.011 			// Masse linéique de la corde
#define Long 1 			// Longueur de la corde en M


int main()
{

printf("Debut du programme... \n");




//------------------------------------------------------------------DEFINITION DES VARIABLES
 
//Choix de N --
printf("Entrer le nombre N de divisions considérées\n");
int N; 
int i,j;
scanf("%d",&N);
//-------------
double M[N][N]; // matrice M de notre système
double vectPropre[N];
double lambda;
double omega0 = (pi/Long) * sqrt(sig/roh); // Valeur de Wo
double coeffM = (sig * N) / (roh * Long);// Coefficient devant la matrice M
double puls;


while (N<2)
{
printf("Erreur, entrer un N supérieur ou égal à 2 : \n");
scanf("%d",&N);
}
//------------------------------------------------------------------------------------------

//--------------------------------------------------------DEFINITION DE LA MATRICE PARAMETRE

RempM(N,M);

// On multiplie par le coeff.

for (i = 0 ; i < N ; ++i)
{
	for (j = 0 ; j < N ; ++j)
	{
		M[i][j] *= coeffM;
	}
}

AffMat(N,M);

printf(" \n"); // pour éviter d'avoir des matrices collées


//------------------------------------------------------------------------------------------

//------------------------------------------------------------------- DECOMPOSITION CHOLESKY
double L[N][N];
double Lt[N][N];

for (i = 0 ; i < N ; ++i)
{
	for (j = 0 ; j < N ; ++j)
	{
		L[i][j] = 0;
		Lt[i][j] = 0;
	}
}

//double A[4][4] = {{1,2,6,8},{2,5,15,23},{6,15,46,73},{8,23,73,130}};

Cholesky(N, M, L, Lt);
printf("Matrice L obtenue \n");
AffMat(N, L);
printf("Matrice Lt \n");
AffMat(N, Lt);

//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------ PUISSANCE INVERSE

lambda = P_inverse(N, M, vectPropre, eps);

printf("\n Plus petite valeur propre = %f \n" ,lambda); 

AffVect(N, vectPropre);

//Calcul pulsation propre
puls = sqrt(lambda);
printf("\n Plus petite pulsation propre = %f \n" ,puls);

printf("\n Valeur théorique Wo = %f \n" ,omega0);

//------------------------------------------------------------------------------------------









printf("Fin du programme :) \n");

return 0;
}
































