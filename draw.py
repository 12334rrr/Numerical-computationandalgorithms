import numpy as np
import matplotlib.pyplot as plt


# 计算贝塞尔曲线上的点
def bezier_curve(control_points, num_points=100):
    """
    :param control_points: 控制点列表（二维坐标）
    :param num_points: 曲线上的点数（离散化数目）
    :return: 贝塞尔曲线上的点
    """
    t = np.linspace(0, 1, num_points)
    n = len(control_points) - 1
    curve_points = np.zeros((num_points, 2))

    for i in range(n + 1):
        binomial_coeff = np.math.comb(n, i)  # 计算二项式系数
        curve_points[:, 0] += binomial_coeff * (1 - t) ** (n - i) * t ** i * control_points[i][0]  # X 坐标
        curve_points[:, 1] += binomial_coeff * (1 - t) ** (n - i) * t ** i * control_points[i][1]  # Y 坐标

    return curve_points


# 贝塞尔曲线 A 的控制点
control_points_a = np.array([[0, 0], [1, 2], [3, 3], [4, 0]])

# 贝塞尔曲线 B 的控制点
control_points_b = np.array([[0, 0], [1, 1], [3, 2], [4, 0]])

# 计算贝塞尔曲线上的点
curve_a = bezier_curve(control_points_a)
curve_b = bezier_curve(control_points_b)

# 绘制曲线
plt.plot(curve_a[:, 0], curve_a[:, 1], label='Bezier Curve A', color='r')  # 红色
plt.plot(curve_b[:, 0], curve_b[:, 1], label='Bezier Curve B', color='b')  # 蓝色

# 绘制控制点
plt.scatter(control_points_a[:, 0], control_points_a[:, 1], color='r', marker='o')
plt.scatter(control_points_b[:, 0], control_points_b[:, 1], color='b', marker='o')

# 绘制控制线
plt.plot(control_points_a[:, 0], control_points_a[:, 1], '--', color='r')  # 红色控制线
plt.plot(control_points_b[:, 0], control_points_b[:, 1], '--', color='b')  # 蓝色控制线

# 设置图形属性
plt.title('Bezier Curves')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid(True)

# 显示图形
plt.show()
