#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 计算两个点之间的欧几里得距离，扩展为n维
double euclidean_distance(double *p1, double *p2, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += pow(p1[i] - p2[i], 2);  // 计算每个维度的差值平方
    }
    return sqrt(sum);  // 返回平方根
}

// 计算 Bézier 曲线上的点
void bezier_curve(double **control_points, int num_points, int n, double **curve_points) {
    double t, binomial_coeff;
    int i, j;

    for (i = 0; i < num_points; i++) {
        t = (double)i / (num_points - 1); // 计算 t 值
        // 初始化曲线点
        for (int d = 0; d < n; d++) {
            curve_points[i][d] = 0.0;
        }

        for (j = 0; j < n; j++) {
            binomial_coeff = 1;
            for (int k = 0; k < j; k++) {
                binomial_coeff *= (n - k) / (k + 1.0);
            }
            // 计算 Bézier 曲线上的点
            for (int d = 0; d < n; d++) {
                curve_points[i][d] += binomial_coeff * pow(1 - t, n - j - 1) * pow(t, j) * control_points[j][d];
            }
        }
    }
}

// 计算 Hausdorff 距离的一个方向 (从 A 到 B)
double directed_hausdorff(double **curve_a, int a_size, double **curve_b, int b_size, int n) {
    double max_distance = 0.0;
    for (int i = 0; i < a_size; i++) {
        double min_distance = INFINITY;
        for (int j = 0; j < b_size; j++) {
            double dist = euclidean_distance(curve_a[i], curve_b[j], n);  // 使用n维欧几里得距离
            if (dist < min_distance) {
                min_distance = dist;
            }
        }
        if (min_distance > max_distance) {
            max_distance = min_distance;
        }
    }
    return max_distance;
}

// 计算两条曲线的 Hausdorff 距离
double hausdorff_distance(double **curve_a, int a_size, double **curve_b, int b_size, int n) {
    double d_ab = directed_hausdorff(curve_a, a_size, curve_b, b_size, n);
    double d_ba = directed_hausdorff(curve_b, b_size, curve_a, a_size, n);
    return (d_ab > d_ba) ? d_ab : d_ba;
}

// 主函数计算两条 Bézier 曲线的 Hausdorff 距离
double HDTwoCurve(double **curve_a_control_points, int a_size, double **curve_b_control_points, int b_size, int num_points, int n) {
    // 动态分配内存
    double **curve_a = (double **)malloc(num_points * sizeof(double *));
    double **curve_b = (double **)malloc(num_points * sizeof(double *));
    for (int i = 0; i < num_points; i++) {
        curve_a[i] = (double *)malloc(n * sizeof(double));
        curve_b[i] = (double *)malloc(n * sizeof(double));
    }

    // 离散化 Bézier 曲线
    bezier_curve(curve_a_control_points, num_points, n, curve_a);
    bezier_curve(curve_b_control_points, num_points, n, curve_b);

    // 计算 Hausdorff 距离
    double hd = hausdorff_distance(curve_a, num_points, curve_b, num_points, n);

    // 释放内存
    for (int i = 0; i < num_points; i++) {
        free(curve_a[i]);
        free(curve_b[i]);
    }
    free(curve_a);
    free(curve_b);

    return hd;
}

int main() {
    // 打开输入文件
    FILE *in_file = fopen("../Code/BigHomeWork/in.txt", "r");
    if (in_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    else {
        printf("Input file opened successfully.\n");
    }
    // 读取 Bézier 曲线 A 的控制点数量
    int a_size;
    fscanf(in_file, "%d", &a_size);

    // 动态分配 Bézier 曲线 A 的控制点
    double **curve_a_control_points = (double **) malloc(a_size * sizeof(double *));
    for (int i = 0; i < a_size; i++) {
        curve_a_control_points[i] = (double *) malloc(2 * sizeof(double)); // 假设控制点是二维的
    }

    // 填充 Bézier 曲线 A 的控制点
    for (int i = 0; i < a_size; i++) {
        fscanf(in_file, "%lf %lf", &curve_a_control_points[i][0], &curve_a_control_points[i][1]);
    }

    // 读取 Bézier 曲线 B 的控制点数量
    int b_size;
    fscanf(in_file, "%d", &b_size);

    // 动态分配 Bézier 曲线 B 的控制点
    double **curve_b_control_points = (double **) malloc(b_size * sizeof(double *));
    for (int i = 0; i < b_size; i++) {
        curve_b_control_points[i] = (double *) malloc(2 * sizeof(double)); // 假设控制点是二维的
    }

    // 填充 Bézier 曲线 B 的控制点
    for (int i = 0; i < b_size; i++) {
        fscanf(in_file, "%lf %lf", &curve_b_control_points[i][0], &curve_b_control_points[i][1]);
    }

    // 设定离散化的点数
    int num_points = 100;

    // 设定空间的维度（二维）
    int n = 2;

    // 关闭输入文件
    fclose(in_file);

    // 计算 Hausdorff 距离
    double hd = HDTwoCurve(curve_a_control_points, a_size, curve_b_control_points, b_size, num_points, n);

    // 打开输出文件
    FILE *out_file = fopen("../Code/BigHomeWork/out.txt", "w");
    if (out_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }
    else{
        printf("Output file opened successfully.\n");
    }

    // 将计算结果写入输出文件
    fprintf(out_file, "Hausdorff Distance: %lf\n", hd);

    // 关闭输出文件
    fclose(out_file);

    // 释放内存
    for (int i = 0; i < a_size; i++) {
        free(curve_a_control_points[i]);
    }
    free(curve_a_control_points);

    for (int i = 0; i < b_size; i++) {
        free(curve_b_control_points[i]);
    }
    free(curve_b_control_points);

    return 0;
}