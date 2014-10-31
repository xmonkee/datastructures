typedef struct Tree_node{
     struct Tree_node *left, *right;
       int data;
} Tree_node;

void tree_print(Tree_node *node);
