#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "tree.h"

/** Red black self balancing tree */

void tree_balance_insert(Tree *tree, Tree_node *node);
void tree_balance_delete(Tree *tree, Tree_node *node);
void tree_left_rotate(Tree *tree, Tree_node *node);
void tree_right_rotate(Tree *tree, Tree_node *node);

Tree_node *tree_new_node(Tree * tree, void *key, void *value, void(*print)(void*key, void*value)){
   Tree_node *node;
   if((node = malloc(sizeof(Tree_node)))==NULL)
      return NULL;
   node->left = node->right = tree->nil;
   node->parent = NULL;
   node->key = strdup(key);
   node->value = strdup(value);
   node->color = RED;
   node->print = print;
   return node;
}

void tree_node_print(Tree * tree, Tree_node * node, int depth){
   /*prints the tree in preorder with indentation. Affixes words with 
    * 0 for red and 1 for black */
   int i;
   char* dir = ">";
   if(node==tree->nil) return;
   for(i=0; i<depth-1; i++) printf("- ");
   if(node == node->parent->left)
      printf("<");
   if(node == node->parent->right)
      printf(">");
   printf("%d", node->color);
   printf("%s\n", (char*)node->key);
   tree_node_print(tree, node->left, depth+1);
   tree_node_print(tree, node->right, depth+1);
}
void tree_node_print_inorder(Tree *tree, Tree_node * node){
   if(node==tree->nil) return;
   tree_node_print_inorder(tree, node->left);
   node->print(node->key, node->value);
   tree_node_print_inorder(tree, node->right);
}
void tree_node_print_range(Tree *tree, Tree_node *node, void*key1, void*key2){
   if(node==tree->nil) return;
   if(tree->compare(key1, node->key) <= 0){
      tree_node_print_range(tree, node->left, key1, key2);
   }
   if(tree->compare(key1, node->key)<=0 &&
         tree->compare(key2, node->key)>=0){
      node->print(node->key, node->value);
   }
   if(tree->compare(key2, node->key) >= 0){
      tree_node_print_range(tree, node->right, key1, key2);
   }
}

void tree_print_tree(Tree *tree){
   tree_node_print(tree, tree->root, 0);
}
void tree_print_range(Tree *tree, void *key1, void *key2){
   tree_node_print_range(tree, tree->root, key1, key2);
}
void tree_print_inorder(Tree *tree){
   tree_node_print_inorder(tree, tree->root);
}

int tree_init(Tree *tree, int(*compare)(void *key1, void *key2), 
      void(*print)(void *key, void *value)){
   Tree_node * nil = malloc(sizeof(Tree_node));
   tree->compare = compare;
   tree->print = print;
   nil->left = nil->right = nil->parent = NULL;
   nil->color = BLACK;
   nil->key = nil->value = NULL;
   nil->print = NULL;
   tree->nil = nil;
   tree->root = tree->nil;
   return 0;
}

int tree_insert(Tree *tree, void *key, void *value){
   Tree_node *new_node, *node, *parent;
   int left;
   if((new_node = tree_new_node(tree, key, value, tree->print))==NULL)
      return -1;
   if(tree->root == tree->nil){ //tree is emtpy
         new_node->color = BLACK;
         new_node->parent = tree->nil;
         tree->root = new_node;
         return 0;
      } else { //tree is not empty
         node = tree->root;
         while(node != tree->nil){ //we search the tree
            if(tree->compare(key, node->key) == 0){ //key already present 
               return 1;
            }
            parent = node;
            if(tree->compare(key, parent->key) < 0){
               node = parent->left;
               left = 1;
            } else {
               node = parent->right;
               left = 0;
            }
         } // we find the insertable location
         if(left){
            parent->left = new_node;
            new_node->parent = parent;
         } else {
            parent->right = new_node;
            new_node->parent = parent;
         }

         //Now for balancing
         tree_balance_insert(tree, new_node);
         return 0;
   }
}

