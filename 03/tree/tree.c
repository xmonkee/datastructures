#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "tree.h"

/** Red black self balancing tree */

void tree_balance_insert(Tree *tree, Tree_node *node);
void tree_left_rotate(Tree *tree, Tree_node *node);
void tree_right_rotate(Tree *tree, Tree_node *node);

Tree_node *tree_new_node(void *key, void *value, void(*print)(void*key, void*value)){
   Tree_node *node;
   if((node = malloc(sizeof(Tree_node)))==NULL)
      return NULL;
   node->left = node->right = node->parent = NULL;
   node->key = strdup(key);
   node->value = strdup(value);
   node->color = RED;
   node->print = print;
   return node;
}

void tree_node_print(Tree_node * node, int depth){
   int i;
   if(node==NULL) return;
   for(i=0; i<depth; i++) printf(" ");
   printf("%d", node->color);
   node->print(node->key, node->value);
   tree_node_print(node->left, depth+1);
   tree_node_print(node->right, depth+1);
}
void tree_node_print_inorder(Tree_node * node){
   if(node==NULL) return;
   tree_node_print_inorder(node->left);
   node->print(node->key, node->value);
   tree_node_print_inorder(node->right);
}

void tree_print_tree(Tree *tree){
   tree_node_print(tree->root, 0);
}
void tree_print_inorder(Tree *tree){
   tree_node_print_inorder(tree->root);
}

int tree_init(Tree *tree, int(*compare)(void *key1, void *key2), 
      void(*print)(void *key, void *value)){
   Tree_node * nil = malloc(sizeof(Tree_node));
   tree->root = NULL;
   tree->compare = compare;
   tree->print = print;
   nil->left = nil->right = nil->parent = NULL;
   nil->color = BLACK;
   nil->key = nil->value = NULL;
   nil->print = NULL;
   tree->nil = nil;
   return 0;
}

int tree_insert(Tree *tree, void *key, void *value){
   Tree_node *new_node, *node, *parent;
   int left;
   if((new_node = tree_new_node(key, value, tree->print))==NULL)
      return -1;
   if(tree->root == NULL){ //tree is emtpy
         new_node->color = BLACK;
         tree->root = new_node;
         return 0;
      } else { //tree is not empty
         node = tree->root;
         while(node != NULL){ //we search the tree
            if(tree->compare(key, node->key) == 0){ //key already present 
               return 1;
            }
            parent = node;
            if(tree->compare(key, parent->key) < 0){
               node = parent->left;
               left = 1;
            } else {
               node = parent->right;
               left = 0;
            }
         } // we find the insertable location
         if(left){
            parent->left = new_node;
            new_node->parent = parent;
         } else {
            parent->right = new_node;
            new_node->parent = parent;
         }

         //Now for balancing
         tree_balance_insert(tree, new_node);
         return 0;
   }
}

int tree_remove(Tree *tree, void *key, void **value){
   Tree_node * tmp_node;
   int left;
   if(tree_lookup(tree, key, value)!=0)
      return 1;
   Tree_node *node = tree->root;
   while(tree->compare(node->key, key)!=0){
     if(tree->compare(key, node->key) < 0){
        left = 1;
        node = node->left;
     } else{
        left = 0;
        node = node->right;
     }
   }

   *value = node->value; //return deleted value 
   //Now we delete

   //Outer node
   if(node->left == NULL && node->right == NULL){
      if(tree->root == node){ //node is root
         tree->root = NULL;
      } else {
         if(left) node->parent->left = NULL;
         else node->parent->right = NULL;
      }
      free(node->key);
      free(node);
   }
   //No left child
   else if(node->left == NULL){
      free(node->key);
      tmp_node = node->right;
      node->key = node->right->key;
      node->value = node->right->value;
      node->left = node->right->left;
      node->right = node->right->right;
      free(tmp_node);
   }
   //No right child
   else if(node->right == NULL){
      free(node->key);
      tmp_node = node->left;
      node->key = node->left->key;
      node->value = node->left->value;
      node->right = node->left->right;
      node->left = node->left->left;
      free(tmp_node);
   }
   else { //translpant the smallest right descendant
      tmp_node = node->right;
      while(tmp_node->left != NULL){
         tmp_node = tmp_node->left;
      }
      free(node->key);
      node->key = tmp_node->key;
      node->value = tmp_node->value;
      if(tmp_node->parent == node){
         node->right = NULL;
      } else {
         tmp_node->parent->left = NULL;
      }

      free(tmp_node);
   }
   return 0;
   
}

int tree_lookup(Tree *tree, void *key, void **value){
   Tree_node *node = tree->root;
   if(node==NULL) return 1;
   while(tree->compare(node->key, key)!=0){
     if(tree->compare(key, node->key) < 0)
        node = node->left;
     else
        node = node->right;
     if(node == NULL) return 1;
   }
   *value = node->value;
   return 0;
}
int tree_height(Tree *tree){}
void tree_destroy(Tree *tree){}

void tree_balance_insert(Tree *tree, Tree_node *node){
   Tree_node *parent, *uncle, *gp;
   if(tree->root == node){ //Case 1: red or black root
      node->color = BLACK;
      return;
   }
   if(node->parent->color == BLACK)
      return;
   else{ //red parent
      parent = node->parent;
      gp = node->parent->parent;
      uncle = (node->parent == gp->right)? gp->left : gp->right;
      if(uncle->color == RED){ //Case 3, both parent and uncle red
         node->parent->color = BLACK;
         uncle->color = BLACK;
         gp->color = RED;
         tree_balance_insert(tree, gp);
         return;
      } else { //case 4 and case 5, red parent, black uncle
      /*   if(node==parent->left && parent==gp->left){ //case 5.1
            parent->color = BLACK;
            gp->color = RED;
     */ } 
   }

}
void tree_left_rotate(Tree *tree, Tree_node *node){}
void tree_right_rotate(Tree *tree, Tree_node *node){}