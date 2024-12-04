#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024 // Matrix size
#define BLOCK_SIZE 8 // Block size for cache blocking

void initialize_matrices(float A[N][N], float B[N][N], float C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (float)(rand() % 100);
            B[i][j] = (float)(rand() % 100);
            C[i][j] = 0.0;
        }
    }
}

void initialize_C(float C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
        }
    }
}

void naive_matrix_multiply(float A[N][N], float B[N][N], float C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
	    float sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            } 
            C[i][j] += sum;
        }
    }
}

void cache_blocked_matrix_multiply(float A[N][N], float B[N][N], float C[N][N]) {
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
                for (int i = ii; i < ii + BLOCK_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < N; j++) {
                        float sum = 0.0;
                        for (int k = kk; k < kk + BLOCK_SIZE && k < N; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}

int main() {
    static float A[N][N], B[N][N], C[N][N];

    initialize_matrices(A, B, C);
    naive_matrix_multiply(A, B, C);
    printf("%f\n", C[N-1][N-1]);
    initialize_C(C);
    cache_blocked_matrix_multiply(A, B, C);
    printf("%f\n", C[N-1][N-1]);

    printf("Matrix multiplication complete.\n");
    return 0;
}

