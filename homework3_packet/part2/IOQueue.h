#include <atomic>
#include <iostream>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


// Queue in which multiple threads read (deq), or write (enq), but not both

// Why would we want a thing?

// Computation done in phases:
  // First phase prepares the queue (by writing into it)
  // All threads join
  // Second phase reads values from the queue

class IOQueue
{

public:
  IOQueue()
  {
  }

  ~IOQueue()
  {
    delete[] list_ptr;
  }


  // Use this function to initialize the queue to
  // the size that you need.
  void init(int size)
  {
    head.store(0); 
    tail.store(0);
    list_ptr = new int[size];
  }

  // enqueue the element e into the queue
  void enq(int e) // write = enq()
  {
    int reserved_index = atomic_fetch_add(&head, 1);
    list_ptr[reserved_index] = e;
  }

  // return a value from the queue.
  // return -1 if there if no more values
  // from the queue.
  int deq() // read = deq()
  {
    int reserved_index = atomic_fetch_add(&tail, 1);
    // if (reserved_index > SIZE) { return -1; }
    if (reserved_index > head.load()) { return -1; }
    return list_ptr[reserved_index];
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
  int* list_ptr;

};
