#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


void repeated_blur(double *input, double *output, int size)
{
  for (int i = 1; i < size - 1; i++)
  {
    output[i] = (input[i] + input[i + 1] + input[i - 1]) / 3;
  }
}


int main(int argc, char *argv[])
{
  int num_threads = 8;

  if (argc > 1)
  {
    num_threads = atoi(argv[1]);
  }

  double *input  = new double[SIZE];
  double *output = new double[SIZE];

  for (int i = 0; i < SIZE; i++)
  {
    double randval = fRand(-100.0, 100.0);
    input[i]  = randval;
    output[i] = randval;
  }

  auto time_start = std::chrono::high_resolution_clock::now();
  thread thread_array[num_threads];


  for (int r = 0; r < REPEATS; r++)
  {
    for (int i = 0; i < num_threads; i++)
    {
      // Launch threads to compute the blur
      thread_array[i] = thread(repeated_blur, input, output, SIZE);
    }
  }

  for (int i = 0; i < num_threads; i++)
  {
    // join threads
    thread_array[i].join();
  }

    // Swap input and output pointers.
  double *tmp = input;
  input       = output;
  output      = tmp;


  auto   time_end       = std::chrono::high_resolution_clock::now();
  auto   time_duration  = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds   = time_duration.count() / 1000000000.0;

  std::cout << "timings: " << time_seconds << std::endl;

  delete[] input;
  delete[] output;
  return 0;
}
