
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;


// Q2a. answer!
// We will get a mutual exclusion violation:
// P1 does give up:=1;
// P0 does give up:=0;
// P0 does interested[0]:=true;
// P0 does while(give up == 0 && interested [1]); // (#t and #f)  #f
// P0 enters the CS.
// P1 does interested [1]:=true;
// P1 does while(give up == 1 && interested [0]); // (#f and #t)  #f
// P1 enters the CS.
// now both processes are in the critical section.


// Q2b. answer!
// We will get a mutual exclusion violation (race condition)
// the flag variable is responsible for indicating the intent of the label variable.
// With line 13 and 14 swapped, we don't know what the intent is
// The purpose of the first 3 lines is that if a process is changing 
// its label value then at that time some other process should not be allowed to
// check its old ticket value which is now obsolete.

class Mutex
{
public:
    Mutex()
    {
        flag = new bool[2];
        victim = 0;
    }

    ~Mutex()
    {
        delete[] flag;
    }

    void lock(int thread_id)
    {
        int i = thread_id;
        int j = 1 - i;
        flag[i] = true;
        victim = i;

        while (flag[j] && victim == i)
        {
        }
    }

    void unlock(int thread_id)
    {
        int i = thread_id;
        flag[i] = false;
    }

private:
    bool* flag;
    int victim;

};


void do_stuff(int* a, int thread_id, Mutex* mtx)
{
    for (int i = 0; i < 1000000; i++)
    {
        mtx->lock(thread_id);
        a++;
        mtx->unlock(thread_id);
    }
}


int main()
{
    thread threads[8];
    Mutex mtx;
    int* a = new int[1];

    for (int i = 0; i < 10; i++)
    {   

        threads[i] = thread(do_stuff, a, i, &mtx);
    }

    for (int i = 0; i < 10; i++)
    {
        threads[i].join();
    }


    return 0;
}
