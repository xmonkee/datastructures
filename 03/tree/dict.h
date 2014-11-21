/** interface between interactive layer and red-black tree */

#include "tree.h"

typedef Tree t_node;

/* tree functions */

t_node *t_init(void);
void t_destroy(t_node *node);
int t_insert(t_node *node, char *key, char *value);
int t_delete(t_node *node, char *key);
char *t_find(t_node *node, char *key);
int t_print(t_node *node);
int t_print_range(t_node *node, char *word1, char *word2);
int t_height(t_node *node);
