/* Source: Intro to File I/O https://www.cs.bu.edu/teaching/c/file-io/intro/ */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CHAR_PER_LINE 1000
#define MAX_LINES 1000
typedef char* string;

int readfile(char lines[MAX_LINES][MAX_CHAR_PER_LINE], string fname){
  FILE *fp = fopen(fname, "r");
  int n = 0; /* number of lines read */
  char *l;
  while(!feof(fp)) {
    l = fgets(lines[n], MAX_CHAR_PER_LINE, fp); /* read a single line */
    if(l!=NULL) n++;
  }
  fclose(fp);
  return n;
}

int main(int argc, char *argv[]){
  char text[MAX_LINES][MAX_CHAR_PER_LINE];
  int i, n = readfile(text, argv[1]);
  for(i=0; i<n; printf("%s", text[i++]));
  return EXIT_SUCCESS;
}
