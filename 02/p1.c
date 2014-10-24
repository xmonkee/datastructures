#include <stdlib.h>
#include <stdio.h>
#include "p1.h"

int binary_search(double *a, size_t size, double x){
   int max = size;
   int min = 0;
   int mid;
   while(max > min){
      mid=(min+max)/2;
      if(a[mid]<x)min=mid+1;
      else max = mid;
   }
   return max;
}

void s1_init(S1 *s1, double **L, size_t n, size_t *m){
  s1->L = L;
  s1->n = n;
  s1->m = m;
}

void s1_search(size_t *r, S1 *s1, double x){
   int i;
   for(i=0; i<s1->n; i++)
      r[i] = binary_search(s1->L[i], s1->m[i], x);
}
  
void s2_init(S2 *s2, double **L, size_t n, size_t *m){
   int i,j;
   int k; //stores total length of all L's
   size_t runningidx[n]; //keeps current index into all L's
   int minidx; //index into runningidx
   for(i = k = 0; i < n; i++)
      k += m[i];
   s2->U = malloc(sizeof(double)*k);
   s2->idx = malloc(sizeof(size_t*)*k);
   for(j = 0; j < n; j++)
      runningidx[j] = 0; //initalize all indexes to 0
   for(i = 0; i < k; i++){
      minidx = 0;
      s2->idx[i] = malloc(sizeof(size_t)*n);
      for(j=0; j < n; j++){
         s2->idx[i][j] = runningidx[j];
         if(L[j][runningidx[j]] < L[minidx][runningidx[minidx]])
            minidx = j; //find which array holds current minimum
      }
      s2->U[i] = L[minidx][runningidx[minidx]]; //put current minimum in U
      runningidx[minidx] += 1; //move on in that array
   }
   s2->k = k;
}

void s2_search(size_t *r, S2 *s2, double x){
   int i = binary_search(s2->U, s2->k, x);
}
