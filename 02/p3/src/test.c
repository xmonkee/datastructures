#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

void tree_print(Tree_node *node);

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

   printf("Ordered tree: ");
   tree_print(arr[7]);
   printf("\n");
   printf("isBST: %d\n" ,isBST(arr[7]));
   printf("isBST_recursive: %d\n" ,isBST_recursive(arr[7]));

   arr[11]->left = arr[5];
   arr[3]->right = arr[9];

   printf("Ordered tree: ");
   tree_print(arr[7]);
   printf("\n");
   printf("isBST: %d\n" ,isBST(arr[7]));
   printf("isBST_recursive: %d\n" ,isBST_recursive(arr[7]));
   return 1;
}

void tree_print(Tree_node *node){
   if(node->left!=NULL)
      tree_print(node->left);
   printf("%d ", node->data);
   if(node->right!=NULL)
      tree_print(node->right);
   return;
}


