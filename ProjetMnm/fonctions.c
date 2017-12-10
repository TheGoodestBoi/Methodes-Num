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
void multmatvect(int taille, double A[taille][taille], double x[taille], double res[taille]) {
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


//----------------------------------------------------------------------------------------- CHOLESKY

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


			L[i][j] = (L[i][j] - somme)/L[j][j];//termes inf de L
			Lt[j][i] = L[i][j];//termes sup de L

		}
		//-- Fin du calcul des autres val --//
	}
}

//----------------------------------------------------------------------------------- RESOLUTION LLt

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


//-------------------------------------------------------------------------------- PUISSANCE INVERSE

double puissance_inverse(int n, double eps, double A[n][n], double x[n], double x0[n]){

int i, j = 0;
double Low[n][n], Up[n][n];
double lamb = 0, prev_lamb = 0, r;
double v[n], y[n];

Cholesky(n , A, Low, Up);

for (i = 0 ; i < n ; ++i) x[i] = x0[i];
r = norme2vect(n, x);
for (i = 0 ; i < n ; ++i) x[i] = x[i]/r;


do {

    prev_lamb = lamb;                   // Stockage de lamb dans prev_lamb pour le while

    resol_trig_inf(n, Low, y, x);       // Résolution du système décomposé
    resol_trig_sup(n, Up, v, y);        //
    for (i = 0 ; i < n ; ++i) printf(" \n v[%d] = %f", i, v[i]);

    lamb = scalaire(n, x, v);           // Calcul du nouveau lambda

    for (i=0;i<n;i++) x[i] = v[i];      // Calcul de x_(k+1)
    r = norme2vect(n, x);               //
    for (i=0;i<n;i++) x[i] = x[i]/r;    //

    ++j;                                // Compteur

    } while (fabs(lamb - prev_lamb) >= eps); // Condition de sortie

    printf("\n \n Calcul effectue en %d tours. \n", j);
    lamb = 1/lamb;
    printf("Plus petite valeur propre : %f", lamb);
    return lamb;
}















