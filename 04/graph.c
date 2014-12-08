#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "boolean.h"
#include "graph.h"

#define MAXLINE 100
#define MAXV 1000000 /* Maximum number of vertices */

Adjlist *adjlist_new(int v, float weight){
   Adjlist * e;
   if((e = malloc(sizeof(Adjlist))) == NULL)
      return NULL;
   e->v = v;
   e->w = weight;
   e->next = NULL;
   return e;
}

void adjlist_destroy(Adjlist * a){
   Adjlist * tmp;
   while(a != NULL){
      tmp = a->next;
      free(a);
      a = tmp;
   }
}

int graph_init(Graph *G){
   int i;
   G->N = 0;
   G->E = 0;
   if((G->V = malloc(sizeof(Adjlist *)*MAXV))==NULL)
      return -1;
   if((G->degrees = malloc(sizeof(int)*MAXV))==NULL)
      return -1;
   for(i = 0; i < MAXV; i++){
      G->degrees[i] = 0;
      G->V[i] = NULL;
   }
   return 0;
}

int graph_add_edge(Graph *G, int source, int target, float weight){
   Adjlist *tmp;

   if(source >= G->N) G->N = source+1;
   if(target >= G->N) G->N = target+1;
   
   tmp = G->V[source];
   G->V[source] = adjlist_new(target, weight);
   G->V[source]->next = tmp;
   
}

int graph_read(Graph *G, FILE *fp){
   int u, v;
   float w;
   while(!feof(fp)){
      if(fscanf(fp, "%d %d %f", &u, &v, &w)!=3){
         fscanf(fp, "%*[^\n]");
         continue;
      }
      graph_add_edge(G, u, v, w);
   }
}

void graph_print(Graph *G){
   int i;
   Adjlist * a;
   for (i=0; i<G->N;){
      printf("%d : ", i);
      for(a = G->V[i]; a != NULL; a = a->next)
         printf("(%d,%.0f) ", a->v, a->w);
      printf("\n");
      i++;
   }
}


void graph_destroy(Graph *G){
   int i;
   Adjlist * a, *tmp;
   for (i=0; i<G->N;){
      adjlist_destroy(G->V[i]);
      i++;
   }
   free(G->V);
   free(G->degrees);
}

