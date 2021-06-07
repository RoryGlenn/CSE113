#include <atomic>
using namespace std;

// this should be the same as SCDekkers with the change that every
// relaxed access should be memory_order_relaxed

// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest


class dekkers_mutex
{
public:
  dekkers_mutex()
  {
    // implement me!
    int num_threads = 2;
    turn.store(0, memory_order_relaxed);
    wants_to_enter = new atomic_bool[num_threads];

    for (int i = 0; i < num_threads; i++)
      wants_to_enter[i].store(false, memory_order_relaxed);

  }


  void lock(int tid)
  {
    // implement me!
    wants_to_enter[tid].store(true, memory_order_relaxed); 
    int wte = 0;
    if (tid == 0) { wte = 1; }


    while (wants_to_enter[wte].load(memory_order_relaxed)) 
    {
      if (turn.load(memory_order_relaxed) != tid)
      {
        wants_to_enter[tid].store(false, memory_order_relaxed);

        while (turn.load(memory_order_relaxed) != tid)
        {
          // spin...
        }

        wants_to_enter[tid].store(true, memory_order_relaxed);
      }
    }

  }

  void unlock(int tid)
  {
    // implement me!
    int wte = 0;
    if (tid == 0) { wte = 1; }
    
    turn.store(wte, memory_order_relaxed);
    wants_to_enter[tid].store(false, memory_order_relaxed);

  }

private:
  // Give me some private variables
  atomic_bool* wants_to_enter;
  atomic_int   turn;

};


// Dekker’s Algorithm

// void main()
// {
//   variables
//       wants_to_enter : array of 2 booleans
//       turn : integer

//   wants_to_enter[0] ← false
//   wants_to_enter[1] ← false
//   turn ← 0   // or 1  
// }

// void p0()
// {
//    wants_to_enter[0] ← true
//    while wants_to_enter[1] {
//       if turn ≠ 0 {
//          wants_to_enter[0] ← false
//          while turn ≠ 0 {
//            // busy wait
//          }
//          wants_to_enter[0] ← true
//       }
//    }

//    // critical section
//    ...
//    turn ← 1
//    wants_to_enter[0] ← false
//    // remainder section
// }



// void p1()
// {
//   wants_to_enter[1] ← true
//   while wants_to_enter[0] {
//     if turn ≠ 1 {
//         wants_to_enter[1] ← false
//         while turn ≠ 1 {
//           // busy wait
//         }
//         wants_to_enter[1] ← true
//     }
//   }

//   // critical section
//   ...
//   turn ← 0
//   wants_to_enter[1] ← false
//   // remainder section
// }