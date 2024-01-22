/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	if(M == 32)
	{
		int i, j, i1, j1, tmp[8];
		for (i = 0; i < N; i += 8)
			for (j = 0; j < M; j += 8)
				if(i == j)
				{
					for(i1 = i ; i1 < i + 8 ; i1++)
					{
						tmp[0] = A[i1][j];
						tmp[1] = A[i1][j+1];
						tmp[2] = A[i1][j+2];
						tmp[3] = A[i1][j+3];
						tmp[4] = A[i1][j+4];
						tmp[5] = A[i1][j+5];
						tmp[6] = A[i1][j+6];
						tmp[7] = A[i1][j+7];
	
						for(j1 = j ; j1 < j + 8 ; j1++)  
						{
							if(j1 < i1)
							{
								B[i1][j1] = B[j1][i1];
								B[j1][i1] = tmp[j1-j];
							}
							else
								B[i1][j1] = tmp[j1-j];

						}
					}
			}

			else
			{
				for(i1 = i ; i1 < i + 8 ; i1++)
					for(j1 = j ; j1 < j + 8 ; j1++)
						B[j1][i1] = A[i1][j1];
			}
	}

	if(M == 64)
	{
		int i, j, k, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
		for(i = 0 ; i < 64 ; i += 8)
			for(j = 0 ; j < 64 ; j += 8)
			{
				for(k = 0 ; k < 4 ; k++)
				{
					tmp0 = A[i+k][j];
					tmp1 = A[i+k][j+1];
					tmp2 = A[i+k][j+2];
					tmp3 = A[i+k][j+3];
					tmp4 = A[i+k][j+4];
					tmp5 = A[i+k][j+5];
					tmp6 = A[i+k][j+6];
					tmp7 = A[i+k][j+7];
					
					B[j][i+k] = tmp0;	
					B[j+1][i+k] = tmp1;
					B[j+2][i+k] = tmp2;
					B[j+3][i+k] = tmp3;

					B[j][i+k+4] = tmp4;
					B[j+1][i+k+4] = tmp5;
					B[j+2][i+k+4] = tmp6;
					B[j+3][i+k+4] = tmp7;
				}

				for(k = 0 ; k < 4 ; k++)
				{
					tmp0 = B[j+k][i+4];
					tmp1 = B[j+k][i+5];
					tmp2 = B[j+k][i+6];
					tmp3 = B[j+k][i+7];
					
					tmp4 = A[i+4][j+k];
					tmp5 = A[i+5][j+k];
					tmp6 = A[i+6][j+k];
					tmp7 = A[i+7][j+k];
					
					B[j+k][i+4] = tmp4;
					B[j+k][i+5] = tmp5;
					B[j+k][i+6] = tmp6;
					B[j+k][i+7] = tmp7;
					
					B[j+k+4][i] = tmp0;
					B[j+k+4][i+1] = tmp1;
					B[j+k+4][i+2] = tmp2;
					B[j+k+4][i+3] = tmp3;
				}

				for(k = 0 ; k < 4 ; k++)
				{
					tmp0 = A[i+k+4][j+4];
					tmp1 = A[i+k+4][j+5];
					tmp2 = A[i+k+4][j+6];
					tmp3 = A[i+k+4][j+7];

					B[j+4][i+k+4] = tmp0;
					B[j+5][i+k+4] = tmp1;
					B[j+6][i+k+4] = tmp2;
					B[j+7][i+k+4] = tmp3;
				}
			}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

