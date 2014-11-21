#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "list.h"

/*
   be careful to include match in interface if we want to subclass Sets, etc. 
   */
void  list_init(List *list, 
      int (*des)(void *data), 
      int (*match)(void *key1, void *key2),
      char* (*tostr)(void *data)){
   list->head    = NULL;    /* NULL head and tail means list is zero sized */
   list->tail    = NULL; 
   list->size    = 0;       /* number of elements currently */
   list->destroy = des;     /* function to de-allocate element */
   list->tostr   = tostr;   /* function to print element */
   list->match   = match;   /* used for subclassing */
}

/* when this function is called list_rem_next is called on each element of the
   list and the list->destroy is called for the data blob returned by the 
   list_rem_next call */
void list_destroy(List *list){
   void *data;
   while (list_size(list) > 0){
      if (list_rem_next(list,NULL,(const void **) &data) == 0)
         list->destroy(data);
   }
}

/* insert new element in List after element provided as ListElmt element. Note that
   the user has to provide element. This is a constant-time operation. Insertion
   at head of list is indicated by NULL */
int list_ins_next(List *list, ListElmt *element, const void *data){
   ListElmt *new_element;
   /* allocate new element that will be linked to element, check for NULL */
   if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL)
      return -1;

   new_element->data = (void *) data;        /* set the new element's data */
   /* now it's time to link */
   if (element == NULL){                     /* this means insert at head of list */
      if (list_size(list) == 0)               /* if tail also then set tail to new_element */
         list->tail = new_element;

      new_element->next = list->head;         /* insert at head of list */
      list->head = new_element;      
   }
   else{                                     /* not inserting at head */
      if (element->next == NULL)              /* element becomes new tail */
         list->tail = new_element;
      new_element->next = element->next;      /* re-link nodes */
      element->next = new_element;
   }
   list->size++;    
   return 0;
}

int list_rem_next(List *list, ListElmt *element, const void **data){
   ListElmt *old_element;

   if (list_size(list) == 0)
      return -1;

   /* handle remove of list head first. this is indicated by NULL */
   if (element == NULL){
      *data = list->head->data;
      old_element = list->head;
      list->head = list->head->next;      /* note if list is size 1 list->head=NULL here */
      if (list_size(list) == 1)
         list->tail = NULL;                /* in that case set tail explicitly to NULL also */
   }
   else{
      if (element->next == NULL)           /* already at tail , not possible to rem next */
         return -1;
      *data = element->next->data;         /* grab data of element to be removed */
      old_element = element->next;         /* important to keep old element so we can free it */
      element->next = element->next->next; /* relink */

      if (element->next == NULL)           /* check if you are now tail */
         list->tail = element; 
   }
   free(old_element);                     /* note that old_element can be freed here, but data
                                             must be freed by client */
   list->size--;
   return 0;
}

/* O(n) methods -------------------------------------------- */
void list_print(List *list){
   ListElmt *node = list_head(list);
   printf("[");
   while (node != NULL){
      printf("%s ", list->tostr(node->data));
      node = node->next;
   }
   printf("]\n");
}


/* add to specified index */
int list_add(List *list, int index, void *data){
   int i = 0;
   ListElmt *node = list->head;

   if (index > list->size || index < 0)
      return -1;

   if (index == 0)
      list_ins_next(list, NULL, data);  
   else if (index == list->size)
      list_ins_next(list, list->tail, data);  
   else{
      while (i < index){
         node = node->next;
         ++i;
      }
      list_ins_next(list, node, data);  
   }
   return 0;
}
/* this is O(1) but is included for convencience */
void list_append(List *list, void *data){
   ListElmt *node = list->tail;
   list_ins_next(list,list->tail,data);
   return;
}

void* list_element_at(List *list, int index){
   ListElmt *node = list_head(list);
   int i;
   for (i=0; i < index && node != list_tail(list); ++i)
      node = node->next;

   return node->data;
}
