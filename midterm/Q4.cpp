#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
using namespace std;

 
class Mutex 
{

public:
 
    void lock()
    {
        // 0 = lock is free
		// 1 = lock is taken

        bit e = 0;
        bit acquired = false;

        while(!acquired)
        {
            while (atomic_fetch_and(b, 1) == 1)
            {
                // spin
            }

            e = 0;
            acquired = atomic_fetch_or(b, 1);
    }
 
    void unlock()
    {
        atomic_fetch_and(b, 0);
    }
 
 
private:
	atomic_bit* b;

};

