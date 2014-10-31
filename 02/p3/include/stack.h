typedef struct Stack{
   void *data;
   struct Stack *rest;
} Stack;

Stack * empty_stack(void);
int stack_is_empty(Stack *s);
Stack * stack_push(Stack *old, void *data);
void * stack_pop(Stack **s);
void stack_print(Stack *s, char*(*tostr)(void *data));
