#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "dict.h"


#define MAXLEN 1000
#define ADD "add"
#define DELETE "delete"
#define FIND "find"
#define PRINT "print"
#define EXIT "exit"
#define READ "read"
#define TPRINT "tprint" //print in tree format... secret option

int main(){
   FILE *f;
   char *tofree, *input, *instr, *word, *def, *filename, *word2;
   t_node *root = t_init();
   tofree = input = malloc(sizeof(char)*(MAXLEN));

   char *menu = "Welcome to dictionary. Valid commands:\n" 
                "1) add <word> \"<definition>\"\n"
                "2) delete <word>\n"
                "3) find <word>\n"
                "4) print\n"
                "5) exit [or ^d]\n";
   printf("%s", menu);

   while(printf(">>> "), fgets(input, MAXLEN, stdin)!=NULL){
      instr = strsep(&input, " \n");

      //ADD case
      if(strcmp(ADD, instr) == 0){
         word = strsep(&input, " ");
         strsep(&input, "\"");
         def = strsep(&input, "\"");
         if(def == NULL || input == NULL){
            printf("Invalid. The definition should be quotes.\n");
            input = tofree;
            continue;
         }
         if(t_insert(root, word, def)==0) {
            printf("Adding \"%s\" to dictionary\n", word); 
         }
         else 
            printf("Couldn't add \"%s\"\n", word);
      }

      //Delete Case
      else if(strcmp(DELETE, instr) == 0){
         word = strsep(&input, " \n");
         if(t_delete(root, word)==0) {
            printf("Deleting \"%s\" from dictionary\n", word); 
         }
         else 
            printf("Couldn't delete \"%s\"\n", word);
      }

      //Find Case
      else if(strcmp(FIND, instr) == 0){
         word = strsep(&input, " \n");
         word2 = strsep(&input, " \n");
         if(strsep(&input, " \n")!= NULL){ //range find
            t_print_range(root, word, word2);
         } else {
            if((def = t_find(root, word))==NULL) 
               printf("Couldn't find \"%s\"\n", word);
            else 
               printf("%s: %s\n",word, def);
         }
      }

      //Print Case
      else if(strcmp(PRINT, instr) == 0){
         t_print(root);
      }
      //Tree Print Case
      else if(strcmp(TPRINT, instr) == 0){
         t_print_tree(root);
      }

      //Read case
      else if(strcmp(READ, instr) == 0){
         filename = strsep(&input, " \n");
         f = fopen(filename, "r");
         input = tofree;
         while(fgets(input, MAXLEN, f)!=NULL){
            word = strsep(&input, " ");
            strsep(&input, "\"");
            def = strsep(&input, "\"");
            t_insert(root, word, def);
            input = tofree;
         } 
         fclose(f);
      }


      else if(strcmp(EXIT, instr) == 0)
         break;

      else printf("Invalid Command, try again\n%s", menu);

      input = tofree;
   }
   free(tofree);
   t_destroy(root);
   printf("Bye \n");
   return 1;
}

