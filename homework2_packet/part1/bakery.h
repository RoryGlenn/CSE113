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
  }

  ~mutex()
  {
    delete[] this->label;
    delete[] this->flag;
  }

  int find_largest(atomic<int>* array)
  {
    int largest = array[0].load(); 

    for (int i = 1; i < number_threads; i++)
    {
      if (largest < array[i].load())
      {
        largest = array[i].load();
      }
    }

    return largest;
  }

  void init(int num_threads)
  {
    // Implement me!
    flag  = new atomic<bool>[num_threads];
    label = new atomic<int>[num_threads];
    number_threads = num_threads;

    for (int i = 0; i < num_threads; i++)
    {
      flag[i].store(false);
      label[i].store(0);
    }
  }

  // bakery algorithm
  void lock(int thread_id)
  {
    // Implement me!
    flag[thread_id].store(true);
    label[thread_id].store( find_largest(label) + 1 );

    for (int j = 0; j < number_threads; j++)
    {
      while ( j != thread_id && (flag[j].load() && (label[j].load() < label[thread_id].load()) || (label[thread_id].load() == label[j].load() && j < thread_id)) ) 
      {
        /* spin */ 
        this_thread::yield();
      }
    }

  }


  void unlock(int thread_id)
  {
    // Implement me!
    flag[thread_id].store(false);
  }

private:
  // Give me some private variables!
  atomic<bool>* flag;
  atomic<int>*  label;
  int number_threads;
};
