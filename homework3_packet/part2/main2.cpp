// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// 2.2 Global worklist workstealing schedule
// global implicit worklist
  // Pros, simple to implement

#include <thread>
#include <atomic>
#include <assert.h>
#include <iostream>
#include "util.h"
using namespace std;

atomic_int counter(0);

// Global Worklist: threads take tasks (iterations) dynamically
void parallel_mult(float *result_parallel, int *mult, int size)
{
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from incrementing the counter

  int local_counter = atomic_fetch_add(&counter, 1);

  for (; local_counter < size; local_counter = atomic_fetch_add(&counter, 1) )
  {
    float base = result_parallel[local_counter];

    // dynamic assign work based on counter
    for (int j = 0; j < mult[local_counter] - 1; j++)
    {
      result_parallel[local_counter] = result_parallel[local_counter] + base;
    }
  }

}



// void check_mult(float* check_work, int* mult, int size)
// {
//   for (int i = 0; i < size; i++)
//   {
//     float base = check_work[i];

//     for (int j = 0; j < mult[i]-1; j++)
//     {
//       check_work[i] = check_work[i] + base;
//     }
//   }

// }



int main()
{
  float* result_parallel = new float[SIZE];
  // float* check_work      = new float[SIZE];
  int*   mult            = new int[SIZE];

  for (int i = 0; i < SIZE; i++)
  {
    result_parallel[i] = i;
    // check_work[i]      = i;
  }

  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads and then join them
  thread thread_array[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++)
  {
    thread_array[i] = thread(parallel_mult, result_parallel, mult, SIZE);
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    thread_array[i].join();
  }


  // ///// for checking work 
  // check_mult(check_work, mult, SIZE);

  // for (int i = 0; i < SIZE; i++)
  // {
  //   if (result_parallel[i] != check_work[i])
  //   {
  //     printf("result_parallel[%d] != check_work[%d]: %f, %f\n", i, i, result_parallel[i], check_work[i]);
  //     assert(result_parallel[i] == check_work[i]);
  //   }
  // }
  // /////  

  delete[] result_parallel;
  // delete[] check_work;
  delete[] mult;
  return 0;
}
