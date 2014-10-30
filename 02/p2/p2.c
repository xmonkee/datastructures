#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "p2.h"

d_node *d_init(void){
   d_node *d = malloc(sizeof(d_node));
   d->word = "";
   d->left = NULL;
   d->right = NULL;
   return d;
}

int d_insert(d_node *root, char *word, char *def){
   d_node * node;
   char * tmp_def;
   if(root->left == NULL){ //empty tree
      root->word = strdup(word);
      root->left = (d_node *)strdup(def);
      return 1;
   }
   node = root;
   while(node->right != NULL)
      node = strcmp(word, node->word) < 0 ? node->left : node->right;
   if (strcmp(word, node->word) == 0) return 0;
   tmp_def = (char*)(node->left);
   node->left = d_init();
   node->right = d_init();
   if (strcmp(word, node->word) < 0) {
      node->right->word = strdup(node->word);
      node->right->left = (d_node*)tmp_def;
      node->left->word = strdup(word);
      node->left->left = (d_node*)strdup(def);
   } else {
      node->right->word = strdup(word);
      node->right->left = (d_node*)strdup(def);
      node->left->word = strdup(node->word);
      node->left->left = (d_node*)tmp_def;
      node->word = strdup(word);
   }
      
   return 1;
}

int d_delete(d_node *root, char *word){
   d_node *parent, *current, *tmp;
   
   if(root->left == NULL) return 0;
   if(root->right == NULL){
      if(strcmp(root->word, word)==0){
         free(root->left);
         root->left = NULL;
         return 1;
      } else{ return 0; }
   }
   
   current = root;
   while(current->right != NULL){
      parent = current;
      if(strcmp(word, current->word) < 0)
         current = current->left;
      else
         current = current->right;
   }
   if(strcmp(word, current->word)==0){ 
      //delete the current node
      free((char*) current->left);
      free((char*) current->word);
      free(current);
      if(parent->left == current) //current is left child, promote right child to parent
         tmp = parent->right;
      else  //current child is right child, promote left child to parent
         tmp = parent->left;
      parent->word = tmp->word;
      parent->left = tmp->left;
      parent->right = tmp->right;
      free(tmp);
      return 1;
   }
   return 0;
}

char *d_find(d_node *root, char *word){

   if(root->left == NULL) return NULL;

   while(root->right != NULL){
      if(strcmp(word, root->word) < 0) 
         root = root->left;
      else 
         root = root->right;
   }
   if(strcmp(root->word, word)==0)
      return (char*)root->left;
   else return NULL; 
}


void d_print(d_node *root){
   if(root->left == NULL) return;
   if(root->right == NULL){
      printf("%s: %s\n", root->word, (char *)root->left);
      return;
   }
   d_print(root->left);
   d_print(root->right);
   return;
}

void d_destroy(d_node * root){
   if(root->left == NULL){
      free(root);
      return;
   }
   if(root->right == NULL){
      free((char*)root->left);
      free(root->word);
      free(root);
      return;
   }
   d_destroy(root->left);
   d_destroy(root->right);
   free(root->word);
   free(root);
   return;
}
