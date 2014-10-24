#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "p1.h"

void populate_array(double **L, size_t *n, int m[]){
   char *line, *token, *tofree;
   FILE *f;
   size_t size_L = 10;
   L = malloc(sizeof(double*)*size_L);
   m = malloc(sizeof(int)*size_L);
   f = fopen("input_arr", "r");
   tofree = line = malloc(sizeof(char)*100);
   token = malloc(sizeof(char)*10);
   *n = 0;
   while(fgets(line, 100, f) != NULL){
      m[*n]=0;
      while((token = strsep(&line, " ")) != NULL){
        L[*n][m[*n]++]=atof(token);
      }
      *n += 1;
      if(*n == size_L){
         size_L *= 2;
         L=realloc(L, size_L);
         m=realloc(m, size_L);
      }
   }
   free(tofree); free(token);
   fclose(f);
}
void print_array(double *l, int m){
   for(int j=0; j<m; j++)
      printf("%1.1lf ", l[j]);
   printf("\n");
}

void print_arrays(double **L, int n, int m[]){
   for(int i = 0; i<n; i++){
      print_array(L[i], m[i]);
   }
}

int main(int argc, char *argv[]){
   size_t n;
   double **L;
   int *m;
   double x = 5.0;
   populate_array(L, &n, m);
   printf("Given arrays:\n");
   print_arrays(L, n, m);
   printf("\n");

   //Init the first data structure
   S1 *s1 = malloc(sizeof(S1));
   s1_init(s1, L, n, m);
   //we will store the results of the search operation in r1
   double *r1 = malloc(sizeof(double)*n);
   //do a search for x in s1
//  s1_search(r1, s1, x);
//
//  print_array(r1, n);
   


}


