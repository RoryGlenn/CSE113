
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

// time ./asyncQueue

#include <atomic>
#include <iostream>
using namespace std;

// #define CQUEUE_SIZE 2048
#define CQUEUE_SIZE 2

class CQueue
{
public:
  CQueue()
  {
    // Implement me!
    // head.store(-1);
    // tail.store(-1);

    head.store(0);
    tail.store(0);
    count.store(0);

    for (int i = 0; i < CQUEUE_SIZE; i++)
    {
      list[i].store(0);
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

  // enq increment head
  void enq(float e)
  {
    while ( is_full() ) { /* spin */ }

    list[head.load()].store(e);
    head.store( (head.load() + 1) % CQUEUE_SIZE );

    // list[tail.load()].store(e);

    // if (is_empty()) // <- this line is being triggered WAY too much!!!
    // {
    //   printf("enq empty\n");
    //   head.store(0);
    //   tail.store(0);
    // }
    // else
    // {
    //   tail.store( (tail.load() + 1) % CQUEUE_SIZE );
    // }

    // currently storing items at index 0 over and over again
    // this must mean that tail is not incrementing properly
    printf("head.load(): %d\n", head.load());
    
    // list[tail.load()].store(e);
    printf( "list[head.load()]: %f\n", list[head.load()].load() );

    count.store(count.load()+1);
    printf("count: %d\n", count.load());
    
  }

  void enq_8(float e[8])
  {
    // Implement me for part 4
  }

  // deq increment tail
  float deq()
  {
    while ( is_empty() ) {  /* spin */ }

    int temp = 0;
    temp = list[tail.load()];
    list[tail.load()] = 0;
    tail.store((tail.load() + 1) % CQUEUE_SIZE);    

    // if (head.load() == tail.load())
    // {
    //   temp = list[tail.load()];
    //   head.store(-1);
    //   tail.store(-1);
    // }
    // else
    // {
    //   temp = list[tail.load()];
    //   list[tail.load()] = 0;
    //   tail.store((tail.load() + 1) % CQUEUE_SIZE);
    // }

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
  atomic<float> list[CQUEUE_SIZE];
};
