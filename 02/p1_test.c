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
   int j;
   for(j=0; j<m; j++)
      printf("%1.1lf ", l[j]);
   printf("\n");
}

void print_size_array(size_t *l, size_t m){
   int j;
   for(j=0; j<m; j++)
      printf("%d ", (int)l[j]);
   printf("\n");
}

void print_arrays(double **L, size_t n, size_t *m){
   int i;
   for(i = 0; i<n; i++){
      print_double_array(L[i], m[i]);
   }
}

int main(int argc, char *argv[]){
   size_t n;
   double **L = malloc(sizeof(double*)*MAXL);
   size_t *m = malloc(sizeof(size_t)*MAXL);
   if(argc < 2){
      printf("Enter search term");
      return -1;
   }
   double x = atof(argv[1]); //search term from command line

   populate_array(L, &n, m);

   size_t *results = malloc(sizeof(size_t)*n);
   print_size_array(m, n);

   //Init the first data structure
   S1 *s1 = malloc(sizeof(S1));
   s1_init(s1, L, n, m);
   //do a search for x in s1
   s1_search(results, s1, x);
   //print results
   print_size_array(results, n);
   //destory s1;
   s1_destroy(s1);

   //Init the second data structure
   S2 *s2 = malloc(sizeof(S2));
   s2_init(s2, L, n, m);
   //do a search for x in s2;
   s2_search(results, s2, x);
   print_size_array(results, n);
   
   return 0;
}


