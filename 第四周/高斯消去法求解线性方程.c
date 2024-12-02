/**
 * @Descripttion: 使用高斯消去法求解高阶稀疏矩阵
 * @filename: 高斯消去法求解高阶稀疏矩阵.c
 * @Author: 王春博
 * @Date: 2024.10.15
 * @Version: V1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000     // 矩阵阶数
#define SPARSITY 0.05  // 稀疏度，表示非零元素占总元素的比例

// 函数：生成稀疏上三角矩阵
void generate_sparse_upper_triangular_matrix(double **A, double *b) {
    srand(time(NULL));  // 初始化随机数种子

    // 初始化稀疏矩阵
    for (int i = 0; i < N; i++) {
        b[i] = rand() % 10 + 1;  // 随机生成b向量

        for (int j = 0; j < N; j++) {
            if (j < i) {
                A[i][j] = 0.0;  // 确保是上三角矩阵，主对角线以下的元素为0
            } else if (i == j) {
                A[i][j] = rand() % 10 + 5;  // 确保对角线上的元素较大，且不为零
            } else if ((double) rand() / RAND_MAX < SPARSITY) {
                A[i][j] = rand() % 5 + 1;  // 随机生成上三角区域的稀疏元素
            } else {
                A[i][j] = 0.0;  // 稀疏矩阵的其他位置为0
            }
        }
    }
}

// 高斯消去法
void gaussian_elimination(double **A, double *b, double *x) {
    // 消元阶段
    for (int i = 0; i < N; i++) {
        // 如果主元为 0，交换行
        if (A[i][i] == 0) {
            for (int k = i + 1; k < N; k++) {
                if (A[k][i] != 0) {
                    for (int j = 0; j < N; j++) {
                        double temp = A[i][j];
                        A[i][j] = A[k][j];
                        A[k][j] = temp;
                    }
                    double temp_b = b[i];
                    b[i] = b[k];
                    b[k] = temp_b;
                    break;
                }
            }
        }

        for (int j = i + 1; j < N; j++) {
            double rate = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= rate * A[i][k];
            }
            b[j] -= rate * b[i];
        }
    }

    // 回代阶段
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

// 函数：评估准确性
double evaluate_accuracy(double *x, double *b, double **A) {
    double error_sum = 0.0;
    for (int i = 0; i < N; i++) {
        double calculated_b = 0.0;
        for (int j = 0; j < N; j++) {
            calculated_b += A[i][j] * x[j];  // 计算 Ax_i
        }
        error_sum += fabs(b[i] - calculated_b);  // 计算 b - Ax 的绝对误差和
    }
    return error_sum;
}

int main() {
    double **A = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    double *b = (double *)malloc(N * sizeof(double));
    double *x = (double *)malloc(N * sizeof(double));  // 解向量

    if (A == NULL || b == NULL || x == NULL) {
        printf("内存分配失败\n");
        return -1;
    }

    // 调用生成稀疏上三角矩阵的函数
    generate_sparse_upper_triangular_matrix(A, b);

    // 开始计时
    clock_t start_time = clock();

    // 使用高斯消去法求解
    gaussian_elimination(A, b, x);

    // 结束计时
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("高斯消去法运行时间: %f 秒\n", elapsed_time);

    // 评估解的准确性
    double accuracy = evaluate_accuracy(x, b, A);
    printf("解的准确性误差总和: %f\n", accuracy);

    for (int i = 0; i < N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    return 0;
}
