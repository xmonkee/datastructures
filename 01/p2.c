/* Sources: http://en.wikipedia.org/wiki/Floating_point */

#include<stdio.h>
#include<stdlib.h>
#define SBITS 0 /* Beginning of Sign bits */
#define EBITS 1 /* Beginning of Exponent bits */
#define MBITS 9 /* Beginning of Mantissa bits */

unsigned int genbitat(unsigned int pos); 
unsigned int getbitat(unsigned int num, unsigned int pos); 
unsigned int ftoi(float f); /* to cast float to int while preserving bits */
void printbits(unsigned int num, unsigned int start, unsigned int end);


int main(int argc, char* argv[]){
  float f;
  unsigned int i;
  
  if (argc < 2) {
    printf("Too few arguments");
    return EXIT_FAILURE;
  }

  f = atof(argv[1]);
  i = ftoi(f);
  printbits(i, SBITS, EBITS-1);
  printf(" ");
  printbits(i, EBITS, MBITS-1);
  printf(" ");
  printbits(i, MBITS, sizeof(f)*8-1);
  printf("\n");


  return EXIT_SUCCESS;
}

unsigned int ftoi(float f){
/* The compiler does not allow bit shifting on floats,
 * and casting float as int changes the structure, 
 * this is the key function. It uses pointers to make the 
 * compiler think that the value stored at the address is an int */

  void *vp = &f;
  unsigned int *ip = vp;
  return *ip;
}

void printbits(unsigned int n, unsigned int start, unsigned int end){
  unsigned int i;
  for(i=start; i<=end; i++)
    printf("%d", getbitat(n, i));
}

unsigned int genbitat(unsigned int pos){
  return 1<<(sizeof(unsigned int)*8-1-pos);
}

unsigned int getbitat(unsigned int num, unsigned int pos){
  return (num & genbitat(pos))>>(sizeof(unsigned int)*8 - 1 - pos);
}
