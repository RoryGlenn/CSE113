#include <atomic>
#include <iostream>
#include <thread>
#include "SRBarrier.h"
using namespace std;

#define TEST_ITERATIONS (1024 * 256)


// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest
barrier_object B;

atomic_int x(0);
atomic_int y(0);

int var0 = 0;
int var1 = 0;

void t0_function()
{
  // complete me!
  B.barrier(0);
  x.store(1, memory_order_seq_cst);
  var0 = y.load(memory_order_seq_cst);
}


void t1_function()
{
  // complete me!
  B.barrier(1);
  y.store(1, memory_order_seq_cst);
  var1 = x.load(memory_order_seq_cst);
}

int main()
{
  int output0 = 0;
  int output1 = 0;
  int output2 = 0;
  int output3 = 0;

  B.init(2);

  for (int i = 0; i < TEST_ITERATIONS; i++)
  {
    // Run a test iteration
    x.store(0);
    y.store(0);

    // Run a test iteration
    thread t0 = thread(t0_function);
    thread t1 = thread(t1_function);

    t0.join();
    t1.join();

    // Record a histogram, fill in the conditions
    if (var0 == 1 && var1 == 1)      { output0++; }
    else if (var0 == 1 && var1 == 0) { output1++; }
    else if (var0 == 0 && var1 == 1) { output2++; }
    else if (var0 == 0 && var1 == 0) { output3++; } // This should be the relaxed behavior
  }

  // Complete the print out using your output instantiations
  cout << "histogram of different observations:" << endl;
  cout << "output0: " << output0 << endl;
  cout << "output1: " << output1 << endl;
  cout << "output2: " << output2 << endl;
  cout << "output3: " << output3 << endl << endl;
  cout << "relaxed behavior frequency: " << float(output3) / float(TEST_ITERATIONS) << endl;

  return 0;
}
