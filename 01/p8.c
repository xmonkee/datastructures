#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 80
typedef char* charptr;

void alphabetize(char *text[], int nlines);
int compar(const void *, const void *);

int main(int argc, char *argv[]){
  int n = 0; /* number of lines read */
  int s = 10; /* initial size of array of line pointers*/
  int i;
  char *l, *line;
  charptr *linestmp;
  charptr *lines = malloc(sizeof(char*)*s); /* array storing pointers to lines */
  while(!feof(stdin)) {
    line = malloc(sizeof(char)*MAXLEN);
    l = fgets(line, MAXLEN, stdin);
    if(l != NULL){
      lines[n++] = line;
      if(n==s){
        linestmp = malloc(sizeof(char*)*(s=s*2));
        for (i=0; i<n; i++) linestmp[i] = lines[i];
        free(lines);
        lines = linestmp;
      }
    }
  }
  
  alphabetize(lines, n);

  for(i=0; i<n; printf("%s", lines[i++]));
  return EXIT_SUCCESS;
}


void alphabetize(charptr lines[], int nlines){
  qsort(lines, nlines, sizeof(char *), *compar);
}

int compar(const void *p1, const void *p2){
  return strcmp(*(charptr *)p1, *(charptr *)p2); 
}
