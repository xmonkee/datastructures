#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2.h"

#define ADD "add"
#define DELETE "delete"
#define FIND "find"
#define PRINT "print"
#define EXIT "exit"

int main(){
   char *tofree, *input, *instr, *word, *def;
   d_node *root = d_init();

   tofree = input = malloc(sizeof(char)*(MAXLEN));

   char *menu = "Welcome to dictionary. Valid commands:\n" 
                "1) add <word> \"<definition>\"\n"
                "2) delete <word>\n"
                "3) find <word>\n"
                "4) print\n"
                "5) exit [or ^d]\n";
   printf("%s", menu);

   while(fgets(input, MAXLEN, stdin)!=NULL){
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
         if(d_insert(root, word, def)) 
            printf("Adding \"%s\" to dictionary\n", word); 
         else 
            printf("Couldn't add\n");
      }

      //Delete Case
      else if(strcmp(DELETE, instr) == 0){
         word = strsep(&input, " \n");
         if(d_delete(root, word)) 
            printf("Deleting \"%s\" from dictionary\n", word); 
         else 
            printf("Couldn't delete\n");
      }

      //Find Case
      else if(strcmp(FIND, instr) == 0){
         word = strsep(&input, " \n");
         if((def = d_find(root, word))==NULL) printf("Couldn't find\n");
         else printf("%s: %s\n",word, def);
      }

      //Print Case
      else if(strcmp(PRINT, instr) == 0){
         d_print(root);
      }

      else if(strcmp(EXIT, instr) == 0)
         break;

      else printf("Invalid Command, try again\n%s", menu);

      input = tofree;
   }
   free(tofree);
   d_destroy(root);
   printf("Bye \n");
}

