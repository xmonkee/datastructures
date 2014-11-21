typedef struct ListElmt_{
   void                *data;
   struct ListElmt_    *next;
} ListElmt;

typedef struct List_{
   int              size;                   /* number of elements in list at any time */
   int              (*destroy)(void *data); /* function to free list element */
   char*            (*tostr)(void *data);   /* function to print list element */
   int              (*match)(void *key1, void *key2); /* function to comp two list elements */
   ListElmt         *head;                            
   ListElmt         *tail;                 
} List;


void  list_init(List *list, 
      int (*destroy)(void *data), 
      int (*match)(void *key1, void *key2),
      char* (*tostr)(void *data));
void  list_destroy(List *list);
int   list_ins_next(List *list, ListElmt *element, const void *data);
int   list_rem_next(List *list, ListElmt *element, const void **data);
void  list_print(List *list);
int   list_add(List *list, int index, void *data);
void  list_append(List *list, void *data);
void* list_element_at(List *list, int index);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list,element) ((element) == (list)->head)
#define list_is_tail(list,element) ((element) == (list)->tail)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)
