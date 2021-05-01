#pragma once

#include <atomic>
#include <mutex>
using namespace std;

class rw_mutex
{

public:
  rw_mutex()
  {
    // Implement me!
    writer = false;
    num_readers = 0;
    num_writers_waiting = 0;
  }

  void lock_reader()
  {
    // Implement me!

    // if there is a writer waiting, we should yield
    while (num_writers_waiting > 0)
    {
      this_thread::yield();
    }

    bool acquired = false;

    while (!acquired)
    {
      internal_mutex.lock();

      if (!writer)
      {
        num_readers++;
        acquired = true;
      }
      
      internal_mutex.unlock();
    }
  
  }

  void unlock_reader()
  {
    // Implement me!
    internal_mutex.lock();
    num_readers--;
    internal_mutex.unlock();
  }

  void lock()
  {
    // Implement me!
    num_writers_waiting++;
    bool acquired = false;
    
    while (!acquired)
    {
      internal_mutex.lock();
    
      if (!writer && num_readers == 0)
      {
        writer   = true;
        acquired = true;
      }
    
      internal_mutex.unlock();
      
    }
    
    num_writers_waiting--;

  }

  void unlock()
  {
    // Implement me!
    internal_mutex.lock();
    writer = false;
    internal_mutex.unlock();
  }

private:
  // Give me some private variables!
  bool writer;
  int num_readers;
  int num_writers_waiting;
  mutex internal_mutex;
};
