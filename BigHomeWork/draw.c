#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

// 计算两个点之间的欧几里得距离
double euclidean_distance(double *p1, double *p2, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += pow(p1[i] - p2[i], 2);
    }
    return sqrt(sum);
}

// 计算贝塞尔曲线上的点
void bezier_curve(double **control_points, int num_points, int n, double **curve_points) {
    double t, binomial_coeff;
    int i, j;
    for (i = 0; i < num_points; i++) {
        t = (double)i / (num_points - 1);
        // 初始化曲线点
        for (int d = 0; d < n; d++) {
            curve_points[i][d] = 0.0;
        }
        for (j = 0; j < n; j++) {
            binomial_coeff = 1;
            for (int k = 0; k < j; k++) {
                binomial_coeff *= (n - k) / (k + 1.0);
            }
            // 计算贝塞尔曲线上的点
            for (int d = 0; d < n; d++) {
                curve_points[i][d] += binomial_coeff * pow(1 - t, n - j - 1) * pow(t, j) * control_points[j][d];
            }
        }
    }
}

// 主函数
int main() {
    // 贝塞尔曲线 A 的控制点（二维空间）
    int a_size = 4;
    double *curve_a_control_points[] = {
            (double[]){0, 0},
            (double[]){1, 2},
            (double[]){3, 3},
            (double[]){4, 0}
    };

    // 贝塞尔曲线 B 的控制点（二维空间）
    int b_size = 4;
    double *curve_b_control_points[] = {
            (double[]){0, 0},
            (double[]){1, 1},
            (double[]){3, 2},
            (double[]){4, 0}
    };

    int num_points = 100;  // 离散化的点数
    int n = 2;  // 空间的维度（二维）

    // 初始化 SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bézier Curve", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 计算贝塞尔曲线的离散点
    double **curve_a_points = (double **)malloc(num_points * sizeof(double *));
    double **curve_b_points = (double **)malloc(num_points * sizeof(double *));
    for (int i = 0; i < num_points; i++) {
        curve_a_points[i] = (double *)malloc(n * sizeof(double));
        curve_b_points[i] = (double *)malloc(n * sizeof(double));
    }

    bezier_curve(curve_a_control_points, a_size, n, curve_a_points);
    bezier_curve(curve_b_control_points, b_size, n, curve_b_points);

    // 绘制贝塞尔曲线 A
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // 红色
    for (int i = 1; i < num_points; i++) {
        SDL_RenderDrawLine(renderer, (int)curve_a_points[i-1][0], (int)curve_a_points[i-1][1], (int)curve_a_points[i][0], (int)curve_a_points[i][1]);
    }

    // 绘制贝塞尔曲线 B
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // 蓝色
    for (int i = 1; i < num_points; i++) {
        SDL_RenderDrawLine(renderer, (int)curve_b_points[i-1][0], (int)curve_b_points[i-1][1], (int)curve_b_points[i][0], (int)curve_b_points[i][1]);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);  // 显示 5 秒

    // 释放内存
    for (int i = 0; i < num_points; i++) {
        free(curve_a_points[i]);
        free(curve_b_points[i]);
    }
    free(curve_a_points);
    free(curve_b_points);

    // 清理 SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
