#include<stdio.h>
#include<stdlib.h>
  
void heapify(int *f, int n)
{
  int i, j, tmp;
  for(i=0; i<n; i++){
    j = i;
    while(j>0 && f[j/2] < f[j]){
      tmp = f[j/2];
      f[j/2] = f[j];
      f[j] = tmp;
      j = j/2;
    }
  }
}

int * allocate_array( int argc, char * argv[])
{
  int * result;
  int i;
  result = malloc(sizeof(int)*(argc-1));
  for (i=1; i<argc; *(result+i-1) = atoi(argv[i++]))
    ;
  return  result;
}

int test_heap( int * f, int n)
{
  int i;
  int child_A, child_B;

  for( i = 0; i < n; i++ )
  {
    child_A = ( 2 * i ) + 1;
    child_B = ( 2 * i ) + 2;

    if( child_A < n )
      if( f[i] < f[child_A] )
        return -1;
    
    if( child_B < n )
      if( f[i] < f[child_B] )
        return -1;
  }

  return 1;
}

int main(int argc, char * argv[])
{
  int result;
  int i;
  int n = argc - 1;
  int * arr = allocate_array( argc, argv );

  heapify( arr, n );
  result = test_heap( arr, n );

  for( i = 0; i < n; i++ )
    printf("%d ", arr[i]);
  printf("\n");

  if( result == 1 )
    printf("Heap test success!\n");
  else
    printf("Heap test failed.\n");

  free(arr);

  return 0;
}
