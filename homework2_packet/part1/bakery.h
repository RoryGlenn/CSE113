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

  int find_largest(int* array)
  {
    int largest = array[0];

    for (int i = 1; i < this->number_threads; i++)
    {
      if (largest < array[i])
      {
        largest = array[i];
      }
    }

    return largest;    
  }

  void init(int num_threads)
  {
    // Implement me!
    this->flag  = new bool[num_threads];
    this->label = new int[num_threads];
    this->number_threads = num_threads;

    for (int i = 0; i < num_threads; i++)
    {
      this->flag[i]  = false;
      this->label[i] = 0;
    }

  }

  void lock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id]  = true;
    // this->label[thread_id] = max( this->label[0], ...,this->label[this->number_threads-1] ) + 1;

    int largest = find_largest(this->label);

    this->label[thread_id] = largest + 1;

    for (int j = 0; j < this->number_threads; j++)
    {
      // spin
      while (j != thread_id && (this->flag[j] && (this->label[j] < label[thread_id]) || (this->label[thread_id] == this->label[j] && j < thread_id))) { };
    }


    // while ((3k != thread_id) && (this->flag[k] && (this->label[k], k)               << this->label[thread_id], thread_id)) { };

  }

  void unlock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id] = false;
  }


private:

  // Give me some private variables!
  bool *flag;
  int  *label;
  int   number_threads;

};
