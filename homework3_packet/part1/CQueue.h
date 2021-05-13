// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// time ./asyncQueue

#include <atomic>
#include <iostream>
using namespace std;

#define CQUEUE_SIZE 2048

class CQueue
{
public:
  CQueue()
  {
    // Implement me!
    list = new atomic<float>[CQUEUE_SIZE];
    head.store(-1);
    tail.store(-1);
  }

  void print_array()
  {
    for (int i = 0; i < CQUEUE_SIZE; i++)
    {
      printf("circular_list[%d]: %f\n", i, list[i].load());
    }
    exit(EXIT_FAILURE);
  }

  // enq to the head
  void enq(float e)
  {
    // queue is full
    while (this->size() >= CQUEUE_SIZE)
    {
      // spin...
    }

    // queue is empty so insert the first element
    if (head.load() == -1)
    {
      head.store(0);
    }

    tail.store( (tail.load() + 1) % CQUEUE_SIZE );
    list[0].store(e); // <- heap-buffer-overflow

  }

  void enq_8(float e[8])
  {
    // Implement me for part 4
  }

  // deq from the tail
  float deq()
  {
    // check if queue is empty
    while (this->size() <= 0)
    {
      // spin...
    }
    printf("head.load(): %d\n", head.load());

    int data = -1;
    if (head.load() != -1)
    {
      data = list[head.load()];
    }


    if (head.load() == tail.load())
    {
      head.store(-1);
      tail.store(-1);
    }
    else if (tail.load() == CQUEUE_SIZE - 1)
    {
      // queue is full so reposition the tail in the front
      tail.store(0);
    }
    else
    {
      tail.store(tail.load() + 1);
    }

    return data;
  }

  void deq_8(float e[8])
  {
    // Implement me for part 4
  }

  int size()
  {
    // check if the queue is full
    if (tail.load() == CQUEUE_SIZE - 1 && head.load() == 0)
    {
      return CQUEUE_SIZE;
    }

    // check if the queue is full
    if (tail.load()-1 == head.load())
    {
      return CQUEUE_SIZE;
    }

    // check if queue is empty
    if (head.load() == -1)
    {
      return 0;
    }

    return 2;
  }

private:
  // give me some variables!
  atomic_int head;
  atomic_int tail;
  atomic<float> *list;
};
