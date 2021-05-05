#pragma once

// docker pull reeselevine/cse113:latest
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// what is the built in lock in C++?

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

  int find_largest(int *array)
  {
    int largest = array[0];  // <- race (i think its ok though?)

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
    this->flag = new bool[num_threads];
    this->label = new int[num_threads];
    this->number_threads = num_threads;

    for (int i = 0; i < num_threads; i++)
    {
      this->flag[i] = false;
      this->label[i] = 0;
    }
  }

  // bakery algorithm
  void lock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id] = true; // <- race (i think its ok though?)

    int largest = find_largest(this->label);

    this->label[thread_id] = largest + 1; // <- race (i think its ok though?)

    for (int j = 0; j < this->number_threads; j++)
    {
       // is this suppose to be   != or ==     ?
      if (thread_id == j) 
      {
        continue;
      }
      else
      {
        // old spin
        // while (j != thread_id && (this->flag[j] && (this->label[j] < label[thread_id]) || (this->label[thread_id] == this->label[j] && j < thread_id)));

        // when running the binary, I will get caught in an infinite loop once every other time.
        while (this->flag[j] && (this->label[j] < label[thread_id]) || (this->label[thread_id] == this->label[j] && j < thread_id)) 
        { 
          // printf("thread_id: %d\n", thread_id);
          // printf("label[%d]: %d\n", thread_id, label[thread_id]);
          printf("j: %d\n", j);
        };

      }
    }

    // from the book
    // while ((3k != thread_id) && (this->flag[k] && (this->label[k], k) << this->label[thread_id], thread_id)) { };
  }

  void unlock(int thread_id)
  {
    // Implement me!
    this->flag[thread_id] = false; // <- race (i think its ok though?)
  }

private:
  // Give me some private variables!
  bool *flag;
  int *label;
  int number_threads;
};
