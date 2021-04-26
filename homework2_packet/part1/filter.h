#pragma once

#include <atomic>
using namespace std;

class mutex
{
public:
  mutex()
  {
    // Implement me!
    this->level  = new int[num_threads];
    this->victim = new int[num_threads];    
  }

  ~mutex()
  {
    delete[] this->level;
    delete[] this->victim;
  }

  void init(int num_threads)
  {
    // // Implement me!
    this->number_threads = num_threads;

    for (int i = 0; i < num_threads; i++)
    {
      this->level[i] = 0;
    }
  }

  void lock(int thread_id)
  {
    // Implement me!

    for (int i = 1; i < this->number_threads; i++)
    {
      this->level[thread_id] = i;
      this->victim[i]        = thread_id;

      // spin while conflicts exist
      // while there exists a thread that does not equal thread_id
      // while ((3k != thread_id) && level[k] >= i && victim[i] == thread_id) { }
      
      for (int j = 0; j < this->number_threads; j++)
      {
        // spin
        while ((j != thread_id) && this->level[j] >= i && this->victim[i] == thread_id) { }
      }
    }
  }

  void unlock(int thread_id)
  {
    // Implement me!
    level[thread_id] = 0;
  }

private:
  // Give me some private variables!
  // use atomic data type only when required
  // must use the store and load methods to access memory through the atomics.
  // not allowed to use atomic RMWs in any part of your implementations
  int* level;
  int* victim;
  int  number_threads;

};
