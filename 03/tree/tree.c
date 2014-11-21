#include<stdlib.h>
#include "tree.h"

/** Red black self balancing tree */


int tree_init(Tree *tree, int(*compare)(void *key1, void *key2), 
      void(*print)(void *key, void *value)){
  tree 
}
void tree_destroy(Tree *root){}
int tree_insert(Tree *root, void *key, void *value){}
int tree_remove(Tree *root, void *key, void **value){}
int tree_lookup(Tree *root, void *key, void **value){}
int tree_height(Tree *root){}
