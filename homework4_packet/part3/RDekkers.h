#include <atomic>

// this should be the same as SCDekkers with the change that every
// relaxed access should be memory_order_relaxed

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

class dekkers_mutex
{
public:
  dekkers_mutex()
  {  
    // implement me!

  }

  void lock(int tid)
  {
    // implement me!

  }

  void unlock(int tid)
  {
    // implement me!
    
  }

private:
  // Give me some private variables
};
