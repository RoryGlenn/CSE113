#include <atomic>
#include <thread>
#include "util.h"
#include "IOQueue.h"

//  docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

// for (int i = 0; i < 32; i++)
// {
//   printf("index_array[%d]: %d\n", i, index_array[i]);
// }
// exit(EXIT_SUCCESS);

void parallel_enq(int size, int tid, int num_threads)
{
  // Use this function to enqueue indexes to each of the local
  // workstealing queues

  // Hint: this should be the same as in main3.cpp
  int chunk_size = size / num_threads;
  int start = chunk_size * tid;       
  int end = start + chunk_size;       

  for (int x = start; x < end; x++) { Q[tid].enq(x); }
}

void parallel_mult(float *result_parallel, int *mult, int tid, int num_threads)
{
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed

  // Unlike in main3.cpp, you should deq 32 elements
  // at a time.

  int index_array[32] = {-1};

  if (Q[tid].deq_32(index_array) == -1)
  {
    // Error: invalid index
  }
  else
  {
    for (int i = 0; i < 32; i++)
    {
      // dynamic work based on task
      int index  = index_array[i];
      float base = result_parallel[index]; // <- rc 2

      for (int j = 0; j < mult[index] - 1; j++)
      {
        result_parallel[index] = result_parallel[index] + base;
      }
    }
  }

  // // track how many threads are finished
  atomic_fetch_add(&finished_threads, 1);

  // // look for any thread that needs help finishing their task
  while (finished_threads.load() != num_threads)
  {
    int target = (tid + 1) % NUM_THREADS; // pick a thread to steal from

    if (Q[target].deq_32(index_array) == -1)
    {
      // Thread chosen has nothing left to work on.
      // Pick a thread to steal from
      target = (tid + 1) % NUM_THREADS;
    }
    else
    {
      for (int i = 0; i < 32; i++)
      {
        // dynamic work based on task
        int index  = index_array[i];
        float base = result_parallel[index]; // rc 1

        for (int j = 0; j < mult[index] - 1; j++)
        {
          result_parallel[index] = result_parallel[index] + base; // rc 1 // rc 2
        }
      }
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
  float *result_parallel = new float[SIZE];
  int   *mult            = new int[SIZE];

  for (int i = 0; i < SIZE; i++) { result_parallel[i] = i; }

  linear_work(mult, SIZE);

  // Launch NUM_THREADS threads to initialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.
  thread thread_array[NUM_THREADS];
  init_queue_array(SIZE / NUM_THREADS);

  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_enq, SIZE, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }

  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing
  // hint: this part should be the same as in main3.cpp
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i] = thread(parallel_mult, result_parallel, mult, i, NUM_THREADS); }
  for (int i = 0; i < NUM_THREADS; i++) { thread_array[i].join(); }

  delete[] mult;
  delete[] result_parallel;

  return 0;
}
