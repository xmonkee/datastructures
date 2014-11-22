#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "dict.h"

/*t_node refers to the tree, not a node. Apologies for confusing 
 * nomenclature */

int compare(void *key1, void *key2){
   return strcmp((char*)key1, (char*)key2);
}

void print(void *key, void *value){
  // printf("%s: %s\n", (char*)key, (char*)value);
  printf("%s\n", (char*)key);
}

t_node *t_init(void){
   t_node *tree = malloc(sizeof(t_node));
   tree_init(tree, compare, print);
   return tree;
}
int t_insert(t_node *tree, char *key, char *value){
   int error_code;
   error_code = tree_insert(tree, (void*)key, (void*)value);
   return error_code;
}
int t_delete(t_node *tree, char *key){
   char *def;
   int error_code;
   error_code=tree_remove(tree, (void*)key, (void**)&def);
   if(error_code == 0) free(def);
   return error_code;
}

char *t_find(t_node *tree, char *key){
   char *value;
   int error_code;
   if((error_code = tree_lookup(tree, key, (void**)&value))!=0)
      return NULL;
   else
      return value;
}

int t_print(t_node *tree){
  tree_print_tree(tree);
  // tree_print_inorder(tree);  
}
int t_print_range(t_node *tree, char *word1, char *word2){}
int t_height(t_node *tree){}
void t_destroy(t_node *tree){}
