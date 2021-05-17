#include <math.h>
#include <thread>
#include <atomic>
#include <assert.h>
#include "CQueue.h"

#define SIZE (1024 * 1024 * 8)

CQueue memory_to_trig;
CQueue trig_to_memory;


void memory_thread_func(float *a, int size)
{

  for (int i = 0; i < size; i++)
  {
    // Implement me!
    float loaded = a[i];
    memory_to_trig.enq(loaded);
    float to_store = trig_to_memory.deq();
    a[i] = to_store;    
  }
}


void trig_thread_func(int size)
{
  for (int i = 0; i < size; i++)
  {
    //Implement me!
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

  for (int i = 0; i < SIZE; i++)
  {
    float temp = 0.5 + i;

    if ( a[i] != cos(temp) )
    {
      printf("a[%d]: %f\n", i, a[i]);
      printf("cos(0.5 + %d): %f\n", i, cos(0.5+i));    
      assert(a[i] == cos(temp));
    }

  }  

  delete[] a;
  return 0;
}
