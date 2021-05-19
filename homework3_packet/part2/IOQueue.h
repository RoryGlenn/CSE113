#include <atomic>
#include <iostream>
using namespace std;

class IOQueue
{

public:
  IOQueue()
  {
    head.store(0);
    tail.store(0);
  }

  // Use this function to initialize the queue to
  // the size that you need.
  void init(int size)
  {
    list_ptr = new int[size];
  }

  // enqueue the element e into the queue
  void enq(int e)
  {
    int reserved_index = atomic_fetch_add(&tail, 1);
    list[reserved_index] = e;
  }

  // return a value from the queue.
  // return -1 if there is no more values
  // from the queue.
  int deq()
  {
    int reserved_index = atomic_fetch_add(&head, 1);
    if (reserved_index > SIZE) { throw exception("Error: array index out of bounds"); }
    return list[reserved_index];
  }
  

  int size()
  {
    return tail.load() - head.load();
  }

  // return 32 values from the queue. The
  // values should be returned through
  // the array passed in.
  // return 0 if successful. return 1 if not
  // i.e. if the queue does not have 32 elements
  int deq_32(int ret[32])
  {
    return -1;
  }


private:
  // Give me some private variables
  atomic_int head;
  atomic_int tail;
  int list[SIZE];
  int* list_ptr;

};
