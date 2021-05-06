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


class CSE113_Stack
{

public:

  CSE113_Stack()
  {
    start = NULL;
  }

  int pop()
  {

    s_mtx.lock();
    
    if (start == NULL)
    {
      s_mtx.unlock();
      return -1;
    }
    
    if (start->next == NULL)
    {
      int ret = start->data;
      delete start;
      start = NULL;
      s_mtx.unlock();
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

    s_mtx.unlock();
    return ret;
  }

  int peek()
  {
    s_mtx.lock_shared();

    if (start == NULL)
    {
      s_mtx.unlock_shared();
      return -1;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    int temp_data = current->data;

    s_mtx.unlock_shared();
    return temp_data;
  }


  void push(int p)
  {
    s_mtx.lock();

    if (start == NULL)
    {
      start = new Llist_node(p);
      s_mtx.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL)
    {
      current = current->next;
    }

    current->next = new Llist_node(p);
    
    s_mtx.unlock();
  }

private:
  Llist_node *start;
  shared_mutex s_mtx;
  
};
