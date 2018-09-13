#include "stdio.h"
#define SIZE 200

unsigned int rand(int* seed){
  unsigned int hi, lo;
  lo = 16807 * ((*seed) & 0xFFFF);
  hi = 16807 * ((*seed) >> 16);

  lo += (hi & 0x7FFF) << 16;
  lo += (hi >> 15);

  if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;

  return ((*seed) = (unsigned int) lo);
}

int main(){
  unsigned arr[SIZE];
  int i;
  unsigned seed = 1; // You can use any seed value EXCEPT 0
  for(i = 0; i < SIZE; i++){
    arr[i] = rand(&seed) % 100;
  }
  for(i = 0; i < SIZE; i++){
    printf("%u ", arr[i]);
  }

  return 0;
}
