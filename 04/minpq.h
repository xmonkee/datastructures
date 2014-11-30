/* Minimum priority queue */


typedef struct {
   //member name is represented by integer index into d
   int N; //number of total memebers
   boolean *extracted; //array indicating which members have been extracted
   int nextracted; //number of values extracted
   float *values; //values of members
} PQ;

