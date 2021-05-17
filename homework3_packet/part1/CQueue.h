
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
    count.store(0);

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
    count.store(count.load()+1);
  }

  void enq_8(float e[8])
  {
    // Implement me for part 4
  }

  // deq increment tail
  float deq()
  {
    while ( is_empty() ) {  /* spin */ }

    float temp = list[tail.load()];
    list[tail.load()] = 0;
    tail.store( (tail.load() + 1) % CQUEUE_SIZE );
    count.store( count.load() - 1 );
    return temp;
  }

  void deq_8(float e[8])
  {
    // Implement me for part 4
  }

  int size()
  {
    return count.load();
  }

private:
  // give me some variables!
  atomic_int head;
  atomic_int tail;
  atomic_int count;
  float list[CQUEUE_SIZE];
};
