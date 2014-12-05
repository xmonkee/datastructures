#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "graph.h"
#include "dijkstra.h"
#include "minpq.h"

void init_single_source(Graph *G, int s, float *d, int *p){
   int i;
   for(i=0; i < graph_vertices(G); i++){
      d[i] = INFINITY;
      p[i] = -1;
   }
   d[s] = 0;
   return;
}



void dijkstra_single_source(Graph *G, int s, float *d, int *p){
   
   int N = graph_vertices(G);
   int u, v;
   Adjlist *edge;
   PQ *Q = malloc(sizeof(PQ)); //create Queue

   init_single_source(G, s, d, p);
   pq_init(Q, d, N);
   
   while (!pq_is_empty(Q)){
      u = pq_extract_min(Q);
      for(edge = graph_adjlist(G,u); edge != NULL; 
            edge = edge_next(edge)){
         v = edge_target(edge);
         if(d[v] > d[u] + edge_weight(edge)){
            d[v] = d[u] + edge_weight(edge);
            p[v] = u;
         }
      }
   }
   pq_destroy(Q);
   free(Q);
}

