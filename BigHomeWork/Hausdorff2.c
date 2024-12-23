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

// 计算三点间的夹角，返回单位弧度
double angle(Point p1, Point p2, Point p3) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p3.x - p2.x;
    double dy2 = p3.y - p2.y;

    double dot_product = dx1 * dx2 + dy1 * dy2;
    double magnitude1 = sqrt(dx1 * dx1 + dy1 * dy1);
    double magnitude2 = sqrt(dx2 * dx2 + dy2 * dy2);

    return acos(dot_product / (magnitude1 * magnitude2));
}

// 计算曲率：通过三点角度变化估算曲率
double curvature(Point p1, Point p2, Point p3) {
    return fabs(angle(p1, p2, p3));
}

// 在曲率较大的地方增加更多采样点
void adaptive_sampling(Point original[], int *size, Point sampled[], int *new_size) {
    *new_size = 0;
    for (int i = 0; i < *size - 2; i++) {
        // 计算曲率
        double curv = curvature(original[i], original[i + 1], original[i + 2]);

        // 如果曲率较大，插入更多点
        sampled[*new_size++] = original[i];

        // 插入额外的点
        if (curv > 0.5) {
            sampled[*new_size++] = original[i + 1];
        }
    }
    sampled[*new_size++] = original[*size - 2];
    sampled[*new_size++] = original[*size - 1];
}

// 计算两集合A和B之间的Hausdorff距离
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

    // 对集合A和集合B进行自适应采样
    Point sampledA[MAX_POINTS], sampledB[MAX_POINTS];
    int new_sizeA, new_sizeB;
    adaptive_sampling(setA, &sizeA, sampledA, &new_sizeA);
    adaptive_sampling(setB, &sizeB, sampledB, &new_sizeB);

    // 计算Hausdorff距离
    double hd = hausdorff_distance(sampledA, new_sizeA, sampledB, new_sizeB);
    printf("Hausdorff Distance: %lf\n", hd);

    fclose(file);
    return 0;
}
