#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "tnw.h"

TN_wrapper * tnw_new(Tree_node * tn, float lower, float upper){
   TN_wrapper * new = malloc(sizeof(TN_wrapper));
   new->tn = tn; new->lower = lower, new->upper = upper;
   return new;
}

char* tnw_tostr(void * data){
   TN_wrapper * tnw = (TN_wrapper*)data;
   char *ret;
   if(tnw->tn == NULL)
      asprintf(&ret, "[%1.0f, %1.0f] null", tnw->lower, tnw->upper);
   else
      asprintf(&ret, "[%1.0f, %1.0f] %d", tnw->lower, tnw->upper, tnw->tn->data);
   return ret;
}

