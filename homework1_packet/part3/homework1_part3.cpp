#include <iostream>
#include <thread>
using namespace std;

#define THREADS 8
#define SIZE    1024
#define K       1048576


void function_a(volatile int* a)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < K; j++)
        {
            a[i]++;
        }
    }

    // for (int i = 0; i < SIZE; i++)
    // {
    //     printf("a[%d]: %d\n", i, a[i]);
    // }
    
}


void increment_b(volatile int* b, int &ret, int tid, int num_threads)
{
    // For array b, you must do this computation in parallel by writing an SMPD style function.
    // You must access elements in a round-robin style. That is, a thread with thread id of tid must
    // compute the elements at index i where
    //             i%NUM_THREADS = tid
    // a thread must complete all increment operations on a location before moving on to the next
    // location. It must operate on its location in order.
    
    for (int i = tid; i < SIZE; i+=num_threads)
    {
        // b[i % num_threads]++;
        
        for (int j = 0; j < K; j++)
        {
            b[i]++;
        }
    }


}


void print_array(volatile int* a)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("a[%d]: %d\n", i, a[i]);
    }
}



int main() 
{
    // int a[SIZE] = {0};
    // int b[SIZE] = {0};
    // int c[SIZE] = {0};

    int ret = 0;
    int* a = new int[SIZE];
    int* b = new int[SIZE];
    int* c = new int[SIZE];
    thread thread_ar[THREADS];

    function_a(a);

    // create threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i] = thread(increment_b, b, ref(ret), i, THREADS);  
    }
    
    // join threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i].join();
    }

    print_array(a);



    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}