#include<stdio.h>
#include<stdlib.h>
#define MAXV 1000
#define TRUE 1
#define FALSE 0
#define MAXINT 10000000

typedef struct edgenode {
  int y;
  int weight;
  struct edgenode *next;
} edgenode;

typedef struct {
  edgenode *edges[MAXV+1];
  int degree[MAXV+1];
  int nvertices;
  int nedges;
  int directed;
} graph;

void dijkstra(graph *g, int start, int *distance){
  int i;
  edgenode *p;
  int processed[MAXV+1];
  int v;
  int w;
  int weight;
  int dist;
  
  for (i=1; i<=g->nvertices; i++) {
    processed[i] = FALSE;
    distance[i] = MAXINT;
  }
  distance[start] = 0;
  v = start;
  
  /* add v to processed list and update distance of neighbors */
  while (processed[v] == FALSE) {
    processed[v] = TRUE;
    p = g->edges[v];
    while (p != NULL) {
      w = p->y;
      weight = p->weight;
      if (distance[w] > (distance[v]+weight)) 
        distance[w] = distance[v]+weight;
      p = p->next;
    }


    /* find next closest vertex */
    for (i=1,v=1,dist=MAXINT; i<=g->nvertices; i++)
      if ((processed[i] == FALSE) && (dist > distance[i])) {
	dist = distance[i];
	v = i; 
      }
  }
}
