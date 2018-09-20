#include "stdio.h"
#include "sys/time.h"



double getTimeAsDoubleSeconds(){
  struct timeval now;
  gettimeofday(&now, NULL);
  return (double)now.tv_sec + (double)now.tv_usec / 1000000.0;
}

void think(){
    int i = 0;
    while(i != -1)i++;
}

int main(){
    double start = getTimeAsDoubleSeconds();
    think();
    double end = getTimeAsDoubleSeconds();
    
    printf("Thinking took %f seconds\n", end - start);
}