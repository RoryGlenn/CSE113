
#include <math.h>
#include <thread>
#include <atomic>
#include <iostream>

#if defined(SYNCQUEUE)
#include "CQueueSync.h"
#else
#include "CQueue.h"
#endif

#define SIZE (1024 * 1024 * 8) // 8,388,608

CQueue memory_to_trig;
CQueue trig_to_memory;

void print_array(float *array)
{
  for (int i = 0; i < SIZE; i++)
  {
    printf("array[%d]: %f\n", i, array[i]);
  }
}

// A memory thread, which can access memory.
// The array of floats is sent to the memory thread.
// For each item in the array, the memory thread loads the value, and sends it to the trig thread for computation.
void memory_thread_func(float *a, int size)
{
  // producer

  for (int i = 0; i < size; i++)
  {
    float loaded = a[i];
    memory_to_trig.enq(loaded);
    float to_store = trig_to_memory.deq();
    a[i] = to_store;
  }
}

// trig thread, which can execute trigonometry functions.
// The trig thread performs the computation, and sends the value back
// to the memory thread. The memory thread then stores the value back to memory.
void trig_thread_func(int size)
{
  // consumer

  for (int i = 0; i < size; i++)
  {
    float consume = memory_to_trig.deq();
    consume = cos(consume);
    trig_to_memory.enq(consume);
  }
}

int main()
{
  float *a = new float[SIZE];

  for (int i = 0; i < SIZE; i++)
  {
    a[i] = 0.5 + i;
  }

  std::thread memory_thread(memory_thread_func, a, SIZE);
  std::thread trig_thread(trig_thread_func, SIZE);

  memory_thread.join();
  trig_thread.join();

  return 0;
}
