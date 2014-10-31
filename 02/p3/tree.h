typedef struct Tree_node{
     struct Tree_node *left, *right;
       int data;
} Tree_node;

#define DEBUG 0 //make 1 to see stack activity

int isBST(Tree_node *tree);
int isBST_recursive(Tree_node *tree);
static int isBST_r(Tree_node *tree, float lower, float upper);
