/* Header file for graph data structure.  The graph datastructure holds an
 * array of adjlists. The adjlist at index i represents the vertices adjacent
 * to node i. Every adjlist is a linked list, with each node containing an int
 * v that represents an edge from i to v, an float w that represents the weight
 * of edge (i, v) and a link to the next node on the list. 
 */

#include <stdio.h>
#define MAXV 10

typedef struct Adjlist {
   int v; 
   float w;
   struct Adjlist * next;
} Adjlist;

typedef struct Graph {
   Adjlist ** V; //array of Adjlists
   int * isVertex; //keeps track of locations where there's a vertex
   int * degrees; //keeps track of number of edges for each vertex
   int N; //number of vertices
   int E; //number of edges
} Graph;


int graph_init(Graph * G); //returns an empty graph
int graph_read_from_file(Graph * G, FILE * f); 
int graph_add_vertex(Graph * G, int u, Adjlist ** adjlist); 
Adjlist * adjlist_new(int v, float weight);
//adds new Adjlist at vertex u, replacing theh old one if there was any


#define graph_vertices(G) ((G)->N)
#define graph_edges(G) ((G)->E)
#define graph_degrees(G, u) ((G)->degrees[u])
#define graph_is_vertex(G, u) ((G)->isVertex[u])
#define graph_adjlist(G, u) ((G)->V[(u)])
#define edge_next(a) ((a)->next)
#define edge_target(a) ((a)->v)
#define edge_weight(a) ((a)->w)
