/* Source: man page for strsep() */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 10000 /* Assumed maximum length of line */
#define MAXWORDS 1000 /* Assumed maximum words in a file */

typedef struct {
  char* word;
  int count;
} counter;

const char * NONALPHA = " ,./?;:'\"\\\n\t\b[]{}!@#$%^&*()1234567890<>=_-=+";

int repeated(char * word){
  int i, n=0;
  int b_rep=0;
  while(word[n] != '\0' && !b_rep){
    i = n+1;
    while(word[i] != '\0' && !b_rep){
      if(word[n]==word[i]) b_rep = 1;
      i++;
    } 
    n++;
  }
  return b_rep;
}

int add_to_list(counter * dict, char * word, int n){
  int i, l;
  for(i=0; i < n; i++){
     if(strcmp(dict[i].word, word) == 0){ 
       dict[i].count++; /* increase count if word already in list */
       return n; /* no change in number of unique words */
     }
  }
  /* Word is not in list */
  l = strlen(word);
  dict[n].word = malloc(sizeof(char)*l);
  dict[n].count = 1;
  strncpy(dict[n].word, word, l);
  n++;  /* word added to list */
  return n; 
}

void printdict(counter * dict, int n){
  int i;
  for(i=0; i<n; i++)
    printf("%s : %d\n", dict[i].word, dict[i].count);
}

int main(int argc, char *argv[]){
  FILE *fp = fopen(argv[1], "r");
  char *l, *line, *word;
  int n = 0;
  counter * dict = malloc(sizeof(counter)*MAXWORDS);
  while(!feof(fp)){
    line = malloc(sizeof(char)*MAXLEN);
    l = fgets(line, MAXLEN, fp);
    if(l != NULL){
      while ((word = strsep(&line,NONALPHA)) != NULL)
        if(repeated(word)) n = add_to_list(dict, word, n);
    } 
    free(line);
  }
  fclose(fp);
  printdict(dict,n);
  free(dict);
  return EXIT_SUCCESS;
}
