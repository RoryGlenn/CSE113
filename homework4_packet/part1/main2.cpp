#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#if defined(SRBARRIER)
#include "SRBarrier.h"
#elif defined(SROBARRIER)
#include "SROBarrier.h"
#else
#error "no barrier specified!"
#endif

barrier_object B;

// implement an optimized variant of the sense reversing barrier of the 
// previous section by adding relaxed peeking and yielding (similar to the mutexes).

void repeated_blur(double *input, double *output, int size, int tid) 
{

  B.barrier(tid);

  for (int i = 1; i < size - 1; i++) 
  {
    output[i] = (input[i] + input[i + 1] + input[i - 1]) / 3;
  }
  
}



int main(int argc, char *argv[])
{
  int     num_threads = 8;
  double* input       = new double[SIZE];
  double* output      = new double[SIZE];  
  thread  thread_array[num_threads];

  if (argc > 1) { num_threads = atoi(argv[1]); }

  for (int i = 0; i < SIZE; i++)
  {
    double randval = fRand(-100.0, 100.0);
    input[i]       = randval;
    output[i]      = randval;
  }

  B.init(num_threads);

  auto time_start = chrono::high_resolution_clock::now();

  // Launch threads once
  for (int i = 0; i < num_threads; i++) 
  { 
    int chunk_size  = SIZE / num_threads;
    thread_array[i] = thread(repeated_blur, &input[i * chunk_size], &output[i * chunk_size], chunk_size, i);

    // Swap input and output pointers.
    double *tmp = input;
    input       = output;
    output      = tmp;

  }

  // Join threads once
  for (int i = 0; i < num_threads; i++) { thread_array[i].join(); }

  auto   time_end       = std::chrono::high_resolution_clock::now();
  auto   time_duration  = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds   = time_duration.count() / 1000000000.0;
  std::cout << "timings: " << time_seconds << std::endl;

  delete[] input;
  delete[] output;

  return 0;  
}
