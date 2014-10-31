#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Stack* empty_stack(void){
   Stack *s = malloc(sizeof(Stack));
   s->data = NULL;
   return s;
}

int stack_is_empty(Stack *s){
   return s->data == NULL;
}

Stack* stack_push(Stack *old, void *data){
   Stack *new = malloc(sizeof(Stack));
   new->data = data;
   new->rest = old;
   return new;
}

void * stack_pop(Stack **s){
   void *data = (*s)->data;
   Stack *tofree = *s; 
   *s = (*s)->rest;
   free(tofree);
   return data;
}


void stack_print(Stack *s, char * (*tostr)(void *data)){
   while(!stack_is_empty(s)){;
      printf("%s\n", tostr(s->data));
      s = s->rest;
   }
}
