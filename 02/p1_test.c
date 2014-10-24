#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "p1.h"

void populate_array(double **L, size_t *n, size_t *m){
   char *line, *token, *tofree;
   FILE *f;
   f = fopen("input_arr", "r");
   tofree = line = malloc(sizeof(char)*100);
   *n = 0;
   while(fgets(line, 100, f) != NULL && *n < MAXL){
      m[*n] = 0;
      L[*n] = malloc(sizeof(double)*MAXARRAYLEN);
      while((token = strsep(&line, " ")) != NULL){
         L[*n][m[*n]]=atof(token);
         m[*n] += 1;
      }
      *n += 1;
      line = tofree; //reset line to beginning of alloced space
   }
   free(tofree); free(token);
   fclose(f);
}
void print_double_array(double *l, size_t m){
   for(int j=0; j<m; j++)
      printf("%1.1lf ", l[j]);
   printf("\n");
}

void print_size_array(size_t *l, size_t m){
   for(int j=0; j<m; j++)
      printf("%d ", (int)l[j]);
   printf("\n");
}

void print_arrays(double **L, size_t n, size_t *m){
   for(int i = 0; i<n; i++){
      print_double_array(L[i], m[i]);
   }
}

int main(int argc, char *argv[]){
   size_t n;
   double **L = malloc(sizeof(double*)*MAXL);
   size_t *m = malloc(sizeof(size_t)*MAXL);
   populate_array(L, &n, m);
   printf("Given arrays:\n");
   print_arrays(L, n, m);
   printf("\n");

   //Init the first data structure
   S1 *s1 = malloc(sizeof(S1));
   s1_init(s1, L, n, m);
   //we will store the results of the search operation in r1
   size_t *r1 = malloc(sizeof(size_t)*n);
   //do a search for x in s1
   s1_search(r1, s1, 5.0);
   print_size_array(r1, n);
}


