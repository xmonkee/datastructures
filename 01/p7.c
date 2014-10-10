/* Sources:
 * timing methods: http://stackoverflow.com/questions/459691/best-timing-method-in-c 
 * addressing an error while trying to free up static memory: http://stackoverflow.com/questions/16506579/c-free-variables-declared-inside-function
 * */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define M 1000
#define N 1000

void work_kernel_dynamic(double **U, int m, int n)
{
  int i,j;
  double a = 1.0, b = 0.5, c;

  for( i=1; i < (m-1); i++)
    for( j=1; j < (n-1); j++)
    {
      c = ( a * (U[i+1][j] + U[i-1][j]) ) +
                ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
    }

  return;
}

void work_kernel_static(double U[M][N], int m, int n)
{
  int i,j;
  double a = 1.0, b = 0.5, c;

  for( i=1; i < (m-1); i++)
    for( j=1; j < (n-1); j++)
    {
      c = ( a * (U[i+1][j] + U[i-1][j]) ) +
                ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
    }

  return;
}

double  **contmatrix(size_t m, size_t n){
  int i;
  double *zero;
  double **result;
  result = malloc(sizeof(double*)*m);
  zero = malloc(sizeof(double)*m*n);
  for(i=0; i<m; i++)
    result[i] = zero+i*n ;
  return result;
}

double **discontmatrix(size_t m, size_t n){
  int i;
  double **result;
  result = malloc(sizeof(double*)*m);
  for(i=0; i<m; i++)
    result[i] = malloc(sizeof(double)*n);
  return result;

}

void initarray_static(double U[M][N], int m, int n){
  int i, j;
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      U[i][j] = i*n+j;
}

void initarray_dynamic(double **U, int m, int n){
  int i, j;
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      U[i][j] = i*n+j;
}


int main(int argc, char * argv[])
{
  
  int m = 1000;
  int n = 1000;
  clock_t t1, t2, t3, t;

  /* Declare and allocate your arrays A,B,C */
  double A[M][N];
  double **B, **C;
  B = contmatrix(m,n);
  C = discontmatrix(m,n);

  initarray_static(A, m, n);
  initarray_dynamic(B, m, n);
  initarray_dynamic(C, m, n);

  

  /* time A */
  t = clock(); 
  work_kernel_static( A, m, n);
  t1 = clock() - t;

  /* clock B */
  t = clock();
  work_kernel_dynamic( B, m, n);
  t2 = clock() - t;

  /* clock C */
  t = clock();
  work_kernel_dynamic( C, m, n);
  t3 = clock() - t;


  /* Print out timing to stdout in seconds for each array */
  printf("%f - statically allocated 2d array\n", (float)t1/CLOCKS_PER_SEC);
  printf("%f - dynamically allocated 2d array, contiguous in memory\n", (float)t2/CLOCKS_PER_SEC);
  printf("%f - dynamically allocated 2d array, distributed through memory\n", (float)t3/CLOCKS_PER_SEC);

  /* Free memory*/
  free(B);
  free(C);
  
  return 0;

}

