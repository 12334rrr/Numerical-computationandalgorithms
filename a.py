import numpy as np
import matplotlib.pyplot as plt

# 设置种子以确保结果可重现
np.random.seed(42)

# 生成测试数据 (6列 11行)
# 每个格子的值为浮动在 0 到 100 之间的浮点数
data = np.random.uniform(0, 100, (3, 11, 6))

# 计算每行的平均值和方差
mean_values = np.mean(data, axis=1)  # 计算每行的平均值
var_values = np.var(data, axis=1)    # 计算每行的方差

# 创建图形
fig, ax = plt.subplots(figsize=(12, 8))

# 绘制数据矩阵
# 我们通过 'imshow' 绘制每个格子的数值，并显示数值
cax = ax.matshow(data[0], cmap="Blues", vmin=0, vmax=100)

# 在每个格子中显示对应的数值
for i in range(3):  # 3行
    for j in range(11):  # 11列
        ax.text(j, i, f'{data[i, j]:.2f}', ha='center', va='center', color='black')

# 设置 x 和 y 轴标签
ax.set_xticks(np.arange(6))
ax.set_xticklabels(['普通取点', '优化取点', '梯度下降', '平均数', '方差'])
ax.set_yticks(np.arange(3))
ax.set_yticklabels(['Testcase 1', 'Testcase 2', 'Testcase 3'])

# 设置标题
plt.title('测试数据矩阵及每行平均值与方差')

# 在图表下方添加平均值和方差
# 设置平均值和方差的数值标签
for i in range(3):
    ax.text(3, i, f'Mean: {mean_values[i, -1]:.2f}', ha='center', va='center', color='black', fontsize=12)
    ax.text(4, i, f'Var: {var_values[i, -1]:.2f}', ha='center', va='center', color='black', fontsize=12)

# 显示图表
plt.colorbar(cax, ax=ax, label='数值范围 (0-100)')

# 设置图形边距
plt.tight_layout()
plt.show()
