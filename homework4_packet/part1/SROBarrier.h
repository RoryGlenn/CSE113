#include <atomic>
#include <thread>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


class barrier_object
{
public:
  barrier_object() { /* Probably don't need to do anything here*/ }

  void init(int num_threads)
  {
    // Implement me
    size = num_threads;
    sense.store(false); 
    count.store(num_threads);
    threadSense = new bool[num_threads];
    for (int i = 0; i < num_threads; i++) { threadSense[i] = true; }
  }

  void barrier(int tid)
  {
    bool local_sense  = threadSense[tid];
    int  position     = atomic_fetch_sub(&count, 1);
    
    if (position == 1)
    {
      count.store(size);
      sense.store(local_sense);
    }
    else
    {
      while (sense.load(memory_order_relaxed) != local_sense) 
      {
        this_thread::yield();
      }

      // need a fence to synchronize and make sure no reordering happens
      sense.load();
    }

    threadSense[tid] = !local_sense;
  }


private:
  // Give me some private variables
  atomic_int  count;
  atomic_bool sense;
  int         size;
  bool*       threadSense;  
};
