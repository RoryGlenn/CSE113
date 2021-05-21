#include <thread>
#include <assert.h>
#include <iostream>
#include "util.h"
using namespace std;


void parallel_mult(float* result_parallel, int* mult, int size, int tid, int num_threads)
{
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)
  
  int chunk_size = size/num_threads;

  for (int i = tid*chunk_size; i < (tid+1)*chunk_size; i++)
  {
    float base = result_parallel[i];

    for (int j = 0; j < mult[i]-1; j++)
    {
      result_parallel[i] = result_parallel[i] + base;
    }
  }

}



int main()
{
  float* result_parallel = new float[SIZE];
  int*   mult            = new int[SIZE];

  for (int i = 0; i < SIZE; i++) { result_parallel[i] = i; }

  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads and then join them
  thread thread_array[NUM_THREADS];
  
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_mult, result_parallel, mult, SIZE, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }

  delete[] result_parallel;
  delete[] mult;

  return 0;

}
