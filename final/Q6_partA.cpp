// https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
// https://www.youtube.com/watch?v=2zX0Q0UrmII


// a) Consider the blur function you worked on in Homework 4 (note that this blur is not repeated,
// it is only done once). The C++ code is given below. Your job is to write a CUDA program to do
// this function on the GPU, and in parallel. Compute your GPU blur using 1 block with 16 warps.


__global__ void blur(double *input, double *output, int size)
{
    for (int i = threadIdx.x; i < size; i+=blockDim.x)
    {
        output[i] = (input[i - 1] + input[i] + input[i + 1]) / input[i];
    }
}



int main()
{
    double* input;
    double* output;

    cudaMalloc(&input, SIZE*sizeof(double));
    cudaMalloc(&output, SIZE*sizeof(double));

    // input initialization (not shown)
    blur<<<1, 16>>>(input, output, SIZE);

    // check results in output (not shown)
    for (int i = 0; i < SIZE; i++)
    {
        printf("output[%d]: %d\n", i, output[i]);
    }


    return 0;
}