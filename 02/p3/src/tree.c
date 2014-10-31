#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "stack.h"
#include "tnw.h"
#include "math.h"

static int isBST_r(Tree_node * tree, float lower, float upper);

int isBST(Tree_node * tree){
   TN_wrapper * tnw;
   tnw = tnw_new(tree, -INFINITY, INFINITY);
   Stack *s = empty_stack(); 
   s = stack_push(s, tnw);  
   while(!stack_is_empty(s)){
      if(DEBUG){stack_print(s, &tnw_tostr); printf("\n");}
      tnw = stack_pop(&s);
      if(tnw->tn == NULL)
         continue;
      if(tnw->tn->data <= tnw->lower || tnw->tn->data >= tnw->upper)
         return 0;
      s = stack_push(s, tnw_new(tnw->tn->right, tnw->tn->data, tnw->upper));
      s = stack_push(s, tnw_new(tnw->tn->left, tnw->lower, tnw->tn->data));
      free(tnw);
   }
   return 1;
} 

int isBST_recursive(Tree_node * tree){
   return isBST_r(tree, -INFINITY, INFINITY);
}

static int isBST_r(Tree_node * tree, float lower, float upper){
   if(tree==NULL) return 1;
   if(tree->data <= lower || tree->data >= upper)
      return 0;
   return (isBST_r(tree->left, lower, (float)tree->data) &&
      isBST_r(tree->right, (float)tree->data, upper));
}

