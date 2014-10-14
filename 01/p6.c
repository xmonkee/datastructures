
#include <stdio.h>
#include <stdlib.h>

double ***d3arr(size_t l, size_t m, size_t n);

int main(int argc, char **argv){
  double ***d3;
  int n;
  int i,j,k;

  if(argc < 2){
    printf("Too few arguments");
    return EXIT_FAILURE;
  }

  n = atoi(argv[1]);
  d3 = d3arr(n, n, n);

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      for(k=0; k<n; k++)
        d3[i][j][k] = i*n*n + j*n + k;

  printf("Matrix with 1D indexing:\n");

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      for(k=0; k<n; k++)
        printf(k <n-1 ? "%.1f ":"%.1f", d3[0][0][i*n*n + j*n + k]);
      printf("\n");
    }
  if(i<n-1) printf("\n");
  }

  printf("\nMatrix with 3D indexing:\n");
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      for(k=0; k<n; k++)
        printf(k <n-1 ? "%.1f ":"%.1f", d3[i][j][k]);
      printf("\n");
    }
  if(i<n-1) printf("\n");
  }

  return EXIT_SUCCESS;
}

double  ***d3arr(size_t l, size_t m, size_t n){
  int i, j;
  double ***h;
  h = malloc(sizeof(double**)*l);
  h[0] = malloc(sizeof(double*)*l*m);
  h[0][0] = malloc(sizeof(double)*l*m*n);
  for(i=0;i<l;i++){
    h[i] = &(h[0][i*m]);
    for(j=0; j<m; j++){
      h[i][j] = &h[0][0][j*m+i*m*n];
    }
  }
  return h;
}
