
#pragma omp target device(fpga) \
            implements(block_matmul) \
            copy_in(A,B) copy_inout(C)
extern void matmul_fpga(float A[BS][BS],
                        float B[BS][BS],
                        float C[BS][BS]);
...

int i, j, k;
for (i = 0; i < DIM_SIZE; i += BS)
  for (j = 0; j < DIM_SIZE; j += BS)
    for (k = 0; k < DIM_SIZE; k += BS) {
pragma omp task label(block_matmul) \
          input(A[i:i+BS-1][k:k+BS-1],  \
            B[k:k+BS-1][j:j+BS-1]) \
          inout(C[i:i+BS-1][j:j+BS-1])
        {
          for (i_b = i; i_b < i+BS; ib++)
            for(j_b = j; j_b < j+BS; jb++)
              for(k_b = k; k_b < k+BS; kb++)
                C[i_b][j_b] += A[i_b][k_b] * B[k_b][j_b];
         }
         }
 ...
