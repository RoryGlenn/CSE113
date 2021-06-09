// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#include <thread>
#include <iostream>
#include "Q3.h"
using namespace std;

#define SIZE 1024

void func_add(AddOnlySet* aos)
{
    for (int i = 0; i < SIZE; i++)
    {
        aos->add(i);
    }
}


int main()
{
    int num_threads = 8;

    AddOnlySet* aos = new AddOnlySet(SIZE);
    
    thread *thread_array = new thread[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        thread_array[i] = thread(func_add, aos);
    }

    for (int i = 0; i < num_threads; i++)
    {
        thread_array[i].join();
    }

    
    if (aos->contains(2))
    {
        cout << "yup " << endl;
    }
    else
    {
        cout << "nope " << endl;
    }


    return 0;
}