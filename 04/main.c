#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "dijkstra.h"

//#define VERBOSE

void run_single_source(Graph *G, int source);
void run_all_sources(Graph *G);

int main(int argc, char ** argv){

   FILE *f;
   Graph * G;

   if(argc < 2){
      printf("Please supply filename \n");
      return 1;
   }

   if((f = fopen(argv[1], "r"))==NULL){
      printf("Can't open file\n");
      return -1;
   }
   
   G = malloc(sizeof(Graph));
   graph_init(G);
   graph_read(G, f); //read graph from input file

#ifdef VERBOSE
   graph_print(G); //display graph
#endif


   run_all_sources(G); 

   
   graph_destroy(G);
   free(G);

}

void run_single_source(Graph *G, int source){
   int i, tmp;
   int N = graph_vertices(G);
   float *d = malloc(sizeof(float)*N); //distance array
   int *p = malloc(sizeof(int*)*N); //parent array
   dijkstra_single_source(G, source, d, p); //Run Dijsktra


#ifdef VERBOSE
   printf("Source %d\n", source);
   for(i = 0; i<graph_vertices(G); i++) 
      printf("(%d, %.0f, %d) ", i, d[i], p[i]);
      //print the vertex, it's path wt and it's parent
   printf("\n");
#endif


   free(d);
   free(p);
}


void run_all_sources(Graph *G){
   int i;
#pragma omp parallel for
   for(i = 0; i<G->N; i++){
      run_single_source(G, i);
   }

}

