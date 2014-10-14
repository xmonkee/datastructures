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

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      printf(j <n-1 ? "%.1f ":"%.1f\n", nnmat[i][j]);

  return EXIT_SUCCESS;
}

double  **dmatrix(size_t m, size_t n){
  int i;
  double **result;
  result = malloc(sizeof(double*)*m);
  for(i=0; i<m; result[i++] = malloc(sizeof(double)*n))
    ;
  return result;
}
