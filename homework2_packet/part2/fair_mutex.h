// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#pragma once
#include <atomic>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono_literals;

class rw_mutex
{

public:
  rw_mutex()
  {
    // Implement me!
    writer              = false;
    num_readers         = 0;
    num_writers_waiting = 0;
  }

  void lock_reader()
  {
    // Implement me!

    // if there is a writer waiting, we should yield
    if (num_writers_waiting > 0)
    {
      this_thread::sleep_for(std::chrono::microseconds(50));
      // this_thread::yield();
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

    // num_writers_waiting isn't thread safe, make sure to lock it
    internal_mutex.lock();
    num_writers_waiting++;
    internal_mutex.unlock();

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
    
    internal_mutex.lock();
    num_writers_waiting--;
    internal_mutex.unlock();

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
  int num_readers;
  int num_writers_waiting;
  bool writer;
  mutex internal_mutex;

};
