// for a,b,c: given a litmus test, determine if the specified outcome is possible. 
// Justify your answers with an execution trace (i.e. Lego stack). 
// Additionally, if the outcome is allowed, describe if you can place a FENCE in the program to disallow the behavior

// 4a)

// At the end of the execution can:
// t0 == 1 and t1 == 1?

    // The outcome is allowed by breaking program order. We make a new rule to allow loads to follow stores. Thus the execution trace will be:
    // store(y,1)
    // t1 = load(y)
    // store(x,1)
    // t0 = load(x)

    // To disallow the behavior we would place a fence in these locations:
    // FENCE
    // store(y,1)
    // t1 = load(y)
    // FENCE
    // store(x,1)
    // t0 = load(x)


    

#include <atomic>
#include <iostream>
#include <thread>
#include <assert.h>
using namespace std;

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#define TEST_ITERATIONS (1024 * 256)

atomic_int x(0);
atomic_int y(0);

int var0 = 0;
int var1 = 0;


void t0_function()
{
    var0 = x.load();
    y.store(1);
}

void t1_function()
{
    var1 = y.load();
    x.store(1);
}

int main()
{
    int output0 = 0;
    int output1 = 0;
    int output2 = 0;
    int output3 = 0; // weak behavior
    // You should pay special attention to whether or not you can observe the weak behavior

    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        x.store(0);
        y.store(0);

        // Run a test iteration
        thread t0 = thread(t0_function);
        thread t1 = thread(t1_function);

        t0.join();
        t1.join();

        assert(var0 == 1 && var1 == 1);
    }

    // Complete the print out using your output instantiations
    cout << "histogram of different observations:" << endl;
    cout << "output0:  " << output0 << endl;
    cout << "output1:  " << output1 << endl;
    cout << "output2:  " << output2 << endl;
    cout << "output3:  " << output3 << endl
         << endl;
    cout << "relaxed behavior frequency: " << float(output3) / float(TEST_ITERATIONS) << endl;

    return 0;
}
