#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "boolean.h"
#include "graph.h"
#include "dijkstra.h"

#define printtime() (time_old = time, \
      time = omp_get_wtime(), \
      printf("Time taken: %1.1f\n\n", time-time_old));

void run_single_source(Graph *G, int source);
void run_all_sources(Graph *G);

FILE *ofile;

int main(int argc, char ** argv){

   FILE *ifile;
   Graph * G;
   float time, time_old;
   

   if(argc < 2){
      printf("Please supply input filename \n");
      return 1;
   }

   if((ifile = fopen(argv[1], "r"))==NULL){
      printf("Can't open %s\n", argv[1]);
      return -1;
   }

#ifdef VERBOSE
      if(argc < 3){
         printf("Please supply output filename \n");
         return 1;
      }

      if((ofile = fopen(argv[2], "w"))==NULL){
         printf("Can't open %s\n", argv[2]);
         return -1;
      }
#endif

   
   G = malloc(sizeof(Graph));
   graph_init(G);
   graph_read(G, ifile); //read graph from input file
   fclose(ifile);

   time=omp_get_wtime();

#ifndef ALLSOURCES
   printf("Running Dijkstra Single Source\n");
   run_single_source(G, 0);
   printtime();
#endif

#ifdef ALLSOURCES
   printf("Running Dijkstra All Sources\n");
   run_all_sources(G); 
   printtime();
#endif

#ifdef VEBOSE
   fclose(ofile);
#endif

   graph_destroy(G);
   free(G);

   return 0;

}

void run_single_source(Graph *G, int source){
   int N = graph_vertices(G);
   float *d = malloc(sizeof(float)*N); //distance array
   int *p = malloc(sizeof(int*)*N); //parent array
   dijkstra_single_source(G, source, d, p); //Run Dijsktra

#ifdef VERBOSE
   #ifdef ALLSOURCES
      #pragma omp critical
      {
   #endif
   fprintf(ofile, "Source %d\n", source);
   int i;
   for(i = 0; i<graph_vertices(G); i++) 
      fprintf(ofile, "%d, %.0f, %d\n", i, d[i], p[i]);
      //print the vertex, it's path wt and it's parent
   fprintf(ofile, "\n");
   #ifdef ALLSOURCES
      }
   #endif
#endif

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

