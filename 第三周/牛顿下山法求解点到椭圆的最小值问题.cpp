/**
* @Author: 王春博
 * @Date: 2024.9.23
 * @Description: 数值计算与算法：牛顿下山法求解点到椭圆曲线的最小值问题
 */
#include <iostream>
#include <cmath>
#include <random>

const double epsilon = 1e-6;  // 迭代精度

double generateRandomDouble(double lower_bound, double upper_bound) {
    std::random_device rd;  // 用于生成种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister算法的随机数生成器
    std::uniform_real_distribution<> dis(lower_bound, upper_bound); // 定义浮点数分布范围

    return dis(gen); // 生成随机浮点数
}

void getRandom(double &x, double &y, double &a, double &b) {
    a = generateRandomDouble(0, 100);
    b = generateRandomDouble(0, 100);
    x = generateRandomDouble(-1000, 1000);
    y = generateRandomDouble(-1000, 1000);
}

// 距离函数的梯度
void gradient(double x, double y, double x0, double y0, double *gradX, double *gradY) {
    *gradX = 2 * (x - x0);
    *gradY = 2 * (y - y0);
}

// 更新坐标
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
    double x0, y0, a, b, x, y;
    getRandom(x0, y0, a, b);
    std::cout << "x0: " << x0 << ", y0: " << y0 << ", a: " << a << ", b: " << b << std::endl;
    //使用牛顿下山法求解

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