#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1000
#define LEARNING_RATE 0.01
#define MAX_ITERATIONS 10000
#define EPSILON 1e-6

// 定义点结构体
typedef struct {
    double x;
    double y;
} Point;

// 计算两点之间的欧几里得距离
double euclidean_distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 计算目标函数值
double objective_function(Point A[], int sizeA, Point B[], int sizeB) {
    double sum = 0.0;
    for (int i = 0; i < sizeA; i++) {
        double min_dist = INFINITY;
        for (int j = 0; j < sizeB; j++) {
            double dist = euclidean_distance(A[i], B[j]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        sum += min_dist * min_dist;  // 目标函数是距离的平方
    }
    return sum;
}

// 计算目标函数的梯度
void compute_gradient(Point A[], int sizeA, Point B[], int sizeB, double gradA[], double gradB[]) {
    for (int i = 0; i < sizeA; i++) {
        gradA[i * 2] = 0.0;
        gradA[i * 2 + 1] = 0.0;
        double min_dist = INFINITY;
        int min_idx = -1;
        for (int j = 0; j < sizeB; j++) {
            double dist = euclidean_distance(A[i], B[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = j;
            }
        }

        // 对A点的梯度计算
        gradA[i * 2] = 2 * (A[i].x - B[min_idx].x);
        gradA[i * 2 + 1] = 2 * (A[i].y - B[min_idx].y);
    }

    for (int i = 0; i < sizeB; i++) {
        gradB[i * 2] = 0.0;
        gradB[i * 2 + 1] = 0.0;
        double min_dist = INFINITY;
        int min_idx = -1;
        for (int j = 0; j < sizeA; j++) {
            double dist = euclidean_distance(A[j], B[i]);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = j;
            }
        }

        // 对B点的梯度计算
        gradB[i * 2] = 2 * (B[i].x - A[min_idx].x);
        gradB[i * 2 + 1] = 2 * (B[i].y - A[min_idx].y);
    }
}

// 使用梯度下降优化目标函数
void gradient_descent(Point A[], int sizeA, Point B[], int sizeB) {
    double gradA[MAX_POINTS * 2], gradB[MAX_POINTS * 2];

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        // 计算梯度
        compute_gradient(A, sizeA, B, sizeB, gradA, gradB);

        // 更新A点和B点的坐标
        for (int i = 0; i < sizeA; i++) {
            A[i].x -= LEARNING_RATE * gradA[i * 2];
            A[i].y -= LEARNING_RATE * gradA[i * 2 + 1];
        }
        for (int i = 0; i < sizeB; i++) {
            B[i].x -= LEARNING_RATE * gradB[i * 2];
            B[i].y -= LEARNING_RATE * gradB[i * 2 + 1];
        }

        // 计算目标函数的值
        double loss = objective_function(A, sizeA, B, sizeB);
        if (loss < EPSILON) {
            printf("梯度下降已收敛！\n");
            break;
        }
    }
}

// 计算Hausdorff距离
double hausdorff_distance(Point A[], int sizeA, Point B[], int sizeB) {
    double max_dist = 0.0;
    for (int i = 0; i < sizeA; i++) {
        double min_dist = INFINITY;
        for (int j = 0; j < sizeB; j++) {
            double dist = euclidean_distance(A[i], B[j]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        if (min_dist > max_dist) {
            max_dist = min_dist;
        }
    }

    for (int i = 0; i < sizeB; i++) {
        double min_dist = INFINITY;
        for (int j = 0; j < sizeA; j++) {
            double dist = euclidean_distance(B[i], A[j]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        if (min_dist > max_dist) {
            max_dist = min_dist;
        }
    }
    return max_dist;
}

int main() {
    FILE *file = fopen("BigHomeWork/in.txt", "r");
    if (file == NULL) {
        perror("无法打开文件 in.txt");
        return -1;
    }

    // 读取集合A的点数
    int sizeA;
    fscanf(file, "%d", &sizeA);

    // 读取集合A的点
    Point A[MAX_POINTS];
    for (int i = 0; i < sizeA; i++) {
        fscanf(file, "%lf %lf", &A[i].x, &A[i].y);
    }

    // 读取集合B的点数
    int sizeB;
    fscanf(file, "%d", &sizeB);

    // 读取集合B的点
    Point B[MAX_POINTS];
    for (int i = 0; i < sizeB; i++) {
        fscanf(file, "%lf %lf", &B[i].x, &B[i].y);
    }

    // 使用梯度下降优化计算Hausdorff距离
    gradient_descent(A, sizeA, B, sizeB);

    // 计算最终的Hausdorff距离
    double hd = hausdorff_distance(A, sizeA, B, sizeB);
    printf("Hausdorff Distance: %lf\n", hd);

    fclose(file);
    return 0;
}
