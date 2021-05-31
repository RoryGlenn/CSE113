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
    // printf("tid: %d\n", tid);
    // printf("threadSense[%d]: %d\n", tid, threadSense[tid]);

    bool local_sense  = threadSense[tid];
    int  position     = atomic_fetch_sub(&count, 1);
    // printf("position: %d\n", position);
    if (position == 1)
    {
      count.store(size);
      // printf("count.load(): %d\n", count.load());
      sense.store(local_sense);
      // printf("sense.load(): %d\n", sense.load());
    }
    else
    {
      while (sense.load() != local_sense) 
      {
        // printf("spinning\n");
      }
    }

    threadSense[tid] = !local_sense;
    // printf("threadSense[%d]: %d\n", tid, threadSense[tid]);

  }

private:
  // Give me some private variables
  atomic_int  count;
  atomic_bool sense;
  int         size;
  bool*       threadSense;

};
