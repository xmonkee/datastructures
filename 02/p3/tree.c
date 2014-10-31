#include <stdlib.h>
#include <stdio.h>
#include "tree.h"


void tree_print(Tree_node *node){
   if(node->left!=NULL)
      tree_print(node->left);
   printf("%d ", node->data);
   if(node->right!=NULL)
      tree_print(node->right);
   return;
}


