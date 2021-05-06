#include <thread>
#include <mutex>
#include <atomic>

#include <iostream>
using namespace std;

// Question 4: Mutex implementation
// Assume you are on a system that only supports bits and atomic bits, with the types called “bit”
// and “atomic_bit”, respectively. The following atomic RMWs are provided:

// bit atomic_fetch_and(atomic_bit *b, bit n);
// bit atomic_fetch_or(atomic_bit *b, bit n);
// bit atomic_fetch_xor(atomic_bit *b, bit n);

// Each of these instructions, performs the binary op (and, or, xor) on the location pointed to by b,
// with the value n as the second operand. The operation is performed atomically, i.e., it cannot
// be interleaved. The value at b, before the operation, is returned.

// a) implement an atomic RMW mutex using these operations. It should resemble a lock like the
// CAS or exchange lock.

// b) the architects are willing to make one of the atomic operations much faster than any of the
// others. You can pick one of the operations, and with that operation, you should implement a
// “relaxed peeking” optimization to the lock function of your solution in part (a).


// int atomic_fetch_add(atomic_int *a, value v)
// {
//     do
//     {
//         int old_val = a->load();
//         int new_val = old_val + v;
//         bool success = atomic_compare_exchange(a, &old_val, new_val);
//     } while (!success)
// }



// bool atomic_compare_exchange_strong(atomic *a, value *expected, value replace)
// {
//     value tmp = a.load();

//     if (tmp == *expected)
//     {
//         a.store(replace);
//         return true;
//     }

//     *expected = tmp;
//     return false;
// }

class CAS_mutex
{
public:
    CAS_mutex()
    {
        flag = 0;
    }


    void lock(int thread_id)
    {
        int e = 0;
        while (atomic_compare_exchange(&flag, &e, 1) == false)
        {
            e = 0;
        }
    }

    void unlock(int thread_id)
    {
        flag.store(0);
    }

private:
    atomic_int flag;
}


//////////////////////////////////////
class RMW
{

public:
    void lock()
    {
        bool e = false;
        int acquired = false;

        while (acquired == false)
        {
            // acquired = atomic_compare_exchange_strong(&flag, &e, true);
            auto loaded = atomic_load(&flag, &e);
            auto and = atomic_fetch_and(&flag, &loaded);
            auto store = atomic_store(&flag, &and);

            e = false;
        }
    }

    bool unlock()
    {
        bool e = false;
        return atomic_compare_exchange_strong(&flag, &e, true);
    }

private:
    atomic_bool flag;
    bit *b;
    atomic_bit a;
};
