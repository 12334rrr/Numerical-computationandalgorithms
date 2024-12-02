/**
* @Author: 王春博
 * @Date: 2024.9.23
 * @Description: 数值计算与算法：牛顿下山法求解点到椭圆曲线的最小值问题
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double epsilon = 1e-6;  // 迭代精度

// 生成指定范围内的随机浮点数
double generateRandomDouble(double lower_bound, double upper_bound) {
    double scale = rand() / (double) RAND_MAX; // 生成 0 到 1 之间的随机浮点数
    return lower_bound + scale * (upper_bound - lower_bound); // 缩放到指定范围
}

// 生成随机的 x, y, a, b
void getRandom(double *x, double *y, double *a, double *b) {
    *a = generateRandomDouble(0, 100);
    *b = generateRandomDouble(0, 100);
    *x = generateRandomDouble(-1000, 1000);
    *y = generateRandomDouble(-1000, 1000);
}

// 距离函数的梯度
void gradient(double x, double y, double x0, double y0, double *gradX, double *gradY) {
    *gradX = 2 * (x - x0);
    *gradY = 2 * (y - y0);
}

// 更新坐标，牛顿下山法
void newton_descent(double *x, double *y, double x0, double y0, double a, double b) {
    double gradX, gradY;
    gradient(*x, *y, x0, y0, &gradX, &gradY);

    // 使用牛顿法更新 x, y
    double lambda = 0.1;  // 学习率
    *x = *x - lambda * gradX;
    *y = *y - lambda * gradY;

    // 投影到椭圆上
    double scale = sqrt((*x * *x) / (a * a) + (*y * *y) / (b * b));
    *x /= scale;
    *y /= scale;
}

int main() {
    // 初始化随机数种子
    srand(time(NULL));

    double x0, y0, a, b, x, y;
    getRandom(&x0, &y0, &a, &b);
    printf("x0: %f, y0: %f, a: %f, b: %f\n", x0, y0, a, b);

    // 设置初始值
    x = a;
    y = 0;

    // 牛顿下山法迭代
    while (1) {
        double dist = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
        printf("x: %f, y: %f, distance: %f\n", x, y, dist);

        double prevX = x, prevY = y;
        newton_descent(&x, &y, x0, y0, a, b);

        // 判断收敛
        if (fabs(x - prevX) < epsilon && fabs(y - prevY) < epsilon) {
            break;
        }
    }

    return 0;
}
