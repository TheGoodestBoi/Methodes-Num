#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Fonction affichage pour une Matrice 
void AffMat(int dim, double mat[dim][dim]){

double val;

for (int i=0; i<dim;i++){
	printf("|");
	for (int j=0; j<dim;j++){

	printf("%.0f ",mat[i][j]);
	}
	printf("|\n");
} 
}

//Fonction affichage pour un vecteur 
void AffVect(int dim, double mat[dim]){

double val;
printf("|");
for (int i=0; i<dim;i++){

	printf("%.3f ",mat[i]);
	} 
printf("|\n");
}

//Fonction remplissage (utlisateur) pour une Matrice 
void RempMat(int dim, double mat[dim][dim]){

double val;

for (int i=0; i<dim;i++){
	for (int j=0; j<dim;j++){

	printf("entrer A[%d][%d] : \n",i,j);
	scanf("%lf",&val);
	mat[i][j]=val;
	
	}
} 
}

//Fonction remplissage (utilisateur) pour un vecteur 
void RempVect(int dim, double mat[dim]){

double val;

for (int i=0; i<dim;i++){

	printf("entrer vect[%d]: \n",i);
	scanf("%lf",&val);
	mat[i]=val;
	
	}
}
