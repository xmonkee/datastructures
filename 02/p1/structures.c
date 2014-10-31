#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "structures.h"

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
   long size=0;
   int i;
   s1->L = newlloc(sizeof(double*)*n);
   for(i=0; i < n; i++){
      s1->L[i] = newlloc(sizeof(double)*(m[i]));
      memmove((void*)s1->L[i], (const void*)L[i], sizeof(double)*m[i]);
   }
   s1->m = newlloc(sizeof(size_t)*n);
   memmove((void*)s1->m, (const void*)m, sizeof(size_t)*n);
   s1->n = n;
   printf("Size usage (in MB): %f\n", (float)size/MEGABYTE);
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
   long size=0;
   int i,j;
   int k; //stores total length of all L's
   size_t runningidx[n]; //keeps current index into all L's
   double tmp1, tmp2;
   int minidx; //index into runningidx
   for(i = k = 0; i < n; i++)
      k += m[i];
   s2->U = newlloc(sizeof(double)*(k)); //k+1 because of sentinel
   s2->idx = newlloc(sizeof(size_t*)*(k));
   for(j = 0; j < n; j++)
      runningidx[j] = 0; //initalize all indexes to 0
   for(i = 0; i < k+1; i++){
      minidx = 0;
      s2->idx[i] = newlloc(sizeof(size_t)*n);
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
   printf("Size usage (in MB): %f\n", (float)size/MEGABYTE);
}

void s2_search(size_t *results, S2 *s2, double x){
   int i;
   int s = binary_search(s2->U, s2->k, x);
   for(i=0; i < s2->n; i++)
      results[i] = s2->idx[s][i];
}

void s2_destroy(S2 *s2){
   int i;
   free(s2->U);
   for(i=0; i<s2->k+1; i++)
      free(s2->idx[i]);
   free(s2->idx);
   free(s2);
}
   
void s3_init(S3 *s3, double** L, size_t n, size_t *m){
   long size=0;
   int i,j,k,l,comp,len;
   double tmp1, tmp2;
   double **M = newlloc(sizeof(double*)*n);
   size_t **p1 = newlloc(sizeof(size_t*)*n);
   size_t **p2 = newlloc(sizeof(size_t*)*n);
   size_t *Msize = newlloc(sizeof(size_t)*n);

   //We initialize the last (un)augmented array
   M[n-1] = newlloc(sizeof(double)*(m[n-1]+1));
   p1[n-1] = newlloc(sizeof(size_t)*(m[n-1]+1));
   p2[n-1] = newlloc(sizeof(size_t)*(m[n-1]+1));
   Msize[n-1]=0;
   Msize[n-1] = len = m[n-1];
   for(i=0; i<len+1; i++){
      tmp1 = L[n-1][i];
      if(i==len) tmp1 = DBL_MAX;
      M[n-1][i] = tmp1;
      p1[n-1][i] = i;
      p2[n-1][i] = 0;
   }

   for(i=n-2; i>=0; i--){
      j = k = 0;
      l=1;
      Msize[i] = len = m[i]+Msize[i+1]/2;
      M[i] = newlloc(sizeof(double)*(len+1));
      p1[i] = newlloc(sizeof(size_t)*(len+1));
      p2[i] = newlloc(sizeof(size_t)*(len+1));
      for(j=0; j< len+1; j++){
         tmp1 = k < m[i] ? L[i][k] : DBL_MAX;
         tmp2 = l < Msize[i+1] ? M[i+1][l] : DBL_MAX;
         comp = tmp1 <= tmp2;
         M[i][j] = comp ? tmp1 : tmp2;
         p1[i][j] = k;
         p2[i][j] = l;
         k += comp? 1 : 0;
         l += comp? 0 : 2;
      }
   }

   s3->M = M;
   s3->Msize = Msize;
   s3->p1 = p1;
   s3->p2 = p2;
   s3->n = n;
   printf("Size usage (in MB): %f\n", (float)size/MEGABYTE);
}
   
void s3_search(size_t *result, S3 *s3, double x){
   int i, p, len;
   p = binary_search(s3->M[0], s3->Msize[0], x);
   for(i=0; i < s3->n; i++){
      if(s3->M[i][p-1] >= x) p = p-1 ;
      result[i] = s3->p1[i][p];
      p = s3->p2[i][p];
   }
}

void s3_destroy(S3 *s3){
   int i;
   for(i=0;i<s3->n;i++){
      free(s3->M[i]);
      free(s3->p1[i]);
      free(s3->p2[i]);
   }
   
   free(s3->M);
   free(s3->Msize);
   free(s3->p1);
   free(s3->p2);
   free(s3);
}

