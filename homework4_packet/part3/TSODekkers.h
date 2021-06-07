#include <atomic>
using namespace std;

#define FENCE asm volatile("mfence":::"memory");


// this should be the same as RDekkers with the change that every
// relaxed access should be memory_order_relaxed.
// your job is to use the following MACRO to fix the mutex.
// Think about the reorderings allowed under TSO and where the fence
// needs to be placed.

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest




class dekkers_mutex
{
public:
  dekkers_mutex()
  {
    // implement me!
    int num_threads = 2;
    turn.store(0, memory_order_relaxed);
    wants_to_enter = new atomic_bool[num_threads];

    for (int i = 0; i < num_threads; i++)
      wants_to_enter[i].store(false, memory_order_relaxed);

  }


  void lock(int tid)
  {
    // implement me!
      wants_to_enter[tid].store(true, memory_order_relaxed);
    FENCE      
      int wte = 0;
      if (tid == 0) { wte = 1; }


      while (wants_to_enter[wte].load(memory_order_relaxed)) 
      {
        if (turn.load(memory_order_relaxed) != tid)
        {
          wants_to_enter[tid].store(false, memory_order_relaxed);
        FENCE
          while (turn.load(memory_order_relaxed) != tid)
          {
            // spin...
          }

          wants_to_enter[tid].store(true, memory_order_relaxed);
        FENCE
        }
      }
  }


  void unlock(int tid)
  {
    // implement me!
    int wte = 0;
    if (tid == 0) { wte = 1; }
    
      turn.store(wte, memory_order_relaxed);
      wants_to_enter[tid].store(false, memory_order_relaxed);

  }

private:
  // Give me some private variables
  atomic_bool* wants_to_enter;
  atomic_int   turn;

};
