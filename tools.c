#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//------------------------------------------------------------------------------------------- OUTILS

// Norme 2 d'un vecteur
double norme2vect(int dim, double A[dim]) {

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
double scalaire(int dim, double A[dim], double x[dim]) {
	double somme = 0;
	int i;

	for (i = 0; i < dim; ++i){
			somme = somme + A[i] * x[i];
	}
	return somme;
}



// Fonction pour multiplier une matrice avec un vecteur
void multmatvect(int dim, double matrix[dim][dim], double x[dim], double res[dim]) {
	double somme;
	int i,j;

	for (i = 0; i < dim; i++){
		somme = 0;
		for (j = 0; j < dim; j++){
			somme = somme + matrix[i][j] * x[j];
		}
		res[i] = somme;
	}
}

//matrice egale à soustraction de deux autres
void SousMat (int dim, double mat1[dim][dim], double mat2[dim][dim], double matres[dim][dim])
{
    int i,j;

	for (i=0; i<dim; i++)
	{
		for (j=0; j<dim; j++)
		{
			matres[i][j]=mat1[i][j] - mat2[i][j];
		}

	}
}

// Calcul produit matriciel
void multmatmat(int n, double mat1[n][n], double mat2[n][n], double res[n][n])
{
	double somme;
	int i,j,k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			somme = 0;
			for (k = 0 ; k < n ; ++k)
			{
				somme = somme + mat1[i][k] * mat2[k][j];
			}
			res[i][j] = somme;
		}
	}
}

// Remplissage de la matrice M avec des [-1 2 -1]
void RempM (int dim, double Mat[dim][dim]) {

int i,j,h;


	//Mise à Zero :
	for (i=0; i<dim;i++){
	for (j=0; j<dim;j++){
	Mat[i][j]=0;

	Mat[0][0] = 2;
	Mat[0][1] = -1;
	Mat[dim-1][dim-2]= -1;
	Mat[dim-1][dim-1]=2;

	}
}
	//boucle :
	for(h=1 ; h<(dim-1) ; ++h)
	{
		Mat[h][h]= 2;
		Mat[h][h-1]= -1;
		Mat[h][h+1]= -1;
	}

}
