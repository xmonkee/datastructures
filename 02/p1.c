#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "p1.h"

int binary_search(double *a, size_t size, double x){
   int max = size;
   int min = 0;
   int mid;
   while(max > min){
      mid=(min+max)/2;
      if(a[mid]<x) min=mid+1;
      else max = mid;
   }
   return max;
}

void s1_init(S1 *s1, double **L, size_t n, size_t *m){
   int i;
   s1->L = malloc(sizeof(double*)*n);
   for(i=0; i < n; i++){
      s1->L[i] = malloc(sizeof(double)*(m[i]+1));
      memmove((void*)s1->L[i], (const void*)L[i], sizeof(double)*m[i]);
      s1->L[i][m[i]]=DBL_MAX;
   }
   s1->m = malloc(sizeof(size_t)*n);
   memmove((void*)s1->m, (const void*)m, sizeof(size_t)*n);
   s1->n = n;
}

void s1_search(size_t *results, S1 *s1, double x){
   int i;
   for(i=0; i<s1->n; i++)
      results[i] = binary_search(s1->L[i], s1->m[i], x);
}

void s1_destroy(S1 *s1){
   int i;
   for(i=0; i < s1->n; i++){
      free(s1->L[i]);
    }
   free(s1->L);
   free(s1->m);
   free(s1);
}
  
void s2_init(S2 *s2, double **L, size_t n, size_t *m){
   int i,j;
   int k; //stores total length of all L's
   size_t runningidx[n]; //keeps current index into all L's
   double tmp1, tmp2;
   int minidx; //index into runningidx
   for(i = k = 0; i < n; i++)
      k += m[i];
   s2->U = malloc(sizeof(double)*(k+1)); //k+1 because of sentinel
   s2->idx = malloc(sizeof(size_t*)*(k+1));
   for(j = 0; j < n; j++)
      runningidx[j] = 0; //initalize all indexes to 0
   for(i = 0; i < k+1; i++){
      minidx = 0;
      s2->idx[i] = malloc(sizeof(size_t)*n);
      for(j=0; j < n; j++){
         s2->idx[i][j] = runningidx[j];

         //posting sentinels
         tmp1 = L[j][runningidx[j]];
         if(runningidx[j]>=m[j]) tmp1=DBL_MAX;
         tmp2 = L[minidx][runningidx[minidx]];
         if(runningidx[minidx]>=m[minidx]) tmp2=DBL_MAX;

         if(tmp1 < tmp2)
            minidx = j; //find which array holds current minimum
      }
      s2->U[i] = L[minidx][runningidx[minidx]]; //put current minimum in U
      runningidx[minidx] += 1; //move on in that array
   }
   s2->k = k;
   s2->n = n;
}

void s2_search(size_t *results, S2 *s2, double x){
   int i;
   int s = binary_search(s2->U, s2->k, x);
   for(i=0; i < s2->n; i++)
      results[i] = s2->idx[s][i];
}

