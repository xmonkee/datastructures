#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "graph.h"

#define MAXLINE 1000

Adjlist *adjlist_new(int v, float weight){
   Adjlist * e;
   if((e = malloc(sizeof(Adjlist))) == NULL)
      return NULL;
   e->v = v;
   e->w = weight;
   e->next = NULL;
   return e;
}

int graph_init(Graph *G){
   int i;
   G->N = 0;
   G->E = 0;
   if((G->V = malloc(sizeof(Adjlist *)*MAXV))==NULL)
      return -1;
   if((G->isVertex = malloc(sizeof(int)*MAXV))==NULL)
      return -1;
   if((G->degrees = malloc(sizeof(int)*MAXV))==NULL)
      return -1;
   for(i = 0; i < MAXV; i++){
      G->isVertex[i] = FALSE;
      G->degrees[i] = 0;
      G->V[i] = NULL;
   }
   return 0;
}

int graph_add_vertex(Graph *G, int u, Adjlist ** adjlist){

   Adjlist *tmp;

   //increase total vertices if adding to a new spot
   if(!(G->isVertex[u])){ 
      G->N++;
      G->isVertex[u] = TRUE;
   }
   
   //replace list and return the old list (for deletion etc)
   tmp = G->V[u];
   G->V[u] = *adjlist; 
   *adjlist = tmp;

   //update number of degrees
   G->degrees[u] = 0;
   for(tmp = G->V[u]; tmp != NULL; tmp = tmp->next)
      G->degrees[u]++;

   return 0;

}

int graph_read(Graph * G, FILE *f, int start){
   int i, u, v;
   float w;
   char *line, *tofree;
   Adjlist *head, *tail, *tmp;
   tofree = malloc(sizeof(char)*MAXLINE);
   while(!feof(f)){ //loops over each line
      line = tofree;
      fgets(line, MAXLINE, f);
      u = atoi(strsep(&line, " \n"));
      head = tail =  NULL;
      while(line != '\0' && strcmp(line, "")!=0){ //loop over each edge
         v = atoi(strsep(&line, " \n"));
         w = atof(strsep(&line, " "));
         if(head == NULL)
            head = tail = adjlist_new(v, w);
         else{
            tail->next = adjlist_new(v,w);
            tail = tail->next;
         }
      }
      graph_add_vertex(G, u, &head);
   }
   return 0;
} 

void graph_print(Graph *G){
   int i;
   Adjlist * a;
   for (i=0; i<G->N;){
      for(; !(G->isVertex[i]); i++) 
         ;
      printf("%d : ", i);
      for(a = G->V[i]; a != NULL; a = a->next)
         printf("(%d,%.0f) ", a->v, a->w);
      printf("\n");
      i++;
   }
}

