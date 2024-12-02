import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad
from numpy.polynomial.chebyshev import Chebyshev

# 目标函数
def f(x):
    return np.sqrt(1 - x**2)

# 定义积分计算切比雪夫系数
def chebyshev_coefficients(n):
    coefficients = []
    for k in range(n + 1):
        integrand = lambda x: f(x) * np.cos(k * np.arccos(x)) / np.sqrt(1 - x**2)
        coeff, _ = quad(integrand, -1, 1)
        if k == 0:
            coefficients.append(coeff / np.pi)
        else:
            coefficients.append(2 * coeff / np.pi)
    return coefficients

# 计算8次和10次的切比雪夫系数
coeff_8 = chebyshev_coefficients(8)
coeff_10 = chebyshev_coefficients(10)

# 构造切比雪夫多项式
T_8 = Chebyshev(coeff_8, domain=[-1, 1])
T_10 = Chebyshev(coeff_10, domain=[-1, 1])

# 绘制函数和逼近多项式
x = np.linspace(-1, 1, 500)
y = f(x)
y_approx_8 = T_8(x)
y_approx_10 = T_10(x)

plt.plot(x, y, label='$f(x) = \sqrt{1 - x^2}$', color='black')
plt.plot(x, y_approx_8, label='8th Degree Approximation', linestyle='--')
plt.plot(x, y_approx_10, label='10th Degree Approximation', linestyle=':')
plt.legend()
plt.xlabel('$x$')
plt.ylabel('$f(x)$')
plt.title('Best Square Approximation of $f(x)$ using Chebyshev Polynomials')
plt.grid(True)
plt.show()

# 计算误差
error_8 = np.sqrt(np.mean((y - y_approx_8)**2))
error_10 = np.sqrt(np.mean((y - y_approx_10)**2))

print(f'8次逼近误差: {error_8}')
print(f'10次逼近误差: {error_10}')
