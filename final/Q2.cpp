#include <atomic>
using namespace std;

class Semaphore
{

public:
    Semaphore(int num_allowed_threads)
    {
        this->num_allowed_threads = num_allowed_threads;
        counter.store(num_allowed_threads);
        has_entered = new bool[num_allowed_threads];
        for (int i = 0; i < num_allowed_threads; i++)
        {
            has_entered[i] = false;
        }
    }

    int enter(int tid)
    {
        // Up to N threads (specified in the constructor) are allowed to enter.
        if (!has_entered[tid])
        {
            while (true)
            {
                if (counter.load() > 0)
                {
                    atomic_fetch_sub(&counter, 1);
                    has_entered[tid] = true;
                    return 0; // SUCCESS
                }
            }
        }

        return -1; // FAILURE
    }

    int exit(int tid)
    {
        // threads that exit should make room for more threads to enter
        if (has_entered[tid])
        {
            atomic_fetch_add(&counter, 1);
            has_entered[tid] = false;
            return 0; // SUCCESS
        }
        return -1; // FAILURE
    }

    void resize(int new_num_allowed_threads) 
    {
        while (true)
        {
            // Assuming that resize() should be called when all threads are outside of the critical section.
            // Then it will be safe to modify our private variables.
            if (counter.load() == this->num_allowed_threads)
            {
                counter.store(new_num_allowed_threads);
                has_entered = new bool[new_num_allowed_threads];

                for (int i = 0; i < new_num_allowed_threads; i++)
                {
                    has_entered[i] = false;
                }

                break;
            }
        }
    }

private:
    atomic_int counter;
    bool *has_entered;
    int num_allowed_threads;
};