#include <thread>
#include <atomic>
#include "util.h"
#include "IOQueue.h"

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

void parallel_enq(int size, int tid, int num_threads)
{
  // Use this function to enqueue indexes to each of the local workstealing queues
  int chunk_size = size / NUM_THREADS;
  int start      = chunk_size * tid;
  int end        = start + chunk_size;

  for (int x = start; x < end; x++)
  {
    // just like the static schedule, except we are enqueuing
    Q[tid].enq(x);
  }

}

void parallel_mult(float *result, int *mult, int size, int tid, int num_threads)
{
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed

  int task = 0;

  // loop until the queue is empty
  for (x = Q[tid].deq(); x != -1; x = Q[tid].deq()) // change x to task???
  {
    // dynamic work based on task
  }

  // track how many threads are finished
  atomic_fetch_add(&finished_threads, 1);


  // look for any thread that needs help finishing their task
  while (finished_threads.load() != num_threads)
  {
    int target = // pick a thread to steal from
    task = Q[target].deq();

    // check if task is valid
    if (task != -1)
    {
      // perform task


    }
    
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

  thread thread_array[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++)
  {
    thread_array[i] = thread(parallel_mult, result_parallel, mult, SIZE);
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    thread_array[i].join();
  }

  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing
}
