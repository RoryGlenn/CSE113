
// a) Draw a labeled transition system (LTS) graph for this program.

// b) Is there a potential for non-termination due to starvation when executed under an unfair
// scheduler? if so, describe how this might happen.

    // Yes starvation is an issue, t1 can starve t0. Its possible that everytime that t0 runs,  x.load() could be equal to 1. However this is not guaranteed 

// c) Is the program guaranteed to terminate under the non-preemptive scheduler? i.e. once a
// thread has been scheduled to a core, it will continue fairly executing. Please justify your
// answer.

    // No, the program is not guaranteed to terminate under the non-preemptive scheduler. 
    // Because the schedular waits till the process is complete and then allocates resources to another process, this can block termination

// d) Is the program guaranteed to terminate under the energy-saving scheduler (also known as
// the HSA scheduler)? As a reminder, this scheduler might unfairly preempt threads, but
// guarantees fair execution to the thread with the lowest id. Justify your answer.

    // Because the energy-saving scheduler is preemptive, this will guarantee that our program will terminate.

// e) Consider swapping the thread programs, i.e. 
// thread 0 now spins while x is equal to 1; 
// thread 1 will write 1 followed by a write of 0 to x. 
// Do your answers to c and d hold? Explain your reasoning.

    // C and D will both hold because of preemptive scheduling




#include <atomic>
#include <iostream>
#include <thread>
#include <assert.h>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#define TEST_ITERATIONS (1024 * 256)
#define NUM_THREADS 2

atomic_int x(0);
atomic_int y(0);

int var0 = 0;
int var1 = 0;



// void t0_function()
// {
//     for (int i = 0; i < TEST_ITERATIONS; i++)
//     {
//         var0++;
//         x.store(1);
//         x.store(0);
//     }
// }


// void t1_function()
// {
//     for (int i = 0; i < TEST_ITERATIONS; i++)
//     {
//         while (x.load() == 1)
//         {
//             var1++;
//         }
//     }
// }



void t0_function()
{

    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        while (x.load() == 1)
        {
            var1++;
        }
    }    

}


void t1_function()
{
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        var0++;
        x.store(1);
        x.store(0);
    }
}



int main()
{

  // Launch NUM_THREADS threads and then join them
  thread thread_array[NUM_THREADS];

  thread_array[0] = thread(t0_function);
  thread_array[1] = thread(t1_function);

  thread_array[0].join();
  thread_array[1].join();

  cout << "var0: " << var0 << endl;
  cout << "var1: " << var1 << endl;
}

