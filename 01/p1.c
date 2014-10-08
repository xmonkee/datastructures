#include<stdio.h>
#include<stdlib.h>
#define NBITS 8

int convert(int input); 
/* endianness switching function */
int genbitat(int pos); 
/* return an int with a single 1 bit at pos(from right); pos<32 */
int getbitat(int num, int pos); 
/* get the bit on position pos(from right) of num */

int main(int argc, char* argv[]){
  int input;
  
  if (argc < 2) {
    printf("Too few arguments");
    return EXIT_FAILURE;
  }

  input = atoi(argv[1]);
  printf("%d\n", convert(input));

  return EXIT_SUCCESS;
}


int convert(int input){
  int bytec, byteL, byteR, bit, output=0;
  bytec = sizeof(input) - 1;
  for(byteR=0; byteR<bytec; byteR++){
    byteL = bytec - byteR;
    for(bit=0; bit<NBITS; bit++){
      if(getbitat(input, byteR*NBITS + bit))
        output |= genbitat(byteL*NBITS + bit);
    }
  }
  return output;
}

int genbitat(int pos){
  int bit = 1;
  return bit<<pos;
}

int getbitat(int num, int pos){
  return (num & genbitat(pos))>>pos;
}
