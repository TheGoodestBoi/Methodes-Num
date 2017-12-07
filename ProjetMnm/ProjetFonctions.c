#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "RempAff.h"



//------------------------------------------------------------------------------------------- OUTILS

// Norme 2 d'un vecteur 
double norme2vect(int dim, double A[dim]){

double somme = 0; 
int i;

	for (i = 0; i < dim; i++)
	{
			somme = somme + A[i] * A[i];			
	}
	somme = sqrt(somme);
	return somme;

}




// Produit scalaire de 2 vecteurs
double scalaire(int dim, double A[dim], double x[dim])
{
	double somme = 0;
	int i;

	for (i = 0; i < dim; ++i){
			somme = somme + A[i] * x[i];			
	}
	return somme;
}



// Fonction pour multiplier une matrice avec un vecteur
void multmatvect(int taille, double A[taille][taille], double x[taille], double res[taille]){
	double somme;
	int i,j;

	for (i = 0; i < taille; i++){
		somme = 0;
		for (j = 0; j < taille; j++){
			somme = somme + A[i][j] * x[j];			
		}
		res[i] = somme;
	}
}


void RempM (int dim, double Mat[dim][dim])
{


	//Mise à Zero : 
	for (int i=0; i<dim;i++){
	for (int j=0; j<dim;j++){
	Mat[i][j]=0;
	
	Mat[0][0] = 2; 
	Mat[0][1] = -1; 
	Mat[dim-1][dim-2]= -1;
	Mat[dim-1][dim-1]=2;

	}
} 
	//boucle : 
	for(int h=1 ; h<(dim-1) ; ++h)
	{
		Mat[h][h]= 2;
		Mat[h][h-1]= -1;
		Mat[h][h+1]= -1;
	}

}

//--------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------ RESOLUTION LU


void Cholesky(int dim, double mat[dim][dim] , double L[dim][dim] , double Lt[dim][dim]) 
{
	int i,j,k;
	double somme = 0; 

	
	for(j = 0 ; j < dim ; ++j)
	{

		//-- Calcul de la valeur diagonale --//
		L[j][j] = mat[j][j];

		for (k = 0; k < j-1 ; ++k) //somme sur k
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

			for (k = 0; k < j-1 ; ++k) 
			{			
				somme += L[i][k]*L[j][k];
			}


			L[i][j] = (L[i][j] - somme)/L[j][j];//termes inf de L
			Lt[j][i] = L[i][j];//termes sup de L
			
		}
		//-- Fin du calcul des autres val --//
	}	
}

//-------------------------------------------------------------------------------------------------

void resol_trig_inf(int dim, double A[dim][dim] , double x[dim], double b[dim]) {
	int i,k;
	double l;
	
	for (i=0;i<dim;i++) {
		l=0;
		for (k=0;k<=i-1;k++) l += A[i][k]*x[k];
		x[i] = (b[i] -l)/A[i][i];
	}
}


void resol_trig_sup(int dim, double A[dim][dim] , double x[dim], double b[dim]) {
	int i,k;
	double l;
	
	for (i=dim;i>=0;i--) {
		l=0;
		for (k=i+1;k<dim;k++) l += A[i][k]*x[k];
		x[i] = (b[i] -l)/A[i][i];
	}
}

//------------------------

void resol_LLt(int dim, double A[dim][dim] , double x[dim], double b[dim]) {
	
	double L[dim][dim], Lt[dim][dim], y[dim];
	int i,j;

	for (i = 0 ; i < dim ; ++i)
	{
		for (j = 0 ; j < dim ; ++j)
		{
			L[i][j] = 0;
		}
	}
	
	Cholesky(dim,A,L,Lt);

	resol_trig_inf(dim,L,y,b);
	resol_trig_sup(dim,Lt,x,y);
	
}

//--------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------- PUISSANCE INVERSE

double P_inverse(int dim, double matrix[dim][dim], double vectPropre[dim], double eps)
{

int i,j;
double lambda = 0;
double lambdaprev = 0;
double vectV[dim];
double vectU[dim];
double err;

// On pose V^0 = [1 0 0 0]
for (i = 1 ; i < dim ; ++i)
    {
        vectV[i] = 0;
    }
vectV[0] = 1;

do
{	
	resol_LLt(dim, matrix, vectU, vectV);
	lambdaprev = lambda;
	lambda = scalaire(dim, vectV, vectU);
	for (j = 0 ; j < dim ; ++j)
	{
	vectV[j] = vectU[j] / norme2vect(dim, vectU);
	}
	err = fabs(lambda - lambdaprev);
} while (err >= eps);

lambda = 1/lambda;
for (j = 0 ; j < dim ; ++j)
	{
		vectPropre[j] = vectV[j];
	} 

return lambda;

}



























