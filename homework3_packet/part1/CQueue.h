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
    head.store(-1);
    tail.store(-1);
  }


  // when we enq, we increment the tail
  // enq to the head
  void enq(float e)
  {

    // queue is full
    while ( ((tail.load()+1) % CQUEUE_SIZE) == head.load() )
    {
      // spin...
    }

    // queue is empty so insert the first element
    if (head.load() == -1)
    {
      head.store(0);
    }

    tail.store( (tail.load() + 1) % CQUEUE_SIZE );

    list[tail.load()].store(e); // <- buffer-overflow
    
  }


  void enq_8(float e[8])
  {
    // Implement me for part 4
  }


  // when we deq, we increment the head
  // deq from the tail
  float deq()
  {
    // check if queue is empty
    while ( head.load() == -1 && tail.load() == -1 )
    {
      // queue is empty
      // spin...
    }

    int head_index = head.load();

    // if there is only one element in the queue
    if (head.load() == tail.load())
    {
      head.store(-1);
      tail.store(-1);
    }
    else
    {
      head.store( (head.load() + 1) % CQUEUE_SIZE);
    }

    return list[head_index].load();

  }

  void deq_8(float e[8])
  {
    // Implement me for part 4
  }

  int size()
  {
    return 0;
  }

private:
  // give me some variables!
  atomic_int head;
  atomic_int tail;
  atomic<float> list[CQUEUE_SIZE];
};
