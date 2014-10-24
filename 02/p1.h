#define MAXARRAYLEN 10
#define MINARRAYLEN 3
#define MAXL 100

typedef struct S1_ {
   double **L; //holds the L arrays
   size_t n; //number of arrays in L
   size_t *m; //number of elements in each array
} S1;

void s1_init(S1 *s1, double **L, size_t n, size_t *m);
void s1_search(size_t *r, S1 *s1, double x);
