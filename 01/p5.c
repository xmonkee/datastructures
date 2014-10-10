#include <stdio.h>
#include <stdlib.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char **argv){
  double **nnmat;
  int n;
  int i,j;

  if(argc < 2){
    printf("Too few arguments");
    return EXIT_FAILURE;
  }

  n = atoi(argv[1]);
  nnmat = dmatrix(n, n);

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      nnmat[i][j] = i*n + j;

  printf("Matrix with 1d indexing:\n");

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      printf(j <n-1 ? "%d ":"%d\n", (int)nnmat[0][i*n+j]);

  printf("\nMatrix with 2d indexing:\n");

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      printf(j <n-1 ? "%d ":"%d\n", (int)nnmat[i][j]);

  return EXIT_SUCCESS;
}

double  **dmatrix(size_t m, size_t n){
  int i;
  double *zero;
  double **result;
  result = malloc(sizeof(double*)*m);
  zero = malloc(sizeof(double)*m*n);
  for(i=0; i<m; i++)
    result[i] = zero+i*n ;
  return result;
}
