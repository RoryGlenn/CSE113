#include <atomic>

// this should be the same as RDekkers with the change that every
// relaxed access should be memory_order_relaxed.
// your job is to use the following MACRO to fix the mutex.
// Think about the reorderings allowed under TSO and where the fence
// needs to be placed.

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


#define FENCE asm volatile("mfence":::"memory");

class dekkers_mutex {
public:
  dekkers_mutex() {
    // implement me!
  }

  void lock(int tid) {
    // implement me!
  }

  void unlock(int tid) {
    // implement me!
  }

private:
  // Give me some private variables  
};
