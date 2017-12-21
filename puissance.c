#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "resolution_systeme"

//------------------------------------------------------------------------------------------------------ PUISSANCE INVERSE
double puissance_inverse(int n, double eps, double A[n][n], double B[n][n], double x[n], double x0[n]){

// DECLARATION DES VARIABLES
int i, j;                                       // Compteurs pour les boucles
int choix;                                      // Choix de la methode de resolution
int nbtours;                                    // Compteur d'iteration pour trouver lambda
double Low[n][n], Up[n][n];                     // Matrices decomposees de Cholesky
double lamb = 0, prev_lamb = 0, r;              // Lambda et sa valeur prÈcÈdente
double v[n], y[n];                              // v : vecteur propre normalisÈ  | y : vecteur intermediaire de la descente
double wopt = 0;                                // Omega optimal calculÈ pour la mÈthode SOR
double w;                                       // Omega testÈ dans la boucle pour SOR
int mini;                                       // Nombre minimum de tours trouvÈ pour la recherche de wopt
double x_int[n];                                // Vecteur IntermÈdiaire pour le calcul de multmatvect



for (i = 0 ; i < n ; ++i) x_int[i] = x0[i];         // Initialisation de la matrice x pour le premier tour
r = norme2vect(n, x_int);
for (i = 0 ; i < n ; ++i) x_int[i] = x_int[i]/r;

printf("Choisir la methode (1 = Cholesky ; Autre = SOR) = ");
scanf("%d", &choix);


if (choix ==1){
Cholesky(n , A, Low, Up);
}



else{                                           // Recherche de omega optimal (depend de A)
	nbtours = SOR(n, A, v, x, 0.01);
	for (w = 0.02 ; w <= 2 ; w += 0.01)
	{
		mini = SOR(n, A, v, x, w);
		if (mini < nbtours)
		{
 			wopt = w;
			nbtours = mini;
    	}
	}
printf("\n le wopt est : %.2f \n",wopt);
}

multmatvect(n, B, x_int, x);                    // Multiplication par la matrice B pour la dÈflation


for (i = 0 ; i < n ; ++i) printf("x [%d] = %lf \n", i,x[i]);

do {

    prev_lamb = lamb;                           // Stockage de lamb dans prev_lamb pour le while

    if (choix == 1) 					        // Choix de la DÈcompostion LLT
	{
	resol_trig_inf(n, Low, y, x);
    resol_trig_sup(n, Up, v, y);
    }
    else                                        // Choix de la RÈsolution SOR
    {
	SOR(n,A,v,x,wopt);
    }

    lamb = scalaire(n, x, v);                   // Calcul du nouveau lambda

    for (i = 0 ; i < n ; ++i) x[i] = v[i];      // Calcul de x_(k+1)
    r = norme2vect(n, x);                       //
    for (i = 0 ; i < n ; ++i) x[i] = x[i]/r;    //

    ++j;                                        // Compteur

    } while (fabs(lamb - prev_lamb) >= eps); // Condition de sortie

    printf("\n \n Calcul effectue en %d tours. \n", j);
    lamb = 1/lamb;
    printf("Plus petite valeur propre : %f \n", lamb);
    return lamb;
}





/*
double puissance_iteree(int dim, double eps, double A[dim][dim], double u[dim], double u0[dim]);
{
	// Initialisation des variables -------------------------------------------
	int i, j;										// Compteurs
	double v[dim]; 									// Vecteur propre normalis�
	double L0 = 1, L1 = 2;							// Lambda(k-1) et lambda(k)
	// ------------------------------------------------------------------------
	
	// Premier calcul de v
	for (i=0 ; i<dim ; ++i) v[i] = u0[i];
	r = norme2vect(dim, v);
	for (i=0 ; i<dim ; ++i) v[i] = v[i]/r;
	
	while (fabs(L1 - L0))
	{
		multmatvect(dim, A, v, u);
		
	}
	
	
	
	
	
	for (i=0 ; i<dim ; ++i) x[i] = x0[i];
	r = norme2vect(dim, x);
	for (i=0 ; i<dim ; ++i) x[i] = x[i]/r;
	
}
*/

































