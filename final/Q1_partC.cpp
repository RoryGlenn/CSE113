// declaration of matrix variable sizes

for (int i = 0; i < d0; i++)
{
    for (int j = 0; j < d2; j++)
    {
        #pragma omp parallel for num_threads(4) schedule(static, 4)
        for (int k = 0; k < d1; k++) 
        {
            output[i][j] += A[i][k] * B[k][j];
        }
    }
}