#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "graph.h"
#include "minpq.h"

int pq_init(PQ *pq, float *d, int N){

   boolean *extracted = malloc(N*sizeof(boolean));
   

   int i;
   for(i=0; i<N; i++){
      extracted[i] = FALSE;
   }

   pq->extracted = extracted;
   pq->nextracted = 0;
   pq->values = d;
   pq->N = N;
   return 0;
}


int pq_extract_min(PQ *pq){
   int i;
   float min;
   int minidx;
   boolean found_any=FALSE;
   for(i=0; i<pq->N; i++){
      if(!(pq->extracted[i])){
         if(!found_any){ //to assign at least one value to min
            minidx = i;
            min = pq->values[i];
            found_any = TRUE;
         }
         if(pq->values[i] < min){
            min = pq->values[i];
            minidx = i;
         }
      }
   }
   pq->nextracted++;
   pq->extracted[minidx] = TRUE;
   return minidx;
}

boolean pq_is_empty(PQ *pq){
   return (pq->nextracted == pq->N);
}

void pq_destroy(PQ *pq){
   free(pq->extracted);
}


