float A[DIM_SIZE] [DIM_SIZE];
float B[DIM_SIZE] [DIM_SIZE];
float C[DIM_SIZE] [DIM_SIZE];

#pragma omp target device(fpga) \
    implements (block_matmul) \
    copy_in(A,B) copy_inout(C)
extern void matmul_fpga(float A[BS][BS],
        float B[BS][BS], float C[BS][BS]);

...

int i, j ,k
for (i = 0; i < DIM_SIZE; i++) {
    for (j = 0; j < DIM_SIZE; j++) {
        for (k = 0; k < DIM_SIZE; k++) {
            #pragma omp block nest(3) factor(BS,BS,BS) \
            #pragma omp task label(block_matmul)  \
                              input(A[i][k],B[k][j])  \
                              inout(C[i][j])
            C[i][j] += A[i][k] * B[k][j];
         }
     }
}
...
