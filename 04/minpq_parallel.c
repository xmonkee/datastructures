#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "boolean.h"
#include "graph.h"
#include "minpq.h"


/* A minimum priority queue implemented with a simple array, 
 * *NOT* a binary heap 
 */

int pq_init(PQ *pq, float *d, int N){

   boolean *extracted = malloc(N*sizeof(boolean));

   int i;

   for(i=0; i<N; i++){
      extracted[i] = FALSE;
   }

#pragma omp parallel
   {
#pragma omp master
      {
         printf("Number of threads: %d\n", omp_get_num_threads());
      }
   }

   pq->extracted = extracted;
   pq->nextracted = 0;
   pq->values = d;
   pq->N = N;
   return 0;
}


int pq_extract_min(PQ *pq){
   int i;
   float min, min_g;
   int minidx, minidx_g;
   boolean found_any=FALSE;
   boolean found_any_g = FALSE;
#pragma omp parallel default(none) \
   shared(pq, min_g, minidx_g, found_any_g) \
   private(i, min, minidx) firstprivate(found_any)
   {

#pragma omp for
      /* Here is the parallelization. Each thread looks for the minimum 
       * in a subset of the array */
      for(i=0; i<pq->N; i++){
         if(!(pq->extracted[i])){
            if(!found_any){ //to assign at least one value to min
               min = pq->values[i];
               minidx = i;
               found_any = TRUE;
            } else if(pq->values[i] < min) {
               min = pq->values[i];
               minidx = i;
            }
         }
      }
#pragma omp critical
      /** This is where the global minimum is synchornized. We take 
       * care that only the threads that actually found a minimum 
       * take part in this region. It's basically a reduce 
       * of the minimization. 
       * Since the queue is not yet empty, at least one thread
       * is guaranteed to find a minimum */
      {
        if(found_any){
          if(!found_any_g){
            min_g = min;
            minidx_g = minidx;
            found_any_g = TRUE;
          } else if(min < min_g) {
            min_g = min;
            minidx_g = minidx;
          } 
        } 
      }
   }
   pq->nextracted++;
   pq->extracted[minidx_g] = TRUE;
   return minidx_g;
}

boolean pq_is_empty(PQ *pq){
   return (pq->nextracted == pq->N);
}

void pq_destroy(PQ *pq){
   free(pq->extracted);
}


