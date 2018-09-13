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
  pthread_mutex_t* lock;
} thread_data_t;



int temp;
//pthread_mutex_t lock;       // Global lock mutex so only 1 thread can modify total above.

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;

  int thread_num = input->thread_id;
  int v = input->value;
  pthread_mutex_t* lock = input->lock;
  // To increase the likelyhood of an incorrect calculation of a shared variable, we do it a lot!
  int i;
  int temp2 = 0;
  for(i = 0; i < 5000; i++){
    temp2++;
  }
    pthread_mutex_lock(lock);    // Make sure only 1 thread is updating the shared variable total.
    temp += temp2;
    pthread_mutex_unlock(lock);
  

  
  printf("Thread #: %i value: %i %i\n", thread_num, v, temp);
  //cout << "Thread #: " << thread_num << " value: " << v << " temp " << temp << endl;

}


const int NUM_THREADS = 30;
int main(){

  pthread_mutex_t lock;       // Global lock mutex so only 1 thread can modify total above.  
  
  temp = 0;

  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_mutex_init(&lock, NULL);

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int i;
  for(i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    passed[i].value = 55;
    passed[i].lock = &lock;
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

  pthread_mutex_destroy(&lock);
  
  return 0;

}
