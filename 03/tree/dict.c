#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "dict.h"

/*t_node refers to the tree, not a node. Apologies for confusing 
 * nomenclature */
FILE * logger;

int compare(void *key1, void *key2){
   return strcmp((char*)key1, (char*)key2);
}

void print(void *key, void *value){
  printf("%s: %s\n", (char*)key, (char*)value);
}

t_node *t_init(void){
   t_node *tree = malloc(sizeof(t_node));
   tree_init(tree, compare, print);
   if(LOG){
      logger = fopen(LOGFILE, "w");
   }
   return tree;
}
int t_insert(t_node *tree, char *key, char *value){
   int error_code;
   error_code = tree_insert(tree, (void*)key, (void*)value);
   if(LOG){
      fprintf(logger, "Added %s. Tree Height %d\n", key, tree_height(tree, tree->root));
   }
   return error_code;
}
int t_delete(t_node *tree, char *key){
   char *def;
   int error_code;
   error_code=tree_remove(tree, (void*)key, (void**)&def);
   if(error_code == 0) free(def);
   if(LOG){
      fprintf(logger, "Deleted %s. Tree Height %d\n", key, tree_height(tree, tree->root));
   }
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

int t_print_tree(t_node *tree){
  tree_print_tree(tree);
}
int t_print(t_node *tree){
  tree_print_inorder(tree);  
}
int t_print_range(t_node *tree, char *word1, char *word2){
   tree_print_range(tree, (void *)word1, (void *)word2);
}
void t_destroy(t_node *tree){ 
   fclose(logger);
   tree_destroy(tree);
}
