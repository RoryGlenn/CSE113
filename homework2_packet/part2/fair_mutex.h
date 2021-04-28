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
    this->num_readers = 0;
    this->writer = false;
  }

  void lock_reader()
  {
    // Implement me!
    bool acquired = false;

    while (!acquired)
    {
      internal_mutex.lock();

      if (!writer)
      {
        acquired = true;
        num_readers++;
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

    // this lock is for writers
    bool acquired = false;

    while (!acquired)
    {
      internal_mutex.lock();

      if (!writer && num_readers == 0)
      {
        acquired = true;
        writer = true;
      }

      internal_mutex.unlock();
    }
  }

  void unlock()
  {
    // Implement me!

    // for writers only
    internal_mutex.lock();
    writer = false;
    internal_mutex.unlock();
  }

private:
  // Give me some private variables!
  mutex internal_mutex;
  int num_readers;
  bool writer;
};
