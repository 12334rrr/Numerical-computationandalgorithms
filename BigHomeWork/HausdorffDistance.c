#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1000

// 定义点结构体
typedef struct {
    double x;
    double y;
} Point;

// 计算两点之间的欧几里得距离
double euclidean_distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 计算集合A和集合B之间的Hausdorff距离
double hausdorff_distance(Point setA[], int sizeA, Point setB[], int sizeB) {
    double max_dist_a_to_b = 0.0;

    // 计算集合A中每个点到集合B的最近距离
    for (int i = 0; i < sizeA; i++) {
        double min_dist_a_to_b = INFINITY;
        for (int j = 0; j < sizeB; j++) {
            double dist = euclidean_distance(setA[i], setB[j]);
            if (dist < min_dist_a_to_b) {
                min_dist_a_to_b = dist;
            }
        }
        if (min_dist_a_to_b > max_dist_a_to_b) {
            max_dist_a_to_b = min_dist_a_to_b;
        }
    }

    double max_dist_b_to_a = 0.0;

    // 计算集合B中每个点到集合A的最近距离
    for (int i = 0; i < sizeB; i++) {
        double min_dist_b_to_a = INFINITY;
        for (int j = 0; j < sizeA; j++) {
            double dist = euclidean_distance(setB[i], setA[j]);
            if (dist < min_dist_b_to_a) {
                min_dist_b_to_a = dist;
            }
        }
        if (min_dist_b_to_a > max_dist_b_to_a) {
            max_dist_b_to_a = min_dist_b_to_a;
        }
    }

    // Hausdorff距离是最大值
    return fmax(max_dist_a_to_b, max_dist_b_to_a);
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
    Point setA[MAX_POINTS];
    for (int i = 0; i < sizeA; i++) {
        fscanf(file, "%lf %lf", &setA[i].x, &setA[i].y);
    }

    // 读取集合B的点数
    int sizeB;
    fscanf(file, "%d", &sizeB);

    // 读取集合B的点
    Point setB[MAX_POINTS];
    for (int i = 0; i < sizeB; i++) {
        fscanf(file, "%lf %lf", &setB[i].x, &setB[i].y);
    }

    // 计算Hausdorff距离
    double hd = hausdorff_distance(setA, sizeA, setB, sizeB);
    printf("Hausdorff Distance: %lf\n", hd);

    fclose(file);
    return 0;
}
