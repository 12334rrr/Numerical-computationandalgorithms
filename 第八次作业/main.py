import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial.polynomial import Polynomial

# 1. 在单位半圆圆周上均匀采样点
N = 30  # 采样点数
angles = np.linspace(0, np.pi, N)  # 角度均匀分布在 [0, π] 区间
x_samples = np.cos(angles)  # 根据角度计算 x 坐标
y_samples = np.sin(angles)  # 根据角度计算 y 坐标

# 2. 使用五次多项式进行拟合
degree = 5  # 拟合多项式的阶数
coeffs = np.polyfit(x_samples, y_samples, degree)  # 最小二乘拟合，得到多项式系数
poly = np.poly1d(coeffs)  # 构建五次拟合多项式

# 3. 计算拟合误差 (均方误差)
y_fit = poly(x_samples)  # 计算拟合的 y 值
mse = np.mean((y_samples - y_fit)**2)  # 计算均方误差

# 4. 绘制采样点和拟合曲线
plt.figure(figsize=(8, 6))
plt.plot(x_samples, y_samples, 'bo', label='Sample Points')  # 采样点
plt.plot(x_samples, y_fit, 'r-', label=f'Fitted Polynomial (degree {degree})')  # 拟合多项式曲线
plt.xlabel('x')
plt.ylabel('y')
plt.title(f'Least Squares Polynomial Fit (Degree={degree})\nMSE = {mse:.5f}')
plt.legend()
plt.grid(True)
plt.show()

# 输出拟合多项式的系数和误差
print("Fitted polynomial coefficients:", coeffs)
print(f"Mean Squared Error (MSE): {mse:.5f}")
