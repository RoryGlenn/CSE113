#include <shared_mutex>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


// Llist_node
////////////////////////////////////////////
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



// CSE113_Stack
/////////////////////////////////////////////////////////
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

    int temp_data = current->data;

    shared_mtx.unlock_shared();
    return temp_data;
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


  void swap_pop()
  {

    if (start == NULL)
    {
      return;
    }

    if (start->next == NULL)
    {
      delete start;
      start = NULL;
      return;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL)
    {
      previous = current;
      current = current->next;
    }

    previous->next = NULL;
    delete current;

  }


  void swap_push(int p)
  {

    if (start == NULL)
    {
      start = new Llist_node(p);
      return;
    }

    Llist_node *current = start;

    while (current->next != NULL)
    {
      current = current->next;
    }

    current->next = new Llist_node(p);
  }


  void swaptop(int to_swap)
  {
    // Implement me!

    shared_mtx.lock();

    if (start == NULL)
    {
      shared_mtx.unlock();
      return;
    }

    // check if top is the same or not
    int temp_data = start->data;

    if (temp_data != to_swap)
    {
      // swap the top
      this->swap_pop();
      this->swap_push(to_swap);
    }

    shared_mtx.unlock();
  
  }


private:
  Llist_node *start;
  shared_mutex shared_mtx;

};
