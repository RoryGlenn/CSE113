#include <atomic>

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

class barrier_object
{
public:
  barrier_object()
  {
    // Probably don't need to do anything here.
  }

  void init(int num_threads)
  {
    // Implement me
  }

  void barrier(int tid)
  {
    // Implement me
  }

private:
  // Give me some private variables
};
