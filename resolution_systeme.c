#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"


//--------------------------------------------------------------------------------------------------------------------------- CHOLESKY

//Calcul de la décomposition de la Matrice mat de dimension dim en L et Lt
void Cholesky(int dim, double mat[dim][dim] , double L[dim][dim] , double Lt[dim][dim]) {
	int i,j,k;
	double somme = 0;


	for(j = 0 ; j < dim ; ++j)
	{

		//-- Calcul de la valeur diagonale --//
		L[j][j] = mat[j][j];

		for (k = 0; k < j ; ++k) //somme sur k
		{
			somme += L[j][k]*L[j][k];
		}

		L[j][j] = sqrt(L[j][j] - somme);//terme diag de L
		Lt[j][j] = L[j][j];//terme diag de Lt

		//-- Fin du calcul de la valeur diag --//



		//-- Calcul des autres valeurs --//
		somme = 0;
		for (i = j+1 ; i < dim ; ++i)
		{

			L[i][j] = mat[i][j];

			for (k = 0; k < j ; ++k)
			{
				somme += L[i][k]*L[j][k];
			}


			L[i][j] = (L[i][j] - somme)/L[j][j];            //termes inf de L
			Lt[j][i] = L[i][j];                             //termes sup de L

		}
		//-- Fin du calcul des autres val --//
	}
}

//-------------------------------------------------------------------------------------------------------------------- RESOLUTION Ax = B

// Résolution de la matrice triangulaire inférieure (descente)
void resol_trig_inf(int dim, double A[dim][dim] , double x[dim], double b[dim]) {
	int i,k;
	double l;

	for (i=0;i<dim;i++) {
		l=0;
		for (k=0;k<=i-1;k++) l += A[i][k]*x[k];
		x[i] = (b[i] -l)/A[i][i];
	}
}


// Résolution de la matrice triangulaire supérieure (remontée)
void resol_trig_sup(int dim, double A[dim][dim] , double x[dim], double b[dim]) {
	int i,k;
	double l;

	for (i=dim;i>=0;i--) {
		l=0;
		for (k=i+1;k<dim;k++) l += A[i][k]*x[k];
		x[i] = (b[i] -l)/A[i][i];
	}
}


//--------------------------------------------------------------------------------------------------------------------- SOR

// Résolution par la Méthode SOR : w le coeff de relaxation
int SOR(int n, double A[n][n], double x[n], double b[n], double w) {

int i,j;
int compt = 0; 				// initialisation d'un compteur de tour (pour calcul de wopt)
double sigma;

double eps = pow(10,-12);
double residu[n];


for (i = 0 ; i < n ; ++i) x[i] = 1;    // x0 est choisit arbitrairement

do {
    for (i = 0 ; i < n ; ++i) {
        sigma = 0;
        for (j = 0 ; j < i ; ++j) {
            sigma += A[i][j] * x[j];
        }

        for ( j = i + 1 ; j < n ; ++j) {
            sigma += A[i][j] * x[j];
        }

        x[i] += w * ( ((b[i] - sigma)/A[i][i]) - x[i]);
    }
    multmatvect(n, A, x, residu);
    for (i = 0 ; i < n ; ++i) residu[i] -= b[i];

    compt+=1;

} while (norme2vect(n, residu) >= eps);

return compt;

}


