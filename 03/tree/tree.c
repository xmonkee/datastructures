#include<stdlib.h>
#include<stdio.h>
#include "tree.h"

/** Red black self balancing tree */

Tree_node *tree_new_node(void *key, void *value, void(*print)(void*key, void*value)){
   Tree_node *node;
   if((node = malloc(sizeof(Tree_node)))==NULL)
      return NULL;
   node->left = node->right = node->parent = NULL;
   node->key = key;
   node->value = value;
   node->color = RED;
   node->print = print;
   return node;
}

void tree_node_print(Tree_node * node, int depth){
   int i;
   //printf("%.*s", depth, " ");
   node->print(node->key, node->value);
   //add recursive call
}

void tree_print_tree(Tree *tree){
   tree_node_print(tree->root, 0);
}


int tree_init(Tree *tree, int(*compare)(void *key1, void *key2), 
      void(*print)(void *key, void *value)){
   tree->root = NULL;
   tree->compare = compare;
   tree->print = print;
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
         } else {
            parent->right = new_node;
         }
         return 0;
   }
}

int tree_remove(Tree *tree, void *key, void **value){}
int tree_lookup(Tree *tree, void *key, void **value){}
int tree_height(Tree *tree){}
void tree_destroy(Tree *tree){}
