
#include <iostream>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

typedef double reduce_type;


void reference_reduction(reduce_type *b, int size) {
  for (int i = 1; i < size; i++) {
    b[0] += b[i];
  }
}

void homework_reduction(reduce_type *a, int size) 
{
    int partitions = 8;
    for (int i = 1; i < size/partitions; i++)
    {
        a[0] += a[i];
        a[size/partitions] += a[(size/partitions)+i];
    }

    a[0] = a[0] + a[size/partitions];
}

#define SIZE (1024*1024*512)


int main() {
  reduce_type *a;
  a = (reduce_type *) malloc(SIZE * sizeof(reduce_type));

  reduce_type *b;
  b = (reduce_type *) malloc(SIZE * sizeof(reduce_type));

  for (int i = 0; i < SIZE; i++) {
    a[i] = 1;
    b[i] = 1;
  }

  auto new_start = high_resolution_clock::now();
  homework_reduction(a,SIZE);
  auto new_stop = high_resolution_clock::now();
  auto new_duration = duration_cast<nanoseconds>(new_stop - new_start);
  double new_seconds = new_duration.count()/1000000000.0;

  auto ref_start = high_resolution_clock::now();
  reference_reduction(b,SIZE);
  auto ref_stop = high_resolution_clock::now();
  auto ref_duration = duration_cast<nanoseconds>(ref_stop - ref_start);
  double ref_seconds = ref_duration.count()/1000000000.0;

  cout << "new loop time: " << new_seconds << endl; 
  cout << "reference loop time: " << ref_seconds << endl; 
  cout << "speedup: " << ref_seconds / new_seconds << endl << endl;

  return 0;
}