#define MAXL 200
#define newlloc(s) malloc((s)); size+=(s);
#define MEGABYTE 1000000

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
   size_t *Msize; //holds size of each M
   size_t **p1; 
   size_t **p2;
   size_t n; //number of arrays
} S3;

void s1_init(S1 *s1, double **L, size_t n, size_t *m);
void s1_search(size_t *results, S1 *s1, double x);
void s1_destroy(S1 *s1);

void s2_init(S2 *s2, double **L, size_t n, size_t *m);
void s2_search(size_t *results, S2 *s2, double x);
void s2_destroy(S2 *s2);

void s3_init(S3 *s3, double **L, size_t n, size_t *m);
void s3_search(size_t *results, S3 *s3, double x);
void s3_destroy(S3 *s3);
