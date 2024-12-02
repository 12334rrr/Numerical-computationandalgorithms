/***
 * 基于复化辛卜生公式的变步长求积算法
 * @Date 2024/11/19
 * @Author: 王春博
 */
#include<stdio.h>
#include<math.h>

double f(double x) {
    return sin(x);
}
double f2(double x) {
    return x*x*x;
}
double composite_simpson(double (*f)(double), double a, double b, double eps, int max_iter) {
    int n = 2;
    double h = (b - a) / n;
    double Tn, T2n;
    int iter;
    // 初始辛卜生公式计算
    Tn = (h / 3) * (f(a) + 4 * f(a + h) + f(b));
    for (iter = 0; iter < max_iter; iter++) {
        T2n = 0.0;
        double x = a;
        for (int i = 0; i < n; i++) {
            double mid = x + h / 2.0;
            T2n += f(x) + 4 * f(mid) + f(x + h);
            x += h;
        }
        T2n *= h / 6;
        if (fabs(T2n - Tn) < eps) {
            return T2n;
        }
        n *= 2;
        h /= 2;
        Tn = T2n;
    }
    printf("迭代次数超过最大迭代次数\n");
    return Tn;
}

int main() {
    double a = 0, b = M_PI,b2=1;
    double eps = 1e-6;
    int max_iter = 50;
    double result = composite_simpson(f, a, b, eps, max_iter);
    printf("the result is:%.8lf\n", result);
    result = composite_simpson(f2, a, b2, eps, max_iter);
    printf("the result is:%.8lf\n", result);
    return 0;
}