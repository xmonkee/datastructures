#include <stdlib.h>
#include <stdio.h>
#include "p1.h"

int binary_search(double *a, int size, double x){
   int max = size-1;
   int min = 0;
   int mid;
   while(max != min){
      mid = (max + min)/2;
      printf("%d %d %d\n", max, mid, min);
      if(a[mid] == x) return mid;
      if(a[mid] < x) min = mid-1;
      else max = mid;
   }
   return max;
}

void s1_init(S1 *s1, double **L, int n, int *m){
  s1->L = L;
  s1->n = n;
  s1->m = m;
}

void s1_search(double *r, S1 *s1, double x){
   for(int i=0; i<s1->n; i++)
      r[i] = s1->L[i][binary_search(s1->L[i], s1->m[i], x)];
}
  
