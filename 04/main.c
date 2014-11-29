#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <math.h>

void init_single_source(Graph *G, int s, float *d, int *p, 
      boolean *processed);
float *dijkstra_single_source(Graph *G, int s);
int get_min(float *d, boolean *processed, int N);

int main(int argc, char ** argv){

   FILE *f;
   Graph * G;
   float *d;
   int i;

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
   graph_read(G, f);
   graph_print(G);
   printf("%d\n", graph_vertices(G));

   d = dijkstra_single_source(G, 0);
   for(i = 0; i<graph_vertices(G); i++)
      printf("%.0f ", d[i]);
   printf("\n");
}

float *dijkstra_single_source(Graph *G, int s){
   
   int nprocessed = 0;
   int N = graph_vertices(G);
   int u, v;
   Adjlist *edge;
   float *d = malloc(sizeof(float)*N); //distance array
   int *p = malloc(sizeof(int*)*N); //parent array
   boolean *processed = malloc(sizeof(boolean)*N);

   init_single_source(G, s, d, p, processed); 
   while (nprocessed < N){
      u = get_min(d, processed, N);
      for(edge = graph_adjlist(G,u); edge != NULL; edge = edge_next(edge)){
         v = edge_target(edge);
         if(d[v] > d[u] + edge_weight(edge)){
            d[v] = d[u] + edge_weight(edge);
            p[v] = u;
         }
      }
      processed[u] = TRUE;
      nprocessed++;
   }
   return d;
}

void init_single_source(Graph *G, int s, float *d, int *p, boolean *processed){
   int i;
   for(i=0; i<graph_vertices(G); i++){
      d[i] = INFINITY;
      p[i] = -1;
      processed[i] = FALSE;
   }
   d[s] = 0;
   return;
}

int get_min(float *d, boolean *processed, int N){
   int i;
   float min = INFINITY;
   int minidx;
   for(i=0; i<N; i++){
      if(!processed[i] && d[i] < min){
         min = d[i];
         minidx = i;
      }
   }
   return minidx;
}
