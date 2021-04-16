#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

#define THREADS 8
#define SIZE    1024
#define K       1048576


// docker pull reeselevine/cse113:latest
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest
// make
// 



void function_a(volatile int* a)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < K; j++)
        {
            a[i]++;
        }
    }
    
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


void function_c(volatile int* c)
{

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


    // initialize all array indices to 0
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }





    // You should time each function. 
    // You can use the chrono library similar to the C++ timing codein part 1. 
    // Print out the speedups of: 
        // • the computation of a related to b
        // • the computation of a related to c
        // • the computation of b related to c

    ///////////////////////////////////////////////


    // a compared to b

    auto   function_a_start     = high_resolution_clock::now();
    function_a(a);
    auto   function_a_stop      = high_resolution_clock::now();
    auto   function_a_duration  = duration_cast<nanoseconds>(function_a_stop - function_a_start);
    double function_a_seconds   = function_a_duration.count() / 1000000000.0;


    auto   function_b_start     = high_resolution_clock::now();
    
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

    auto   function_b_stop      = high_resolution_clock::now();
    auto   function_b_duration  = duration_cast<nanoseconds>(function_b_stop - function_b_start);
    double function_b_seconds   = function_a_duration.count() / 1000000000.0;




    ///////////////////////////////////////////////

    // a related to c

    // // create threads
    // for (int i = 0; i < THREADS; i++)
    // {
    //     thread_ar[i] = thread(increment_b, b, ref(ret), i, THREADS);  
    // }
    
    // // join threads
    // for (int i = 0; i < THREADS; i++)
    // {
    //     thread_ar[i].join();
    // }    





    ///////////////////////////////////////////////

    // b related to c




    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}