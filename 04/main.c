#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "boolean.h"
#include "graph.h"
#include "dijkstra.h"
#include "main.h"

#define printtime() (time_old = time, \
      time = omp_get_wtime(), \
      printf("Time taken: %1.1f\n\n", time-time_old));

void run_single_source(Graph *G, int source);
void run_all_sources(Graph *G);

boolean verbose = FALSE;

int main(int argc, char ** argv){

   FILE *f;
   Graph * G;
   float time, time_old;
   

   if(argc < 2){
      printf("Please supply filename \n");
      return 1;
   }

   if((f = fopen(argv[1], "r"))==NULL){
      printf("Can't open file\n");
      return -1;
   }

   if(argc > 2)
      verbose = (strcmp(argv[2], "-v")==0);

   
   G = malloc(sizeof(Graph));
   graph_init(G);
   graph_read(G, f); //read graph from input file
   fclose(f);

   time=omp_get_wtime();

#ifdef SINGLESOURCE
   printf("Running Dijkstra Single Source\n");
   run_single_source(G, 0);
   printtime();
#endif

#ifdef ALLSOURCES
   printf("Running Dijkstra All Sources\n");
   run_all_sources(G); 
   printtime();
#endif

   graph_destroy(G);
   free(G);

}

void run_single_source(Graph *G, int source){
   int i, tmp;
   int N = graph_vertices(G);
   float *d = malloc(sizeof(float)*N); //distance array
   int *p = malloc(sizeof(int*)*N); //parent array
   dijkstra_single_source(G, source, d, p); //Run Dijsktra

   if(verbose){
      printf("Source %d\n", source);
      for(i = 0; i<graph_vertices(G); i++) 
         printf("%d, %.0f, %d\n", i, d[i], p[i]);
         //print the vertex, it's path wt and it's parent
      printf("\n");
   }

   free(d);
   free(p);
}


void run_all_sources(Graph *G){
   int i;
#pragma omp parallel default(none) shared(G)
   {
#pragma omp master
      {
      printf("Number of threads: %d\n", omp_get_num_threads());
      }
#pragma omp for 
      for(i = 0; i<G->N; i++){
         run_single_source(G, i);
      }
   }
}

