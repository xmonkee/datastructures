#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 200
#define LINES 500
typedef char* charptr;

void swap(charptr lines[], size_t i, size_t j){
  charptr tmp = lines[i];
  lines[i] = lines[j];
  lines[j] = tmp;
}

size_t partition(charptr lines[], size_t p, size_t r){
  size_t k, i=p-1;
  charptr X;
  X = lines[r];
  for(k=p; k<r; k++)
    if(strcmp(lines[k], X) <= 0) 
      swap(lines, ++i, k);
  swap(lines, ++i, r);
  return i;
}

void mysort(charptr lines[], size_t p, size_t r){
  if(p<r){
    size_t q = partition(lines, p, r);
    mysort(lines, p, q-1);
    mysort(lines, q+1, r);
  }
  return;
}

void alphabetize(charptr lines[], size_t nlines){
  mysort(lines, 0, nlines-1);
}


int main(int argc, char *argv[]){
  size_t n = 0; /* number of lines read */
  int s = LINES; /* initial size of array of line pointers*/
  int i;
  char *l, *line;
  charptr *linestmp;
  charptr *lines = malloc(sizeof(char*)*s); /* array storing pointers to lines */
  while(!feof(stdin) && n<LINES) {
    line = malloc(sizeof(char)*MAXLEN);
    l = fgets(line, MAXLEN, stdin); /* read a single line */
    if(l != NULL){
      lines[n++] = line; /* add it to array */
    }
  }
  
  alphabetize(lines, n);

  for(i=0; i<n; printf("%s", lines[i++]));
  return EXIT_SUCCESS;
}

