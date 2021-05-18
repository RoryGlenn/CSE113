#include <thread>
#include <atomic>
#include "util.h"

std::atomic_int counter(0);
void parallel_mult(float *result, int *mult, int size, int tid, int num_threads)
{
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from incrementing the counter
  for (int i = 0; i < size; i++)
  {
    float base = result[i];
    for (int w = 0; w < mult[i] - 1; w++)
    {
      result[i] = result[i] * base;
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
