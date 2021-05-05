#pragma once

// docker pull reeselevine/cse113:latest
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#include <atomic>
using namespace std;

class mutex
{

public:

  mutex()
  {
    // Implement me!
    number_threads = 0;
  }

  ~mutex()
  {
    delete[] level;
    delete[] victim;
  }

  void init(int num_threads)
  {
    // Implement me!
    level  = new atomic<int>[num_threads];
    victim = new atomic<int>[num_threads];
    number_threads = num_threads;

    for (int i = 0; i < num_threads; i++)
    {
      level[i].store(0);
    }
  }

  void lock(int thread_id)
  {
    // Implement me!

    for (int i = 1; i < number_threads; i++)
    {
      level[thread_id].store(i);
      victim[i].store(thread_id);

      // spin while conflicts exist
      // while there exists a thread that does not equal thread_id
      // while ((3k != thread_id) && level[k] >= i && victim[i] == thread_id) { }

      for (int j = 0; j < number_threads; j++)
      {
        while ( (j != thread_id) && level[j].load() >= i && victim[i].load() == thread_id ) { /* spin */ }
      }
    }
  }

  void unlock(int thread_id)
  {
    // Implement me!
    level[thread_id].store(0);
  }

private:
  // Give me some private variables!
  atomic<int> *level;
  atomic<int> *victim;
  int number_threads;
};
