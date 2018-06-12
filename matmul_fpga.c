float A[DIM_SIZE] [DIM_SIZE];
float B[DIM_SIZE] [DIM_SIZE];
float C[DIM_SIZE] [DIM_SIZE];

#pragma omp target device(fpga) \
    implements (block_matmul) \
    copy_in(A,B) copy_inout(C)                 // specification of the direction of the arguments
extern void matmul_fpga(float A[BS][BS],       // task offloading to fpga device
        float B[BS][BS], float C[BS][BS]);

...

int i, j ,k
for (i = 0; i < DIM_SIZE; i++) {
    for (j = 0; j < DIM_SIZE; j++) {
        for (k = 0; k < DIM_SIZE; k++) {
            #pragma omp block nest(3) factor(BS,BS,BS) \     //  blocking and packing/unpacking of data 
            #pragma omp task label(block_matmul)  \          //  specification of the direction of the arguments
                              input(A[i][k],B[k][j])  \      //  specification of the direction of the arguments
                              inout(C[i][j])
            C[i][j] += A[i][k] * B[k][j];
         }
     }
}
...
