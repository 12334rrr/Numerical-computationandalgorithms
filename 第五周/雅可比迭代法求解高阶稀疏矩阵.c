/**
 * @Descripttion: 使用雅克比迭代法求解高阶稀疏矩阵
 * @filename: 雅可比迭代法求解高阶稀疏矩阵.c
 * @Author: 王春博
 * @Date: 2024.10.15
 * @Version: V1.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000     // 矩阵阶数
#define SPARSITY 0.05  // 稀疏度，表示非零元素占总元素的比例
#define TOL 1e-6   // 误差容限
#define MAX_ITER 10000  // 最大迭代次数

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

// 雅克比迭代求解
void jacobi(double **A, double *b, double *x) {
    double *x_new = (double *)malloc(N * sizeof(double));
    if (x_new == NULL) {
        printf("内存分配失败\n");
        return;
    }
    int iter = 0;
    double error;

    // 初始化x_new为0
    for (int i = 0; i < N; i++) {
        x_new[i] = 0.0;
    }

    do {
        error = 0.0;
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
            error += fabs(x_new[i] - x[i]);
        }

        // 更新x
        for (int i = 0; i < N; i++) {
            x[i] = x_new[i];
        }

        iter++;
    } while (error > TOL && iter < MAX_ITER);

    if (iter >= MAX_ITER) {
        printf("雅克比迭代未能在最大迭代次数内收敛\n");
    } else {
        printf("雅克比迭代收敛于 %d 次迭代\n", iter);
    }

    free(x_new);
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
    double *x = (double *)malloc(N * sizeof(double));  // 初始解向量为0

    if (A == NULL || b == NULL || x == NULL) {
        printf("内存分配失败\n");
        return -1;
    }

    // 调用生成稀疏上三角矩阵的函数
    generate_sparse_upper_triangular_matrix(A, b);

    // 开始计时
    clock_t start_time = clock();

    // 使用雅克比迭代法求解
    jacobi(A, b, x);

    // 结束计时
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("雅克比迭代法运行时间: %f 秒\n", elapsed_time);

    // 评估解的准确性
    double accuracy = evaluate_accuracy(x, b, A);
    printf("解的准确性误差总和: %f\n", accuracy);

    // 输出解向量的前10个值
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
