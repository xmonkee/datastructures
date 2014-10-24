#define MAXARRAYLEN 10
#define MINARRAYLEN 3

typedef struct S1_ {
   double **L; //holds the L arrays
   int n; //number of arrays in L
   int *m; //number of elements in each array
} S1;

void s1_init(S1 *s1, double **L, int n, int m[]);
void s1_search(double *r, S1 *s1, double x);
