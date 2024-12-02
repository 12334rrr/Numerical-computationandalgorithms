/**
* @Author: 王春博
 * @Date: 2024.10.04
 * @Description: 数值计算与算法：牛顿下山法求解点到椭圆曲线的最小值问题
 */

#include<cstdio>
#include<algorithm>

double augmented_matrix[101][101]; // 增广矩阵

int main() {
    int n;
    scanf("%d", &n);

    // 读取系数
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            scanf("%lf", &augmented_matrix[i][j]);
        }
    }

    // 高斯消去法
    for(int i = 0; i < n; i++) {
        // 如果主元为 0，交换行
        if (augmented_matrix[i][i] == 0) {
            for (int k = i + 1; k < n; k++) {
                if (augmented_matrix[k][i] != 0) {
                    for (int j = 0; j <= n; j++) {
                        std::swap(augmented_matrix[i][j], augmented_matrix[k][j]);
                    }
                    break;
                }
            }
        }

        for(int j = i + 1; j < n; j++) {
            double rate = augmented_matrix[j][i] / augmented_matrix[i][i];
            for(int k = i; k <= n; k++) {
                augmented_matrix[j][k] -= rate * augmented_matrix[i][k];
            }
        }
    }

    // 回代
    double x[100];
    for(int i = n - 1; i >= 0; i--) {
        x[i] = augmented_matrix[i][n];
        for(int j = i + 1; j < n; j++) {
            x[i] -= augmented_matrix[i][j] * x[j];
        }
        x[i] /= augmented_matrix[i][i];
    }

    // 输出结果
    for(int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i + 1, x[i]);
    }

    return 0;
}

//4
//1 -1 2 -1 -8
//2 -2 3 -3 -20
//1 1 1 0 -2
//1 -1 4 3 4