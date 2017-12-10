#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctions.h"
#define eps pow(10, -12)
#define sigma 1
#define rho 1
#define Long 1



int main(){

//----------------------------------------------------------------------------------------- DECLARATION DES VARIABLES

int i,j;
int n; printf("Entrer le nombres de divisions de la corde : "); scanf("%d", &n);
double L[n][n], Lt[n][n];
double vectP[n];
double x0[n];
double M[n][n]; for(i = 0 ; i < n ; ++i) {x0[i] = 0; for(j = 0 ; j < n ; ++j) {Lt[i][j] = 0; L[i][j] = 0; M[i][j] = 0;}}
double puls;


//----------------------------------------------------------------------------------------- DECLARATION DES VARIABLES

//--------------------------------------------------------------------------------------- REMPLISSAGE DE LA MATRICE M

RempM(n, M);
printf("\n Matrice M \n");
for(i = 0 ; i < n ; ++i) {for(j = 0 ; j < n ; ++j) {M[i][j] *= ((sigma * pow(n, 2))/(rho * pow(Long, 2))) ;printf("%.0f ",M[i][j]);} printf("\n");}


//--------------------------------------------------------------------------------------- REMPLISSAGE DE LA MATRICE M

// ---------------------------------------------------------------------------------------- DECOMPOSITION DE CHOLESKY

Cholesky(n, M, L, Lt);
printf(" Decomposition de Cholesky \n Matrice L : \n");
for(i = 0 ; i < n ; ++i) {printf("\n"); for(j = 0 ; j < n ; ++j) {printf("%.0f ",L[i][j]);}}

//----------------------------------------------------------------------------------------- DECOMPOSITION DE CHOLESKY

//------------------------------------------------------------------------------------------------- PUISSANCE INVERSE

for (i = 0 ; i < n ; ++i) x0[i] = 0;
x0[0] = 1;

 puls = sqrt(puissance_inverse(n, eps, M, vectP, x0));
 printf("\n La plus petite pulsation propre : w = %f \n", puls);


return 0;
}
