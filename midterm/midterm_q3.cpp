// docker pull reeselevine/cse113:latest
// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest
// make

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

void print_array(int* array, string name)
{
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++)
    {
        cout << name << "[";
        printf("%d]: %d\n", i, array[i]);
    }

    cout << endl;
}


void foo(int *a, int *b, int *c, mutex *m0, mutex *m1)
{
    if (b[0] > 0)
    {
        m0->lock();
        a[0] = b[0];
        m0->unlock();
    }
    else if (b[0] > -16)
    {
        m0->lock();
        a[0] = 128;
        m0->unlock();
        return;
    }
    else
    {
        m0->lock();
        a[0] = 256;
        m0->unlock();
    }

    m0->lock();
    a[0]++;
    m0->unlock();
}


// because we pass (c, c, c) in, this function is useless
void bar(int *a, int *b, int *c, mutex *m0, mutex *m1) 
{
    m1->lock();
    c[0] = a[0];
    m1->unlock(); 
}


void baz(int *a, int *b, int *c, mutex *m0, mutex *m1)
{
    m0->lock();
    a[0] = b[0];
    m0->unlock();
} 
    

void qux(int *a, int *b, int *c, mutex *m0, mutex *m1) 
{ 
    m1->lock();
    c[0] = b[0] + c[0];
    m1->unlock();
}




int main()
{
    int *a = new int[1];
    int *b = new int[1];
    int *c = new int[1];

    mutex m0;
    mutex m1;

    // a and c are changed but b is never changed.

    // use m0 to lock a, use m1 to lock c?

    cout << "before" << endl;
    print_array(a, "a");
    print_array(b, "b");
    print_array(c, "c");

    thread tfoo = thread(foo, a, b, c, &m0, &m1);
    thread tbar = thread(bar, c, c, c, &m0, &m1);
    thread tbaz = thread(baz, a, b, c, &m1, &m0);
    thread tqux = thread(qux, a, b, c, &m0, &m1); 
    
    // assume we join and cleanup memory after this
    tfoo.join();
    tbar.join();
    tbaz.join();
    tqux.join();

    cout << "before" << endl;
    print_array(a, "a");
    print_array(b, "b");
    print_array(c, "c");
    
    // after using threads I get the same result as not using threads at all. Whats the point?

    return 0;
}