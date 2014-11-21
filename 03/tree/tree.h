/** Red black self balancing tree */

typedef enum {RED, BLACK} Color;

typedef struct t_node_ {
   void * key;
   void * value;
   struct t_node_ * left;
   struct t_node_ * right;
   Color color;
} Tree_node;

typedef struct Tree_{
   Tree_node * root;
   void (*compare)(void *key1, void *key2);
   int (*print)(void *key, void *value);
} Tree;

/* tree functions */

int tree_init(Tree *tree, int(*compare)(void *key1, void *key2), 
      void (*print)(void *key, void *value));
void tree_destroy(Tree *tree);
int tree_insert(Tree *tree, void *key, void *value);
int tree_remove(Tree *tree, void *key, void **value);
int tree_lookup(Tree *tree, void *key, void **value);
int tree_height(Tree *tree);
