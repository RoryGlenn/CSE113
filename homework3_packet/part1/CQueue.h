
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
    head.store(0);
    tail.store(0);

    for (int i = 0; i < CQUEUE_SIZE; i++)
    {
      list[i] = 0;
    }
  }

  bool is_empty()
  {
    if ( head.load() == tail.load() )
    {
      return true;
    }

    return false;
  }

  bool is_full()
  { 
    if ( ((head.load() + 1) % CQUEUE_SIZE) == tail.load() )
    {
      return true;
    }

    return false;
  }

  // enq: increment head
  void enq(float e)
  {
    while ( is_full() ) { /* spin */ }

    list[head.load()] = e;
    head.store( (head.load() + 1) % CQUEUE_SIZE );
  }

  // It enqueues 8 floats starting at the initial location of the array, i.e. e[0] - e[7]. 
  void enq_8(float e[8])
  {
    // Implement me for part 4

    while ( is_full() ) { /* spin */ }

    for (int i = 0; i < 8; i++) 
    {
      list[head.load()] = e[i];
      head.store((head.load()+1) % CQUEUE_SIZE);
    }

  }

  // deq increment tail
  float deq()
  {
    while ( is_empty() ) {  /* spin */ }

    float temp = list[tail.load()];
    list[tail.load()] = 0;
    tail.store( (tail.load() + 1) % CQUEUE_SIZE );
    return temp;
  }


  // reads 8 values from the queue and stores them in e[0] - e[7].
  void deq_8(float e[8])
  {
    // Implement me for part 4
    while ( is_empty() ) {  /* spin */ }

    for (int i = 0; i < 8; i++)
    {
      e[i] = list[tail.load()];
      list[tail.load()] = 0;
      tail.store( (tail.load() + 1) % CQUEUE_SIZE );
    }

  }

  int size()
  {
    return 0;
  }

private:
  // give me some variables!
  atomic_int head;
  atomic_int tail;
  atomic_int count;
  float list[CQUEUE_SIZE];
};
