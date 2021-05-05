#include <mutex>
using namespace std;

// docker pull reeselevine/cse113:latest
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest
// make

class Llist_node
{
public:
  Llist_node(int d)
  {
    data = d;
    next = NULL;
  }

  int data;
  Llist_node *next;

};


class CSE113_Stack
{
public:
  CSE113_Stack()
  {
    start = NULL;
  }

  int pop()
  {
    internal_mutex.lock();

    if (start == NULL)
    {
      internal_mutex.unlock();
      return -1;
    }

    if (start->next == NULL)
    {
      int ret = start->data;
      delete start;
      start = NULL;
      
      internal_mutex.unlock();
      return ret;
    }

    // move to the top of the stack
    Llist_node *current  = start->next;
    Llist_node *previous = start;

    while (current->next != NULL)
    {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;

    internal_mutex.unlock();
    return ret;
  }

  int peek()
  {
    internal_mutex.lock();

    if (start == NULL)
    {
      internal_mutex.unlock();
      return -1;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    internal_mutex.unlock();
    return current->data;
  }

  void push(int p)
  {
    internal_mutex.lock();

    if (start == NULL)
    {
      start = new Llist_node(p);
      internal_mutex.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    current->next = new Llist_node(p);
    internal_mutex.unlock();
  }


private:
  Llist_node *start;
  mutex internal_mutex;

};
