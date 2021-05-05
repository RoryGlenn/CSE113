#include <atomic>
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;


void increment(int* array, int thread_id, mutex* m)
{
    for (int i = 0; i < 100; i++)
    {
        array[thread_id]++;
        printf("thread_id: %d, array[%d] = %d\n", thread_id, i, array[thread_id]);
    }
}


int main()
{
    mutex m;
    int*  a = new int[1];

    a[0] = 0;
    a[0] = 0;

    thread t1 = thread(increment, a, 0, &m);
    thread t2 = thread(increment, a, 1, &m);

    t1.join();
    t2.join();
    
    return 0;
}