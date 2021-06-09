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





#include <atomic>
#include <mutex>
using namespace std;


class AddOnlySet
{
private:
    int end_index;
    int *elements;
    mutex m1;
    mutex m2;

public:
    AddOnlySet(int s)
    {
        end_index = 0;
        elements = new int[s];
        for (int i = 0; i < s; i++)
        {
            elements[i] = -1;
        }
    }

    bool contains(int check)
    {
        m2.lock();

        for (int i = 0; i < end_index; i++)
        {
            if (elements[i] == check)
            {
                m2.unlock();
                return true;
            }
        }

        m2.unlock();
        return false;
    }

    void add(int to_add)
    {
        m1.lock();

        if (contains(to_add))
        {
            m1.unlock();
            return;
        }
        else
        {
            elements[end_index] = to_add;
            end_index++;
        }

        m1.unlock();
    }

};