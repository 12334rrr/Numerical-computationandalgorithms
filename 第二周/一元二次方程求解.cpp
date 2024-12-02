/**
 * Author: 王春博
 * Date: 2024.9.10
 * Description: 数值计算与算法：一元二次方程求解
 */


#include <stdio.h>
#include <math.h>
#include <float.h>

#define LARGE_THRESHOLD 1e150
#define SMALL_THRESHOLD 1e-150

// 使用标准求根公式求解
void solve_standard(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        printf("No real roots\n");
        return;
    }

    double sqrt_d = sqrt(discriminant);
    double x1 = (-b + sqrt_d) / (2 * a);
    double x2 = (-b - sqrt_d) / (2 * a);

    printf("Standard roots: x1 = %.10e, x2 = %.10e\n", x1, x2);
}

// 使用优化的求根公式处理
void solve_optimized(double a, double b, double c) {
    double scale = fmax(fabs(a), fmax(fabs(b), fabs(c)));
    a /= scale;
    b /= scale;
    c /= scale;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        printf("No real roots\n");
        return;
    }

    double sqrt_d = sqrt(discriminant);
    double x1, x2;

    if (b >= 0) {
        x1 = (-b - sqrt_d) / (2 * a);
        x2 = (2 * c) / (-b - sqrt_d);
    } else {
        x1 = (-b + sqrt_d) / (2 * a);
        x2 = (2 * c) / (-b + sqrt_d);
    }

    x1 *= scale;
    x2 *= scale;

    printf("Optimized roots: x1 = %.10e, x2 = %.10e\n", x1, x2);
}

// 使用牛顿迭代法
void solve_newton(double a, double b, double c, double initial_guess) {
    double x = initial_guess;
    int max_iterations = 10000;
    double tolerance = 1e-12;

    for (int i = 0; i < max_iterations; ++i) {
        double fx = a * x * x + b * x + c;
        double fpx = 2 * a * x + b;

        if (fabs(fpx) < DBL_EPSILON) {
            printf("Derivative near zero; Newton method fails.\n");
            return;
        }

        double x_new = x - fx / fpx;

        if (fabs(x_new - x) < tolerance) {
            printf("Newton root: x = %.10e\n", x_new);
            return;
        }

        x = x_new;
    }

    printf("Failed to converge after %d iterations.\n", max_iterations);
}

// 主函数，判断使用哪种方法求解
void solve_quadratic(double a, double b, double c, double initial_guess) {
    if (fabs(a) == 0) {
        // 处理线性方程
        if (fabs(b) < DBL_EPSILON) {
            printf("No valid roots (both a and b are near zero)\n");
        } else {
            double root = -c / b;
            printf("Linear equation root: x = %.10e\n", root);
        }
        return;
    }

    // 检查系数的绝对值大小
    if (fabs(a) < LARGE_THRESHOLD && fabs(a) > SMALL_THRESHOLD &&
        fabs(b) < LARGE_THRESHOLD && fabs(b) > SMALL_THRESHOLD &&
        fabs(c) < LARGE_THRESHOLD && fabs(c) > SMALL_THRESHOLD) {
        // 使用标准公式
        solve_standard(a, b, c);
    } else if ((fabs(a) > LARGE_THRESHOLD && fabs(b) > LARGE_THRESHOLD && fabs(c) > LARGE_THRESHOLD) ||
               (fabs(a) < SMALL_THRESHOLD && fabs(b) < SMALL_THRESHOLD && fabs(c) < SMALL_THRESHOLD)) {
        // 使用优化公式
        solve_optimized(a, b, c);
    } else {
        // 使用牛顿迭代法，需要用户提供初始猜测值
        printf("Using Newton method with initial guess: %.10e\n", initial_guess);
        solve_newton(a, b, c, initial_guess);
    }
}

int main() {
    // 测试数据
    double a,b,c,initial_guess;
    double array_a[10] = {6e154,0,1,1,1e-154,1};
    double array_b[10] = {4e154,2,-1e6,-(1e8+1e-8),-1e155,-5};
    double array_c[10] = {-5e154,2,1,1.5,1e155,4.999999};
    for(int i = 0 ; i<6 ; i++)
    {
        a = array_a[i];
        b = array_b[i];
        c = array_c[i];
        printf("a = %.10e, b = %.10e, c = %.10e\n", a, b, c);
        printf("Standard roots:\n");
        solve_standard(a, b, c);
        printf("Optimized roots:\n");
        solve_optimized(a, b, c);
        printf("Please input initial guess:");
        scanf("%lf",&initial_guess);
        solve_quadratic(a, b, c, initial_guess);
    }
    return 0;
}
