#include <shared_mutex>
using namespace std;

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


//////////////////////////////////////////////////////////
class CSE113_Stack
{

public:

  CSE113_Stack()
  {
    start = NULL;
  }

  int pop()
  {

    shared_mtx.lock();
    
    if (start == NULL)
    {
      shared_mtx.unlock();
      return -1;
    }
    
    if (start->next == NULL)
    {
      int ret = start->data;
      delete start;
      start = NULL;
      shared_mtx.unlock();
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL)
    {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;

    shared_mtx.unlock();
    return ret;
  }

  int peek()
  {
    shared_mtx.lock_shared();

    if (start == NULL)
    {
      shared_mtx.unlock_shared();
      return -1;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    shared_mtx.unlock_shared();
    return current->data;
  }


  void push(int p)
  {
    shared_mtx.lock();

    if (start == NULL)
    {
      start = new Llist_node(p);
      shared_mtx.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    current->next = new Llist_node(p);
    
    shared_mtx.unlock();
  }

private:
  Llist_node *start;

  // You should identify when you need to use the full lock, and when you can use the reader lock.
  // Recall that the reader lock call is lock_shared and unlock_shared.
  shared_mutex shared_mtx;
};
