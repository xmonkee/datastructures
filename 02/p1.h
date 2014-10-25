#define MAXARRAYLEN 10
#define MINARRAYLEN 3
#define MAXL 100

typedef struct S1_ {
   double **L; //holds the L arrays
   size_t n; //number of arrays in L
   size_t *m; //number of elements in each array
} S1;

typedef struct S2_ {
   double *U; //holds the union array
   size_t **idx; //holds indices into L
   size_t n; //number of sub arrays
   size_t k; //size of U
} S2;

typedef struct S3_ {
   double **M; //holds the M arrays
   size_t **p1; 
   size_t **p2;
} S3;

void s1_init(S1 *s1, double **L, size_t n, size_t *m);
void s1_search(size_t *result, S1 *s1, double x);
void s1_destroy(S1 *s1);

void s2_init(S2 *s2, double **L, size_t n, size_t *m);
void s2_search(size_t *result, S2 *s2, double x);