void tree_transplant(Tree *tree, Tree_node *u, Tree_node *v){
   /* Reference: Introduction to algorithams - Corment */

   if(u->parent == tree->nil){
      tree->root = v;
   } else if(u == u->parent->left){
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

int tree_remove(Tree *tree, void *key, void **value){
   /* Reference: Introduction to algorithams - Corment */

   Tree_node *node  = tree->root;
   Tree_node *y, *x;
   int left;

   if(tree_lookup(tree, key, value)!=0)
      return 1;

   while(tree->compare(node->key, key)!=0){
     if(tree->compare(key, node->key) < 0){
        node = node->left;
     } else{
        node = node->right;
     }
   }

   *value = node->value; //return deleted value 
   
   y = node;
   Color ycolor = node->color;
   if(node->left == tree->nil){
      x = node->right;
      tree_transplant(tree, node, node->right);
   }else if(node->right == tree->nil) {
      x = node->left;
      tree_transplant(tree, node, node->left);
   }else{ //no child is nil
      y = node->right;
      while(y->left != tree->nil){ //find right minimum
         y = y->left;
      }
      ycolor = y->color;
      x = y->right;
      if(y->parent == node){
         x->parent = y;
      } else {
         tree_transplant(tree, y, y->right);
         y->right = node->right;
         y->right->parent = y;
      }
      tree_transplant(tree,node, y);
      y->left = node->left;
      y->left->parent = y;
      y->color = node->color;
   }
   if(ycolor == BLACK){
      tree_balance_delete(tree, x);
   }
   free(node);
   return 0;
}


int tree_remove_old(Tree *tree, void *key, void **value){
   Tree_node * tmp_node;
   int left;
   if(tree_lookup(tree, key, value)!=0)
      return 1;
   Tree_node *node = tree->root;
   while(tree->compare(node->key, key)!=0){
     if(tree->compare(key, node->key) < 0){
        left = 1;
        node = node->left;
     } else{
        left = 0;
        node = node->right;
     }
   }

   *value = node->value; //return deleted value 
   //Now we delete

   //Outer node
   if(node->left == tree->nil && node->right == tree->nil){
      if(tree->root == node){ //node is root
         tree->root = tree->nil;
      } else {
         if(left) node->parent->left = tree->nil;
         else node->parent->right = tree->nil;
      }
      free(node->key);
      free(node);
   }
   //No left child
   else if(node->left == tree->nil){
      free(node->key);
      tmp_node = node->right;
      node->key = node->right->key;
      node->value = node->right->value;
      node->left = node->right->left;
      node->right = node->right->right;
      free(tmp_node);
   }
   //No right child
   else if(node->right == tree->nil){
      free(node->key);
      tmp_node = node->left;
      node->key = node->left->key;
      node->value = node->left->value;
      node->right = node->left->right;
      node->left = node->left->left;
      free(tmp_node);
   }
   else { //translpant the smallest right descendant
      tmp_node = node->right;
      while(tmp_node->left != tree->nil){
         tmp_node = tmp_node->left;
      }
      free(node->key);
      node->key = tmp_node->key;
      node->value = tmp_node->value;
      if(tmp_node->parent == node){
         node->right = tree->nil;
      } else {
         tmp_node->parent->left = tree->nil;
      }

      free(tmp_node);
   }
   return 0;
   
}

int tree_lookup(Tree *tree, void *key, void **value){
   Tree_node *node = tree->root;
   if(node==tree->nil) return 1;
   while(tree->compare(node->key, key)!=0){
     if(tree->compare(key, node->key) < 0)
        node = node->left;
     else
        node = node->right;
     if(node == tree->nil) return 1;
   }
   *value = node->value;
   return 0;
}
int tree_height(Tree *tree){}
void tree_destroy(Tree *tree){}

void tree_balance_insert(Tree *tree, Tree_node *node){
   Tree_node *parent, *uncle, *gp;
   if(tree->root == node){ //Case 1: red or black root
      node->color = BLACK;
      return;
   }
   if(node->parent->color == BLACK)
      return;
   else{ //red parent
      parent = node->parent;
      gp = node->parent->parent;
      uncle = (node->parent == gp->right)? gp->left : gp->right;
      if(uncle->color == RED){ //Case 3, both parent and uncle red
         node->parent->color = BLACK;
         uncle->color = BLACK;
         gp->color = RED;
         tree_balance_insert(tree, gp);
         return;
      } else { //case 4 and case 5, red parent, black uncle
         if(node==parent->right && parent==gp->right){ //case 5.1, right linear
            parent->color = BLACK;
            gp->color = RED;
            tree_left_rotate(tree, gp);
            return;
         } else if (node==parent->left && parent==gp->left) { //case 5.2 left linear
            parent->color = BLACK;
            gp->color = RED;
            tree_right_rotate(tree, gp);
         } else if(node==parent->left && parent==gp->right){ //case4.1, RL
            tree_right_rotate(tree, parent);
            tree_balance_insert(tree, parent);
            return;
         } else { //case 4.2 LR
            tree_left_rotate(tree, parent);
            tree_balance_insert(tree, parent);
         }
         return;
      } 
   }

}


void tree_balance_delete(Tree * tree, Tree_node * x){
   /* Reference: Introduction to Algrorithms - Cormen */
   Tree_node * w;
   while(x!=tree->root && x->color==BLACK){
      if(x==x->parent->left){
         w = x->parent->right;
         if(w->color == RED){
            w->color = BLACK;
            x->parent->color = RED;
            tree_left_rotate(tree, x->parent);
            w = x->parent->right;
         }
         if(w->left->color == BLACK && w->right->color == BLACK){
            w->color = RED;
            x = x->parent;
         } else {
            if(w->right->color == BLACK) {
               w->left->color = BLACK;
               w->color = RED;
               tree_right_rotate(tree, w);
               w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            tree_left_rotate(tree, x->parent);
            x = tree->root;
         }
      } else {
         w = x->parent->left;
         if(w->color == RED){
            w->color = BLACK;
            x->parent->color = RED;
            tree_right_rotate(tree, x->parent);
            w = x->parent->left;
         }
         if(w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;
            x = x->parent;
         } else {
            if(w->left->color == BLACK) {
               w->right->color = BLACK;
               w->color = RED;
               tree_left_rotate(tree, w);
               w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            tree_right_rotate(tree, x->parent);
            x = tree->root;
         }
      }
   }
   x->color = BLACK;
}
         

void tree_left_rotate(Tree *tree, Tree_node *x){
   Tree_node *y = x->right;
   x->right = y->left;
   if(y->left != tree->nil)
      y->left->parent = x;
   y->parent = x->parent;
   if (x == tree->root)
      tree->root = y;
   else if(x == x->parent->left)
      x->parent->left = y;
   else
      x->parent->right = y;
   y->left = x;
   x->parent = y;
}


void tree_right_rotate(Tree *tree, Tree_node *x){
   Tree_node *y = x->left;
   x->left = y->right;
   if(y->right != tree->nil)
      y->right->parent = x;
   y->parent = x->parent;
   if (x == tree->root)
      tree->root = y;
   else if(x == x->parent->right)
      x->parent->right = y;
   else
      x->parent->left = y;
   y->right = x;
   x->parent = y;
}
