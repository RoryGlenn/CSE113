#include <thread>
#include <atomic>
#include <exception>
#include "util.h"
#include "IOQueue.h"

// #define SIZE (1024 * 1024) = 1,048,576
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);


void parallel_enq(int size, int tid, int num_threads)
{
  // Use this function to enqueue indexes to each of the local workstealing queues
  int chunk_size = size / num_threads; // 1,048,576 / 8
  int start      = chunk_size * tid;   // 131,072 * n (where 0 <= n <= 8)
  int end        = start + chunk_size; // 131072*n + 131,072

  for (int x = start; x < end; x++)
  {
    // just like the static schedule, except we are enqueuing
    Q[tid].enq(x);
  }

}

void parallel_mult(float *result_parallel, int *mult, int size, int tid, int num_threads)
{
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed

  // int task = 0;
  for ( int index = Q[tid].deq(); index != -1; index = Q[tid].deq() )
  {
    // dynamic work based on task
    float base = result_parallel[index];

    for (int j = 0; j < mult[index]-1; j++)
    {
      result_parallel[index] = result_parallel[index] + base; 
    }

  }

  // track how many threads are finished
  atomic_fetch_add(&finished_threads, 1);

  // look for any thread that needs help finishing their task
  while ( finished_threads.load() != num_threads )
  {
    int target = (tid + 1) % NUM_THREADS; // pick a thread to steal from
    int index  = Q[target].deq();

    // check if task is valid
    if (index != -1)
    {
      float base = result_parallel[index];

      // dynamic work based on task
      for (int j = 0; j < mult[j]-1; j++)
      {
        result_parallel[index] = result_parallel[index] + base; 
      }   
    }
    else
    {
      target = (tid + 1) % NUM_THREADS; // pick a another thread to steal from
    }
  }

}


void init_queue_array(int list_size)
{
  for (int i = 0; i < NUM_THREADS; i++)
  {
    Q[i].init(list_size);
  }
}


int main()
{
  float* result_parallel = new float[SIZE];
  float* check_work      = new float[SIZE];
  int*   mult            = new int[SIZE];


  for (int i = 0; i < SIZE; i++)
  {
    result_parallel[i] = i;
    check_work[i] = i;
  }
  
  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads to initialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.

  init_queue_array(SIZE);

  thread thread_array[NUM_THREADS];


  // enq threads
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_enq, SIZE, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }


  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_mult, result_parallel, mult, SIZE, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }  


  delete[] mult;
  delete[] check_work;
  delete[] result_parallel;

  return 0;
}
