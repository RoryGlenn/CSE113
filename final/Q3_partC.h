// a) Recall that thread safety means that a program is free from data-conflicts and concurrent
// behavior is well-specified. As written, is this data structure thread-safe? If the private variables
// are changed to atomic variables, is the data-structure thread safe? If not, give an example
// where the concurrent calls to the public methods (add and contain) could cause a
// problematic result according to the specification of the set.

// As written, this data structure is not thread-safe.
// Even if the private variables are changed to atomic variables, the data structure is still not thread-safe.
// Assume that t0 and t1 are accessing the same AddOnlySet object variable.
// While t0 is inside of add(), calling
// elements[end_index] = to_add; (in the atomic case: elements[end_index].store(to_add))
// end_index++;                  (in the atomic case: atomic_fetch_add(&end_index, 1)),
// t1 is inside of contains, iterating through the elements array.
// This is a problem because while t0 is writing to the elements array, t1 is reading from it, thus causing a data race condition

// b) Add one or more mutex private variables, and call lock/unlock in the methods to make
// the class thread safe. You should not make the other private members atomic. You can add
// private methods if you’d like, but the API to the public methods must remain unchanged. Note
// that a data-conflict, i.e. concurrent accesses (where at least 1 access is a write) to a non-atomic
// variable is NOT thread safe, even if it isn’t obvious how the compilation and execution can lead
// to an incorrect result.

    // For this problem, I implemented two mutex's. One for contains() and one for add().
    // With these two mutexes in place, concurrent access to the functions add() and contains() is impossible.
    // Assume that t0 and t1 are accessing the same AddOnlySet object variable.
    // While t0 calls add(), t1 calls contains()
    // Case 1: t0 gets the m1 lock and the m2 lock
    // t1 must wait inside of contains until t0 releases the m2 lock.
    // Even if t1 called add(), it would still have to wait till t0 released the m1 lock
    // Case 2: t1 gets the m2 lock
    // t0 must wait inside of contains() until t1 releases the m2 lock

// c) Remove the mutex(es) from part (b) and make the class both thread-safe and lock-free.
// You are limited in that the only RMW you can use is the C++ compare_exchange_strong (i.e. what we used in the spin-locks).
// Justify in a few sentences why your implementation is correct, and explain why your example in
// part (a) is no longer allowed.

    // This implementation is correct because it provides mutual exclusion
    // Part a is no longer correct because we have provided mutual exclusion for add() and contains()
    // Because of this, there are no race-conditions, etc...



// if you let them claim indexes they won't block each other
// and you can claim indexes with compare exchange while also error checking
// but the error checking has to do making a copy of end_index
// if you copy end index, then check if the list contains 8, then when you go to add 8, if you see that end index is not the same anymore, it means a number was added and that number could be 8
// but you can check if the index is what you expect and also replace it with index+1 if it is with the compare exchange



#include <atomic>
using namespace std;

class AddOnlySet
{
private:
    atomic_int counter;
    atomic_int end_index;
    atomic_int *elements;
    atomic_int *flags;

public:
    AddOnlySet(int s)
    {
        counter.store(0);
        end_index.store(0);
        elements = new atomic_int[s];
        
        for (int i = 0; i < s; i++) { elements[i].store(-1); }
    }

    bool contains(int check)
    {
        for (int i = 0; i < end_index.load(); i++)
        {
            if (elements[i].load() == check)
            {
                return true;
            }
        }

        return false;
    }

    void add(int to_add)
    {
        int ei            = end_index.load();
        int local_counter = atomic_compare_exchange_strong(&counter, &counter.load(), counter.load()+1);

        if (contains(to_add))
        {
            return;
        }
        else
        {
            elements[end_index].store(to_add);
            atomic_compare_exchange_strong(&end_index, &end_index.load(), end_index.load()+1);
        }
    }

};