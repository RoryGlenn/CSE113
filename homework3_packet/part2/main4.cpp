#include <atomic>
#include <thread>
#include "util.h"
#include "IOQueue.h"

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

void parallel_enq(int size, int tid, int num_threads)
{
  // Use this function to enqueue indexes to each of the local
  // workstealing queues

  // Hint: this should be the same as in main3.cpp
}

void parallel_mult(float *result, int *mult, int size, int tid, int num_threads)
{
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed

  // Unlike in main3.cpp, you should deq 32 elements
  // at a time.
}

int main()
{
  float *result_parallel = new float[SIZE];
  int   *mult            = new int[SIZE];
  
  for (int i = 0; i < SIZE; i++)
  {
    result_parallel[i] = i;
  }
  
  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads to initialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.

  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing

  // hint: this part should be the same as in main3.cpp

  thread thread_array[NUM_THREADS];

  // enq threads
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_enq, SIZE/NUM_THREADS, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }


  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_mult, result_parallel, mult, SIZE/NUM_THREADS, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }  

  delete[] mult;
  delete[] check_work;
  delete[] result_parallel;

  return 0;  
}
