#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "p1.h"

#define printtime() (time_old = time, \
      time = clock(), \
      printf("Time taken: %1.3f\n\n", (double)(time - time_old)/CLOCKS_PER_SEC));

void populate_array(double **L, size_t *n, size_t *m, char *filename){
   char *word, *tofree, c;
   FILE *f;
   int newline = 1; 
   int i = 0;
   f = fopen(filename, "r");
   tofree = word = malloc(sizeof(char)*100);
   *n = 0;
   while((c = getc(f))!= EOF){
      if(c==' '){ 
         *word = '\0';
         word = tofree;
         if(newline) {
            newline = 0;
            i = 0;
            m[*n] = atoi(word);
            L[*n] = malloc(sizeof(double)*m[*n]);
         } else { 
            L[*n][i++] = strtod(word, NULL); 
         }
         continue;
      }
      if(c=='\n'){
         (*n)++;
         newline = 1;
         word = tofree;
         continue;
      }
      *word++ = c;
   }
   free(tofree);
   fclose(f);
}

void write_array(size_t *l, size_t m, FILE *f){
   int j;
   for(j=0; j<m; j++)
      fprintf(f, "%d ", l[j]);
   fprintf(f, "\n");
}


int main(int argc, char *argv[]){
   int i,numtests, verbose = 0;
   FILE *of;
   size_t n;
   clock_t time_old, time;

   if(argc < 3 || argc > 4){
      printf("\nUsage: %s arrayfile n-searches [outfile]\n", argv[0]);
      printf("arrayfile is the file containing the input arrays\n"
             "n-searches is number of random searches per datastructure\n" 
             "outfile (optional) if you want to save the result of each search\n"
             "Please note there is a SIGNIFICANT overhead for writing the outfile\n");
      return -1;
   }
   if(argc == 4){
      of = fopen(argv[3], "w");
      verbose = 1;
      fprintf(of, "=== The line of numbers following \"search x:\" are the indices\n"
                  "=== of the first element equal to or greater than x in each input array.\n"
                  "=== The index will be equal to the length of the array if no such\n"
                  "=== element is found \n\n\n");
   }

   double **L = malloc(sizeof(double*)*MAXL);
   size_t *m = malloc(sizeof(size_t)*MAXL);
   numtests = atoi(argv[2]);

   printf("Reading file\n", n);
   time = clock();

   populate_array(L, &n, m, argv[1]);
   printf("Read %d arrays\n", n);
   printtime();
   size_t *results = malloc(sizeof(size_t)*n);

   printf("Creating %d random search numbers\n", numtests);
   double *tests = malloc(sizeof(double)*numtests);
   for(i=0; i<numtests; i++)
      tests[i] = (double)rand()/RAND_MAX*150.0;
   printtime();

   printf("Creating datastructure #1\n");
   S1 *s1 = malloc(sizeof(S1));
   s1_init(s1, L, n, m);
   printtime()
   
   printf("Running %d searches on #1\n", numtests);
   if(verbose) fprintf(of, "\n\n####DATASTRUCTURE 1#####\n\n");
   for(i = 0; i < numtests; i++){
      s1_search(results, s1, tests[i]);
      if(verbose){
         fprintf(of, "search %5.5g: ", tests[i]);
         write_array(results, n, of);
      }
   }
   printtime()

   printf("Clearing datastructure #1\n");
   s1_destroy(s1);
   printtime();

   printf("Creating datastructure #2\n");
   S2 *s2 = malloc(sizeof(S2));
   s2_init(s2, L, n, m);
   printtime()
   
   printf("Running %d searches on #2\n", numtests);
   if(verbose) fprintf(of, "\n\n####DATASTRUCTURE 2#####\n\n");
   for(i = 0; i < numtests; i++){
      s2_search(results, s2, tests[i]);
      if(verbose){
         fprintf(of, "search %5.5g: ", tests[i]);
         write_array(results, n, of);
      }
   }
   printtime()

   printf("Clearing datastructure #2\n");
   s2_destroy(s2);
   printtime();

   printf("Creating datastructure #3\n");
   S3 *s3 = malloc(sizeof(S3));
   s3_init(s3, L, n, m);
   printtime()
   
   printf("Running %d searches on #3\n", numtests);
   if(verbose) fprintf(of, "\n\n####DATASTRUCTURE 3#####\n\n");
   for(i = 0; i < numtests; i++){
      s3_search(results, s3, tests[i]);
      if(verbose){
         fprintf(of, "search %5.5g: ", tests[i]);
         write_array(results, n, of);
      }
   }
   printtime()

   printf("Clearing datastructure #3\n");
   s3_destroy(s3);
   printtime();

   if(verbose) fclose(of);
   for(i = 0; i<n; i++)
      free(L[i]);
   free(L); free(m);
   return 0;
}


