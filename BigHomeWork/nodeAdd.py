import random
import numpy as np

# 原始数据点集
set1 = np.array([[0, 0], [1, 2], [3, 3], [4, 0]])
set2 = np.array([[0, 0], [1, 1], [3, 2], [4, 0]])


# 定义生成随机点的函数
def generate_random_points(original_set, num_points):
    # 获取原始点集的最小和最大坐标值
    min_x, min_y = np.min(original_set, axis=0)
    max_x, max_y = np.max(original_set, axis=0)

    # 生成随机点
    random_points = []
    for _ in range(num_points):
        x = random.uniform(min_x - 1, max_x + 1)  # 在原始范围外稍微扩展一些，以增加随机性
        y = random.uniform(min_y - 1, max_y + 1)
        random_points.append([x, y])

    return np.array(random_points)


# 生成100个随机点的点集
random_set1 = generate_random_points(set1, 100)
random_set2 = generate_random_points(set2, 100)


# 将结果写入文件
def write_points_to_file(filename, points):
    with open(filename, 'w') as file:
        for point in points:
            file.write(f"{point[0]} {point[1]}\n")


# 写入文件
write_points_to_file('random_set1.txt', random_set1)
write_points_to_file('random_set2.txt', random_set2)

# 打印结果到控制台（可选，仅用于验证）
print("Random Set 1 (first 10 points) written to random_set1.txt")
print(random_set1[:10])
print("Random Set 2 (first 10 points) written to random_set2.txt")
print(random_set2[:10])