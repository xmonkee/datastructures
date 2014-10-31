
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include "math.h"

typedef struct TN_wrapper{
   Tree_node *tn;
   float lower; 
   float upper; 
} TN_wrapper;


char* tnw_tostr(void * data){
   TN_wrapper * tnw = (TN_wrapper*)data;
   char *ret;
   if(tnw->tn == NULL)
      asprintf(&ret, "[%1.0f, %1.0f] null", tnw->lower, tnw->upper);
   else
      asprintf(&ret, "[%1.0f, %1.0f] %d", tnw->lower, tnw->upper, tnw->tn->data);
   return ret;
}

TN_wrapper * tnw_new(Tree_node * tn, float lower, float upper){
   TN_wrapper * new = malloc(sizeof(TN_wrapper));
   new->tn = tn; new->lower = lower, new->upper = upper;
   return new;
}

int main(){
   int i;
   const int tot = 15;
   Tree_node **arr = malloc(sizeof(Tree_node*)*tot);
   for(i = 0; i<tot; i++){
      arr[i] = malloc(sizeof(Tree_node));
      arr[i]->data = i;
      arr[i]->left = NULL;
      arr[i]->right = NULL;
   }
   arr[7]->left = arr[3]; arr[3]->left = arr[1]; arr[1]->left = arr[0];
   arr[1]->right = arr[2]; arr[3]->right=arr[5]; arr[5]->left=arr[4];
   arr[5]->right=arr[6]; arr[7]->right=arr[11]; arr[11]->left=arr[9];
   arr[9]->left=arr[8]; arr[9]->right=arr[10]; arr[11]->right=arr[13];
   arr[13]->left=arr[12]; arr[13]->right=arr[14];

   tree_print(arr[7]);
   printf("\n");
   printf("%d\n" ,isBST(arr[7]));
}


int isBST(Tree_node * tree){
   TN_wrapper * tnw = &(TN_wrapper){tree,-INFINITY, INFINITY};
   Stack *s = empty_stack(); //node stack
   s = stack_push(s, tnw);  
   while(!stack_is_empty(s)){
      stack_print(s, &tnw_tostr);
      printf("\n");
      tnw = stack_pop(&s);
      if(tnw->tn == NULL)
         continue;
      if(tnw->tn->data <= tnw->lower || tnw->tn->data >= tnw->upper)
         return 0;
      s = stack_push(s, tnw_new(tnw->tn->right, tnw->tn->data, tnw->upper));
      s = stack_push(s, tnw_new(tnw->tn->left, tnw->lower, tnw->tn->data));
   }
   return 1;
} 


