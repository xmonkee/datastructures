#include "list.h"       /* assume list implementation */

#define BUCKETS 100
#define FILENAME "chtbl.log"


typedef struct CHTbl_ {
   int                        buckets; /* M in class terminology */
   int                        (*h)(const void *key); /* this is just g, f is built in */
   int                        (*match)(const void *key1, const void *key2);
   int                        (*destroy)(void *data);
   int                        size; /* n in class terminology */
   List                       *table; /* array of List type -- one per bucket */
} CHTbl;


/*interface functions */

typedef struct {
   char * word;
   char * def;
} Dpair;

typedef CHTbl t_node;

t_node *t_init(void);
int t_insert(t_node *table, char *word, char *def);
int t_delete(t_node *table, char *word);
char * t_find(t_node *table, char *word);
void t_destroy(t_node *table);
void t_print_range(t_node *table, char * word1, char *word2);

/* hashtable functions */

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int        
      (*match)(const void *key1, const void *key2), int (*destroy)(void *data));
void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)
