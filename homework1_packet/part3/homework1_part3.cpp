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


// 1.For array a, you must do this computation sequentially.
void compute_a(volatile int* a)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < K; j++)
        {
            a[i]++;
        }
    }
    
}

double function_a(volatile int* a)
{
    auto   function_a_start     = high_resolution_clock::now();
    compute_a(a);
    auto   function_a_stop      = high_resolution_clock::now();
    auto   function_a_duration  = duration_cast<nanoseconds>(function_a_stop - function_a_start);
    double function_a_seconds   = function_a_duration.count() / 1000000000.0;
    return function_a_seconds;
}



// For array b, you must do this computation in parallel by writing an SMPD style function.
// You must access elements in a round-robin style. That is, a thread with thread id of tid must
// compute the elements at index i where
//
//             i % NUM_THREADS = tid
//
// a thread must complete all increment operations on a location before moving on to the next location. 
// It must operate on its location in order.
void compute_b(volatile int* b, int tid, int num_threads)
{   
    for (int i = tid; i < SIZE; i+=num_threads)
    {
        for (int j = 0; j < K; j++)
        {
            b[i]++;
        }
    }

}


double function_b(volatile int* b)
{
    auto function_b_start = high_resolution_clock::now();

    thread thread_ar[THREADS];

    // create threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i] = thread(compute_b, b, i, THREADS);  
    }
    
    // join threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i].join();
    }

    auto   function_b_stop      = high_resolution_clock::now();
    auto   function_b_duration  = duration_cast<nanoseconds>(function_b_stop - function_b_start);
    double function_b_seconds   = function_b_duration.count() / 1000000000.0;  
    return function_b_seconds;
}


void compute_c(volatile int* c, int tid, int num_threads)
{
    for (int i = tid; i < SIZE; i+=num_threads)
    {
        for (int j = 0; j < K; j++)
        {
            c[i]++;
        }
    }
}


//For array c, you must do this computation in parallel by writing an SMPD style loop, 
// however you can partition data to the threads in any way you’d like.
// Think about how you can do this in a more eﬀicient way than what is done for array b.
double function_c(volatile int* c)
{
    auto function_c_start = high_resolution_clock::now();

    thread thread_ar[THREADS];

    // create threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i] = thread(compute_c, c, i, THREADS);  
    }
    
    // join threads
    for (int i = 0; i < THREADS; i++)
    {
        thread_ar[i].join();
    }

    auto   function_c_stop     = high_resolution_clock::now();
    auto   function_c_duration = duration_cast<nanoseconds>(function_c_stop - function_c_start);
    double function_c_seconds  = function_c_duration.count() / 1000000000.0;  
    return function_c_seconds;    
}



int main() 
{
    volatile int* a = new int[SIZE];
    volatile int* b = new int[SIZE];
    volatile int* c = new int[SIZE];
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

    double a_time = function_a(a);
    double b_time = function_b(b);
    double c_time = function_c(c);

    for (int i = 0; i < SIZE; i++)
    {
        assert(a[i] == b[i]);
        assert(a[i] == c[i]);
    }

    cout << endl;
    cout << "a time in seconds: " << a_time << endl;
    cout << "b time in seconds: " << b_time << endl;
    cout << "c time in seconds: " << c_time << endl;

    cout << endl;
    cout << "a compared to b: " << a_time/b_time << endl;
    cout << "a compared to c: " << a_time/c_time << endl;
    cout << "b compared to c: " << b_time/c_time << endl;
    cout << endl;

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}