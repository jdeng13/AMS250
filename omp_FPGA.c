/* Example 1, targeted code is a function */
#pragma omp target device(fpga) implements(matmul) copy_in( A[N], B[N] ) copy_inout( C[N] )
void matmul_fpga(int *A, int *B, int *C)
{
  // Code that will run on the FPGA
}

#pragma omp task input( A[N], B[N] ) inout( C[N] )
void matmul(int *A, int *B, int *C)
{
  // Code that can run on the HOST but won't be used if an accelerator is availabe
}

main()
{
  int i,j,k;
  int A[N], B[N], C[N];
  // ...
  // The next call will be untouched if there's no accelerator available
  // If we have a supported target which implements 'matmul' we will replace this call with the
  // calls to the accelerator (Daniel C's code)
  matmul(A[i],B[i],C[c]);
}


/* Example 2, targeted code mixed in the jungle */

#pragma omp target device(fpga) implements(matmul) copy_in( A[N], B[N] ) copy_inout( C[N] )
void matmul_fpga(int *A, int *B, int *C)
{
  // Code that will run on the FPGA
}

main()
{
  int i,j,k;
  int A[N], B[N], C[N];

  for (i = 0; i < N; i++)
  {
    for ...
      ...
        #pragma omp task label(block_matmul) input(A[i], B[k]) inout(C[j])
        C[j] += A[i] * B[k];
  }

}
