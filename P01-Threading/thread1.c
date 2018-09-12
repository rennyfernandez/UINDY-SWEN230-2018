/*                                                                                                                     
  Name: Paul Talaga
  Date: Sept 12, 2018
  Desc: Program to demonstrate the use of pthreads
        This reads and writes to a shared variable (without any semaphore or lock)
	to show how, using threads, an incorrect result could be observed.  You
	may need to run this multiple times to see an incorrect temp value.
  To compile this, do: g++ -lpthread thread1.cpp
*/

#include <stdio.h>
//#include <iostream>
#include <pthread.h>
//#include <string>



typedef struct thread_data_t{
  int thread_id;
  int value;
} thread_data_t;

int temp;

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;

  int thread_num = input->thread_id;
  int v = input->value;
  // To increase the likelyhood of an incorrect calculation of a shared variable, we do it a lot!
  int i;
  for(i = 0; i < 5000; i++){
    temp++;
  }
  printf("Thread #: %i value: %i %i\n", thread_num, v, temp);
  //cout << "Thread #: " << thread_num << " value: " << v << " temp " << temp << endl;

}


const int NUM_THREADS = 30;
int main(){

  temp = 0;

  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int i;
  for(i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    passed[i].value = 55;
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }


  for(i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    //cout << "Thread " << i << " done." << endl;
    printf("Thread %i done\n", i);
  }

  //cout << "temp (should be 30000): " << temp << endl;
  printf("temp should be %i: %i\n", NUM_THREADS * 5000, temp);
  pthread_attr_destroy(&attr);

  return 0;

}
