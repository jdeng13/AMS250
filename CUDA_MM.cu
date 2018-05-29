// Matrix multiplication kernel
__global__ void MatMulKernel(Matrix A, Matrix B, Matrix C)
{
// Block row and column
int blockRow = blockIdx.y;
int blockCol = blockIdx.x;
// Each thread block computes one sub-matrix of C
Matrix Csub = GetSubMatrix(C, blockRow, blockCol);
// Each thread computes one elements of Csub
float Cvalue = 0;
// Thread row and column with Csub
int row = threadIdx.y;
int col = threadIdx.y;
