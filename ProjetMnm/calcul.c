#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// matrice egale à une autre
void EgalVect (int dim, double Vect[dim], double Vectres[dim])
{
	for (int i=0; i<dim; i++)
	{
			Vectres[i]=Vect[i];
	}
}

//Produit d'une matrice avec une vecteur : 
void ProdMatVect (int dim, double mat[dim][dim], double vect[dim] , double vectRes[dim])
{
	for (int i=0; i<dim; i++)
	{	
		vectRes[i]=0;
		for (int j=0; j<dim; j++)
		{
			vectRes[i]= vectRes[i] + mat[i][j] * vect[j]; 
		}

	}
}

//Produit scalaire de deux vecteurs 
double ProdScalaire (int dim, double vect1[dim], double vect2[dim])
{
	double res = 0;
	for (int i=0; i<dim; i++)
	{
		res= res + vect1[i]*vect2[i]; 

	}
	return res; 
}

//matrice egale à adition de deux autres 
void AddiMat (int dim, double mat1[dim][dim], double mat2[dim][dim], double matres[dim][dim])
{
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			matres[i][j]= mat1[i][j] + mat2[i][j]; 
		}
	}
}
//matrice egale à soustraction de deux autres
void SousMat (int dim, double mat1[dim][dim], double mat2[dim][dim], double matres[dim][dim])
{
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			matres[i][j]=mat1[i][j] - mat2[i][j]; 
		}

	}
} 

//calcul de norme 2 
double norme2(int dim, double Vect[dim])
{
	double res = 0 ;
	for (int i=0; i<dim; i++)
	{
			res = res + Vect[i]*Vect[i]; 
	}
	res = sqrt(res);
	return res; 

}

//Normalisation d'un vecteur (norme 2)
void Normalisation (int dim, double VectANorm[dim], double res[dim])
{
	int N = norme2(dim,VectANorm);
	for (int i=0; i<dim; i++)
	{
		res[i] = VectANorm[i] / N ; 
	}

}
