void RempM (int dim, double Mat[dim][dim]);
void Cholesky(int dim, double mat[dim][dim] , double L[dim][dim] , double Lt[dim][dim]);
double P_inverse(int dim, double matrix[dim][dim], double vectPropre[dim], double eps);
void Montee(int dim, double mat[dim][dim], double sol[dim], double vect[dim]);
void Descente(int dim, double mat[dim][dim], double sol[dim], double vect[dim]);
double SommeDescente(int dim, int sup, double mat[dim][dim], double sol[dim]);
double SommeMontee(int dim, int sup, double mat[dim][dim], double sol[dim]);

