#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include "math.h"

typedef struct TN_wrapper{
   Tree_node *tn;
   float lower, upper; 
} TN_wrapper;


char* tnw_tostr(void * data){
   TN_wrapper * tnw = data;
   char *ret;
   asprintf(&ret, "[%1.0f, %1.0f] %d", tnw->lower, tnw->upper, tnw->tn->data);
   return ret;
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
   arr[7]->left = arr[3];
   arr[3]->left = arr[1];
   arr[1]->left = arr[0];
   arr[1]->right = arr[2];
   arr[3]->right=arr[5];
   arr[5]->left=arr[4];
   arr[5]->right=arr[6];
   arr[7]->right=arr[11];
   arr[11]->left=arr[9];
   arr[9]->left=arr[8];
   arr[9]->right=arr[10];
   arr[11]->right=arr[13];
   arr[13]->left=arr[12];
   arr[13]->right=arr[14];

   printf("%d\n" ,isBST(arr[7]));
}

int isBST(Tree_node * tree){
   Stack *s = empty_stack();
   TN_wrapper * tnw = malloc(sizeof(TN_wrapper));
   TN_wrapper *leftw, *rightw;
   tnw->tn = tree;
   tnw->lower = -INFINITY;
   tnw->upper = INFINITY;
   s = stack_push(s, tnw);
   while(!stack_is_empty(s)){
      stack_print(s, tnw_tostr);
      printf("\n");
      tnw = stack_pop(&s);
      if(tnw->tn->left != NULL){//Left Node exists
         if(!(tnw->tn->left->data > tnw->lower))
            //left node is not larger than left interval bound
            return 0;
         if(!(tnw->tn->left->data < tnw->tn->data))
            //left node is not smaller than curret node
            return 0;
         //push left node onto stack;
         leftw = malloc(sizeof(TN_wrapper));
         leftw->tn = tnw->tn->left;
         leftw->lower = tnw->lower;
         leftw->upper = tnw->tn->data;
         s = stack_push(s, leftw);
      }
         
      if(tnw->tn->right != NULL){//Right Node exists
         if(!(tnw->tn->right->data < tnw->upper))
            //right node is not smaller than right interval bound
            return 0;
         if(!(tnw->tn->right->data > tnw->tn->data))
            //right node is not bigger than curret node
            return 0;
         //push right node onto stack;
         rightw = malloc(sizeof(TN_wrapper));
         rightw->tn = tnw->tn->right;
         rightw->upper = tnw->upper;
         rightw->lower = tnw->tn->data;
         s = stack_push(s, rightw);
      }
   }
   return 1;
} 


