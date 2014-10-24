#include <stdlib.h>
#include <stdio.h>
#include "p1.h"

int binary_search(double *a, size_t size, double x){
   int max = size-1;
   int min = 0;
   int mid;
   while(max > min){
      mid=(min+max)/2;
      if(a[mid]<x)min=mid+1;
      else max = mid;
   }
   return max==min && a[min] >= x ? min : size;
}

void s1_init(S1 *s1, double **L, size_t n, size_t *m){
  s1->L = L;
  s1->n = n;
  s1->m = m;
}

void s1_search(size_t *r, S1 *s1, double x){
   for(int i=0; i<s1->n; i++)
      r[i] = binary_search(s1->L[i], s1->m[i], x);
}
  
