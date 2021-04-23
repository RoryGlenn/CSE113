
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
    int partitions = 64;
    int chunk_size = size/partitions;
    
    for (int i = 1; i < chunk_size; i++)
    {
        a[chunk_size*0] += a[chunk_size*0+i];
        a[chunk_size*1] += a[chunk_size*1+i];
        a[chunk_size*2] += a[chunk_size*2+i];
        a[chunk_size*3] += a[chunk_size*3+i];
        a[chunk_size*4] += a[chunk_size*4+i];
        a[chunk_size*5] += a[chunk_size*5+i];
        a[chunk_size*6] += a[chunk_size*6+i];
        a[chunk_size*7] += a[chunk_size*7+i];
        a[chunk_size*8] += a[chunk_size*8+i];
        a[chunk_size*9] += a[chunk_size*9+i];
        a[chunk_size*10] += a[chunk_size*10+i];
        a[chunk_size*11] += a[chunk_size*11+i];
        a[chunk_size*12] += a[chunk_size*12+i];
        a[chunk_size*13] += a[chunk_size*13+i];
        a[chunk_size*14] += a[chunk_size*14+i];
        a[chunk_size*15] += a[chunk_size*15+i];
        a[chunk_size*16] += a[chunk_size*16+i];
        a[chunk_size*17] += a[chunk_size*17+i];
        a[chunk_size*18] += a[chunk_size*18+i];
        a[chunk_size*19] += a[chunk_size*19+i];
        a[chunk_size*20] += a[chunk_size*20+i];
        a[chunk_size*21] += a[chunk_size*21+i];
        a[chunk_size*22] += a[chunk_size*22+i];
        a[chunk_size*23] += a[chunk_size*23+i];
        a[chunk_size*24] += a[chunk_size*24+i];
        a[chunk_size*25] += a[chunk_size*25+i];
        a[chunk_size*26] += a[chunk_size*26+i];
        a[chunk_size*27] += a[chunk_size*27+i];
        a[chunk_size*28] += a[chunk_size*28+i];
        a[chunk_size*29] += a[chunk_size*29+i];
        a[chunk_size*30] += a[chunk_size*30+i];
        a[chunk_size*31] += a[chunk_size*31+i];
        a[chunk_size*32] += a[chunk_size*32+i];
        a[chunk_size*33] += a[chunk_size*33+i];
        a[chunk_size*34] += a[chunk_size*34+i];
        a[chunk_size*35] += a[chunk_size*35+i];
        a[chunk_size*36] += a[chunk_size*36+i];
        a[chunk_size*37] += a[chunk_size*37+i];
        a[chunk_size*38] += a[chunk_size*38+i];
        a[chunk_size*39] += a[chunk_size*39+i];
        a[chunk_size*40] += a[chunk_size*40+i];
        a[chunk_size*41] += a[chunk_size*41+i];
        a[chunk_size*42] += a[chunk_size*42+i];
        a[chunk_size*43] += a[chunk_size*43+i];
        a[chunk_size*44] += a[chunk_size*44+i];
        a[chunk_size*45] += a[chunk_size*45+i];
        a[chunk_size*46] += a[chunk_size*46+i];
        a[chunk_size*47] += a[chunk_size*47+i];
        a[chunk_size*48] += a[chunk_size*48+i];
        a[chunk_size*49] += a[chunk_size*49+i];
        a[chunk_size*50] += a[chunk_size*50+i];
        a[chunk_size*51] += a[chunk_size*51+i];
        a[chunk_size*52] += a[chunk_size*52+i];
        a[chunk_size*53] += a[chunk_size*53+i];
        a[chunk_size*54] += a[chunk_size*54+i];
        a[chunk_size*55] += a[chunk_size*55+i];
        a[chunk_size*56] += a[chunk_size*56+i];
        a[chunk_size*57] += a[chunk_size*57+i];
        a[chunk_size*58] += a[chunk_size*58+i];
        a[chunk_size*59] += a[chunk_size*59+i];
        a[chunk_size*60] += a[chunk_size*60+i];
        a[chunk_size*61] += a[chunk_size*61+i];
        a[chunk_size*62] += a[chunk_size*62+i];
        a[chunk_size*63] += a[chunk_size*63+i];
        }

        a[0] += a[chunk_size*1];
        a[0] += a[chunk_size*2];
        a[0] += a[chunk_size*3];
        a[0] += a[chunk_size*4];
        a[0] += a[chunk_size*5];
        a[0] += a[chunk_size*6];
        a[0] += a[chunk_size*7];
        a[0] += a[chunk_size*8];
        a[0] += a[chunk_size*9];
        a[0] += a[chunk_size*10];
        a[0] += a[chunk_size*11];
        a[0] += a[chunk_size*12];
        a[0] += a[chunk_size*13];
        a[0] += a[chunk_size*14];
        a[0] += a[chunk_size*15];
        a[0] += a[chunk_size*16];
        a[0] += a[chunk_size*17];
        a[0] += a[chunk_size*18];
        a[0] += a[chunk_size*19];
        a[0] += a[chunk_size*20];
        a[0] += a[chunk_size*21];
        a[0] += a[chunk_size*22];
        a[0] += a[chunk_size*23];
        a[0] += a[chunk_size*24];
        a[0] += a[chunk_size*25];
        a[0] += a[chunk_size*26];
        a[0] += a[chunk_size*27];
        a[0] += a[chunk_size*28];
        a[0] += a[chunk_size*29];
        a[0] += a[chunk_size*30];
        a[0] += a[chunk_size*31];
        a[0] += a[chunk_size*32];
        a[0] += a[chunk_size*33];
        a[0] += a[chunk_size*34];
        a[0] += a[chunk_size*35];
        a[0] += a[chunk_size*36];
        a[0] += a[chunk_size*37];
        a[0] += a[chunk_size*38];
        a[0] += a[chunk_size*39];
        a[0] += a[chunk_size*40];
        a[0] += a[chunk_size*41];
        a[0] += a[chunk_size*42];
        a[0] += a[chunk_size*43];
        a[0] += a[chunk_size*44];
        a[0] += a[chunk_size*45];
        a[0] += a[chunk_size*46];
        a[0] += a[chunk_size*47];
        a[0] += a[chunk_size*48];
        a[0] += a[chunk_size*49];
        a[0] += a[chunk_size*50];
        a[0] += a[chunk_size*51];
        a[0] += a[chunk_size*52];
        a[0] += a[chunk_size*53];
        a[0] += a[chunk_size*54];
        a[0] += a[chunk_size*55];
        a[0] += a[chunk_size*56];
        a[0] += a[chunk_size*57];
        a[0] += a[chunk_size*58];
        a[0] += a[chunk_size*59];
        a[0] += a[chunk_size*60];
        a[0] += a[chunk_size*61];
        a[0] += a[chunk_size*62];
        a[0] += a[chunk_size*63];
        
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

  assert(a[0] == b[0]);

  cout << "new loop time: " << new_seconds << endl; 
  cout << "reference loop time: " << ref_seconds << endl; 
  cout << "speedup: " << ref_seconds / new_seconds << endl << endl;

  return 0;
}
