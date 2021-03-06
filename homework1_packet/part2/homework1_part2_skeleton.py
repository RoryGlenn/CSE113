import os
import argparse

# Top of C++ file with includes and namespaces
top_source_string = """
#include <iostream>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

typedef double reduce_type;

"""



# docker pull reeselevine/cse113:latest
# docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest
# python3 homework1_part2_skeleton.py 4



# The reference loop simply adds together all elements in the array
def reference_reduction_source():

    # function header
    function = "void reference_reduction(reduce_type *b, int size) {"

    # loop header
    loop = "  for (int i = 1; i < size; i++) {"

    #simple reduction equation
    eq = "    b[0] += b[i];"

    # closing braces
    loop_close = "  }"
    function_close = "}"

    # joining together all parts
    return "\n".join([function, loop, eq, loop_close, function_close])


# Your homework will largely take place here. Create a loop that
# is semantically equivalent to the reference loop. That is, it computes
# a[0] = a[0] + a[1] + a[2] + a[3] + a[4] ... + a[size]
#
# where size is passed in by the main source string.
#
# You should unroll by a factor of "partitions". This is done logically
# by splitting a into N partitions (where N == partitions). You will compute
# N reductions, one computation for each partition per loop iteration.
#
# You will need a cleanup loop after the main loop to combine
# the values in each partition.
#
# You can assume the size and the number of partitions will be
# a power of 2, which should make the partitioning logic simpler.
#
# You can gain confidence in your solution by running the code
# with several power-of-2 unroll factors, e.g. 2,4,8,16. You
# should pass the assertion in the code.
#
# The reference slides for this part of the assignment are slides 81 -
# 92 of April 8 lecture. The example shows reduction for
# partitions=2. You need to generalize partitions to be any
# power-of-two. You can assume partition is less than size.
def homework_reduction_source(partitions):
    # header
    function = "\nvoid homework_reduction(reduce_type *a, int size) \n{"
    
    # g++ and clang are not smart enough to do this in their compiler

    # implement me!
    open_brace  = "{"
    close_brace = "}"

    function_body_str = f"""    int partitions = {partitions};
    int chunk_size = size/partitions;
    
    for (int i = 1; i < chunk_size; i++)
    {open_brace}
        """

    # however many elements are in each partition is the number of iterations we need minus 1 (CHUNK_SIZE-1)
    # how do we generate our chain length? (number of partitions)

    # elements   = 16
    # partitions = 4
    # chunk_size = elements/partitions (4)

    # a[0]
    # a[1]
    # a[2]
    # a[3]

    # a[4]
    # a[5]
    # a[6]
    # a[7]

    # a[8]
    # a[9]
    # a[10]
    # a[11]

    # a[12]
    # a[13]
    # a[14]
    # a[15]    

    # iteration 1:
        # a[0] += a[1]
        # a[4] += a[5]
        # a[8] += a[9]
        # a[12] += a[13]

    # iteration 2:
        # a[0] += a[2]
        # a[4] += a[6]
        # a[8] += a[10]
        # a[12] += a[14]   

    # iteration 3:
        # a[0] += a[3]
        # a[4] += a[7]
        # a[8] += a[11]
        # a[12] += a[15]   

    # clean up loop (final loop):



    for i in range(0, partitions):
        function_body_str += \
        f"""a[chunk_size*{i}] += a[chunk_size*{i}+i];
        """

    function_body_str += close_brace + "\n\n        "

    for i in range(1, partitions):
        function_body_str += \
        f"""a[0] += a[chunk_size*{i}];
        """

    

    function_body = function_body_str

    function_close = "    }\n"

    
    return "\n".join([function, function_body,function_close])

# String for the main function, including timings and
# reference checks.
main_source_string = """
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
"""

# Create the program source code
def pp_program(partitions):

    # Your function is called here
    homework_string = homework_reduction_source(partitions)

    # View your homework source string here for debugging
    return "\n".join([top_source_string, reference_reduction_source(), homework_string, main_source_string])

# Write a string to a file (helper function)
def write_str_to_file(st, fname):
    f = open(fname, 'w')
    f.write(st)
    f.close()

# Compile the program. Don't change the options here for the official
# assignment report. Feel free to change them for your own curiosity.
# Some notes:
#
# I am using a recent version of C++ to use the chrono library.
#
# I am disabling the compiler's loop unrolling so we can ensure the
# reference loop and the homework loops are not unrolled "behind our backs"
#
# I am using the highest optimization level (-O3) to illustrate that
# the compiler is not even brave enough to perform this optimization!
def compile_program():
    cmd = "clang++ -std=c++17 -fno-unroll-loops -O3 -o homework homework.cpp"
    print("running: " + cmd)
    assert(os.system(cmd) == 0)

# Run the program
def run_program():
    cmd = "./homework"
    print("running: " + cmd)
    print("")
    assert(os.system(cmd) == 0)

# This is the top level program function. Generate the C++ program,
# compile it, and run it.
def generate_and_run(partitions):
    print("")
    print("----------")
    print("generating and running for:")
    print("partitions = " + str(partitions))
    print("-----")
    print("")

    # get the C++ source
    program_str = pp_program(partitions)

    # write it to a file (homework.cpp)
    write_str_to_file(program_str, "homework.cpp")

    # compile the program
    compile_program()

    # run the program
    run_program()

# gets one command line arg unroll factor (UF)                                               
def main():
    parser = argparse.ArgumentParser(description='Part 2 of Homework 1: exploiting ILP by unrolling reduction loop iterations.')
    parser.add_argument('unroll_factor', metavar='UF', type=int, help='how many loop iterations to unroll')
    args = parser.parse_args()
    UF = args.unroll_factor
    generate_and_run(UF)

if __name__ == "__main__":
    main()
