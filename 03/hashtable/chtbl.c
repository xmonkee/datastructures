#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "chtbl.h"



/* functions to interface between interactive and the chtbl */

Dpair * dpair_new(char *word, char *def){
   Dpair * dp = malloc(sizeof(Dpair));
   dp->word = strdup(word);
   dp->def = strdup(def);
   return dp;
}

void dpair_destroy(Dpair * dp){
   free(dp->word);
   free(dp->def);
   free(dp);
   return;
}

/*prehashing functions defined below*/

int h1(const void *key_){
   /*Simple function that adds ascii value of each character*/
   Dpair * key = (Dpair *)key_;
   char * word = key->word;
   int i;
   int prehash = 0;
   for(i=0; i<strlen(word); i++){
      prehash += word[i];
   }
   return prehash;
}

int match(const void *key1, const void *key2){
   if(strcmp(((Dpair*)key1)->word, ((Dpair*)key2)->word) == 0)
      return 1;
   else
      return 0;
}

int destroy(void * data){
   dpair_destroy((Dpair *)data);
   return 0;
}

char * tostr(void *data){
   return ((Dpair*)data)->word;
}

t_node *t_init(void){
   t_node * table = malloc(sizeof(t_node));
   chtbl_init(table, BUCKETS, h1, match, destroy);
   FILE *log = fopen(LOGFILE, "w");
   fprintf(log, "Logging\n");
   fclose(log);
   return table;
}



int t_insert(t_node *table, char *word, char *def){
   int error_code;
   Dpair * dp = dpair_new(word, def);
   error_code = chtbl_insert(table, (void *)dp);
   if(error_code==0){
      FILE *log = fopen(LOGFILE, "a");
      fprintf(log, "Insert %s. Load Factor %f. Occupancy %d\n", word, (float)(table->size)/table->buckets, table->size);
      fclose(log);
   }
   return error_code;
}


int t_delete(t_node *table, char *word){
   int error_code;
   Dpair *to_free, *to_pass;
   to_free = to_pass = dpair_new(word, "");
   if((error_code = chtbl_remove(table, (void **)&to_pass))==0){
      dpair_destroy(to_pass);
      FILE *log = fopen(LOGFILE, "a");
      fprintf(log, "Insert %s. Load Factor %f. Occupancy %d\n", word, (float)(table->size)/table->buckets, table->size);
      fclose(log);
   }
   dpair_destroy(to_free);
   return error_code;
}

char * t_find(t_node *table, char *word){
   int error_code;
   char *def = NULL;
   Dpair *dp = dpair_new(word, "");
   Dpair *to_free = dp;
   error_code = chtbl_lookup(table, (void **)&dp);
   if(error_code==0)
      def = dp->def;
   dpair_destroy(to_free);
   return def;
}

int cmpfun(const void *a, const void *b){
   return strcmp((*(Dpair**)a)->word, (*(Dpair**)b)->word);
}

void t_print(t_node *table){
   ListElmt *element;
   int i = 0;
   int j = 0;
   Dpair ** biglist = malloc(sizeof(Dpair*)*table->size);
   while(i< table->size){
      for (element = list_head(&table->table[j]); 
            element != NULL; 
            element = list_next(element)){
         biglist[i] = list_data(element);
         i++;
      }
      j++;
   }
   qsort(biglist, table->size, sizeof(Dpair*), cmpfun);
   for(i=0; i<table->size; i++){
      printf("%s: %s\n", biglist[i]->word, biglist[i]->def);
   }
   free(biglist);
   return;
}

void t_print_range(t_node *table, char * word1, char * word2){
   ListElmt *element;
   int i = 0;
   int j = 0;
   int isprint = 0;
   Dpair ** biglist = malloc(sizeof(Dpair*)*table->size);
   while(i< table->size){
      for (element = list_head(&table->table[j]); 
            element != NULL; 
            element = list_next(element)){
         biglist[i] = list_data(element);
         i++;
      }
      j++;
   }
   qsort(biglist, table->size, sizeof(Dpair*), cmpfun);
   for(i=0; i<table->size; i++){
      if(strcmp(biglist[i]->word, word1) >= 0 && 
            strcmp(biglist[i]->word, word2) <= 0) 
         printf("%s: %s\n", biglist[i]->word, biglist[i]->def);
   }
   free(biglist);
   return;
   
}

void t_destroy(t_node * table){
}


int chtbl_init(CHTbl *htbl, 
      int buckets, 
      int (*h)(const void *key), 
      int (*match)(const void *key1, const void *key2), 
      int (*destroy)(void *data)){
   int i;
   if ((htbl->table = 
            (List *) malloc(buckets*sizeof(List))) == NULL)
      return -1;

   htbl->buckets = buckets;

   for (i = 0; i < htbl->buckets; i++)
      list_init(&htbl->table[i], destroy, NULL, tostr);

   htbl->h = h;
   htbl->destroy = destroy;
   htbl->match = match;
   htbl->size = 0;
   return 0;
}

/* insert an object into the hashtable */
int chtbl_insert(CHTbl *htbl, const void *data){
   int error_code;
   int bucket;

   if (chtbl_lookup(htbl,(void **) &data) == 0){ /*data already in table */
      return 1;
   }

   /* data not in table, find bucket to place it in */
   /* note that f, in particular the division method, is hardwired
      into the line below as the mod operation
      */
   bucket = htbl->h(data) % htbl->buckets; 

   if ((error_code = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
      htbl->size++; 

   return error_code;
}

int chtbl_lookup(const CHTbl *htbl, void **data){
   ListElmt *element;
   int bucket;
   bucket = htbl->h(*data)%htbl->buckets; /* apply user's g and hardwired f */
   for (element = list_head(&htbl->table[bucket]); 
         element != NULL; 
         element = list_next(element)) {
      if (htbl->match(*data, list_data(element))) {
         *data = list_data(element); /* set pointer to point to object found in table */
         return 0;
      }
   }
   return -1;
}

int chtbl_remove(CHTbl *htbl, void **data){
   ListElmt *element, *prev_element;
   List * bucket_list;
   int bucket;

   if(chtbl_lookup(htbl, data) == -1){ /*data not found*/
      return -1; 
   }

   bucket = htbl->h(*data)%htbl->buckets;
   bucket_list = &htbl->table[bucket];

   if(htbl->match(*data, list_data(list_head(bucket_list)))){
   /* check if first element matches */
      list_rem_next(bucket_list, NULL, (const void **)data);
   /* remove it if it is */
   } else {
      /*there must be at least 2 elements since there is a data match
       * and it's not with the list head */
      prev_element = list_head(bucket_list);
      for (element = list_next(list_head(bucket_list));
            element != NULL; element = list_next(element)){
         if (htbl->match(*data, list_data(element))) {
            list_rem_next(bucket_list, prev_element, (const void **)data);
            return 0;
         }
         prev_element = element;
      }
   }
   htbl->size--;
   return 0;
}

