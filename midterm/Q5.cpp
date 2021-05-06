#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
using namespace std;

// Q5a ANSWER

//////////////////////////////////
class CAS_mutex
{
public:
    CAS_mutex()
    {
        flag = 0;
    }

    void lock(int thread_id)
    {

        // check if we are already locked

        if (flag.load() == 1)
        {
            return;
        }

        int e = 0;
        while (atomic_compare_exchange_strong(&flag, &e, 1) == false)
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
};






// Q5b ANSWER

//////////////////////////////////
class CAS_mutex_b
{
public:
    CAS_mutex_b()
    {
        flag = 0;
    }

    void lock(int thread_id)
    {

        // check if we are already locked
        if (flag.load() == 1)
        {
            return;
        }

        int e = 0;
        while (atomic_compare_exchange_strong(&flag, &e, 1) == false)
        {
            this_thread::yield();
            e = 0;
        }
    }

    void unlock(int thread_id)
    {
        flag.store(0);
    }

private:
    atomic_int flag;
};



void increment(int* a, int thread_id, int* t1_count, int* t2_count, CAS_mutex_b* mtx)
{
    for (int i = 0; i < 100; i++)
    {
        if (thread_id == 1)
        {
            t1_count[0]++;
        }
        else if (thread_id == 2)
        {
            t2_count[0]++;
        }
        
        mtx->lock(thread_id);
        // printf("thread_id %d, a[0]: %d\n", thread_id, a[0]); <- printing here causes race condition
        a[0]++;
        mtx->unlock(thread_id);
    }
}


int main()
{
    CAS_mutex_b mtx;
    // CAS_mutex mtx;
    int* a        = new int[1];
    int* t1_count = new int[1];
    int* t2_count = new int[1];

    t1_count[0] = 0;
    t2_count[0] = 0;

    thread t1 = thread(increment, a, 1, t1_count, t2_count, &mtx);
    thread t2 = thread(increment, a, 2, t1_count, t2_count, &mtx);

    t1.join();
    t2.join();

    cout << "t1 incremented " << t1_count[0] << endl;
    cout << "t2 incremented " << t2_count[0] << endl;

    return 0;

}