#define MAXLEN 1100


typedef struct d_node{
   char *word;
   struct d_node *left;
   struct d_node *right;
} d_node;

d_node *d_init(void);
int d_insert(d_node *node, char *word, char *def);
int d_delete(d_node *node, char *word);
char *d_find(d_node *node, char *word);
void d_print(d_node *node);
void d_destroy(d_node *node);
