#include <atomic>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// The SenseBarrier class: a sense-reversing barrier
class barrier_object
{
public:
  barrier_object() { /* Probably don't need to do anything here*/ }

  void init(int num_threads)
  {
    // Implement me
    size = num_threads;
    
    // true for even-numbered phases and false otherwise.
    // Each SenseBarrier object has a Boolean sense field indicating the sense of the currently executing phase
    sense.store(false);
    count.store(num_threads);
    threadSense = new bool[num_threads];
    for (int i = 0; i < num_threads; i++) { threadSense[i] = true; }
  }

  void barrier(int tid)
  {
    bool local_sense = threadSense[tid];
    int  position    = atomic_fetch_sub(&count, 1);
    
    if (position == 1)
    {
      count.store(size);
      sense.store(local_sense);
    }
    else
    {
      while (sense.load() != local_sense) 
      {
        // spin ...
      }
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
