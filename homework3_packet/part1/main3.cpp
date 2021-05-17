#include <math.h>
#include <thread>
#include <atomic>
#include <assert.h>
#include <iostream>
#include "CQueue.h"

#define SIZE (1024 * 1024 * 8)

CQueue memory_to_trig;
CQueue trig_to_memory;

void memory_thread_func(float *a, int size)
{
  for (int i = 0; i < size; i+=8)
  {
    //Implement me!
    float loaded[8]   = {0};
    float to_store[8] = {0};

    for (int j = 0; j < 8; j++) { loaded[j] = a[i+j]; }
    for (int j = 0; j < 8; j++) { memory_to_trig.enq(loaded[j]); }
    for (int j = 0; j < 8; j++) { to_store[j] = trig_to_memory.deq(); }    
    for (int j = 0; j < 8; j++) { a[i+j] = to_store[j]; }

    // float loaded0 = a[i+0];
    // float loaded1 = a[i+1];
    // float loaded2 = a[i+2];
    // float loaded3 = a[i+3];
    // float loaded4 = a[i+4];
    // float loaded5 = a[i+5];
    // float loaded6 = a[i+6];
    // float loaded7 = a[i+7];

    // memory_to_trig.enq(loaded0);
    // memory_to_trig.enq(loaded1);
    // memory_to_trig.enq(loaded2);
    // memory_to_trig.enq(loaded3);
    // memory_to_trig.enq(loaded4);
    // memory_to_trig.enq(loaded5);
    // memory_to_trig.enq(loaded6);
    // memory_to_trig.enq(loaded7);

    // float to_store0 = trig_to_memory.deq();
    // float to_store1 = trig_to_memory.deq();
    // float to_store2 = trig_to_memory.deq();
    // float to_store3 = trig_to_memory.deq();
    // float to_store4 = trig_to_memory.deq();
    // float to_store5 = trig_to_memory.deq();
    // float to_store6 = trig_to_memory.deq();
    // float to_store7 = trig_to_memory.deq();
    
    // a[i+0] = to_store0;
    // a[i+1] = to_store1;
    // a[i+2] = to_store2;
    // a[i+3] = to_store3;
    // a[i+4] = to_store4;
    // a[i+5] = to_store5;
    // a[i+6] = to_store6;
    // a[i+7] = to_store7;
  }
}

void trig_thread_func(int size)
{

  for (int i = 0; i < size; i+=8)
  {
    //Implement me!
    float consume[8] = {0};

    for (int j = 0; j < 8; j++) { consume[j] = memory_to_trig.deq(); }
    for (int j = 0; j < 8; j++) { consume[j] = cos(consume[j]); }
    for (int j = 0; j < 8; j++) { trig_to_memory.enq(consume[j]); }   
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

  return 0;
}
