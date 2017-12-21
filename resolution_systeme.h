void Cholesky(int dim, double mat[dim][dim] , double L[dim][dim] , double Lt[dim][dim]);
void resol_trig_inf(int dim, double A[dim][dim] , double x[dim], double b[dim]);
void resol_trig_sup(int dim, double A[dim][dim] , double x[dim], double b[dim]);
int SOR(int n, double A[n][n], double x[n], double b[n], double w);

