#include <thread>
#include "util.h"

void parallel_mult(float *result, int *mult, int size, int tid, int num_threads)
{
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)
  for (int i = 0; i < size; i++)
  {
    float base = result[i];
    for (int w = 0; w < mult[i] - 1; w++)
    {
      result[i] = result[i] + base;
    }
  }
}

int main()
{
  float *result_parallel = new float[SIZE];
  int *mult = new int[SIZE];
  for (int i = 0; i < SIZE; i++)
  {
    result_parallel[i] = i;
  }
  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads and then join them
}
