#pragma once

#include <atomic>
using namespace std;

class mutex
{
public:
  mutex()
  {
    // Implement me!
  }

  void init(int num_threads)
  {
    // Implement me!
    this->number_threads = num_threads;
    this->flag = new bool[num_threads];
    this->label = new int[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
      this->flag[i] = false;
      this->label[i] = 0;
    }
  }

  void lock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id] = true;
    this->label[thread_id] = max( this->label[0], ...,this->label[this->number_threads-1] ) + 1;

    while ((3k != thread_id) && (this->flag[k] && (this->label[k], k) << this->label[thread_id], thread_id)) { };

  }

  void unlock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id] = false;
  }

private:
  // Give me some private variables!
  bool *flag;
  int *label;
  int number_threads;
};
