typedef struct TN_wrapper{
   Tree_node *tn;
   float lower; 
   float upper; 
} TN_wrapper;


TN_wrapper * tnw_new(Tree_node * tn, float lower, float upper);
char* tnw_tostr(void * data);
