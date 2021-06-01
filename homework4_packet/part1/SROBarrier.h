#include <atomic>
#include <thread>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// • also known as weak memory behaviors
// • An execution that is NOT allowed by sequential consistency
// • A memory model that allows relaxed memory executions is known as a relaxed memory mode


// Add relaxed peeking and yielding (similar to the mutexes).

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
    }

    threadSense[tid] = !local_sense;
  }


  // void lock(int thread_id)
  // {
  //   bool e       = false;
  //   bool acquire = false;

  //   while (!acquired)
  //   {
  //     while (flag.load(memory_order_relaxed) == true) 
  //     {
  //       /* spin */ 
  //     };

  //     e = false;
  //     acquired = atomic_compare_exchange_strong(&flag, &e, true);
  //   }

  // }

private:
  // Give me some private variables
  atomic_int  count;
  atomic_bool sense;
  int         size;
  bool*       threadSense;  
};
