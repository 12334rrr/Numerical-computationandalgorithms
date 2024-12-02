cmake_minimum_required(VERSION 3.25)
project(数值计算与算法)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        main.cpp
        第二周/示例代码.cpp 第二周/一元二次方程求解.cpp
        第三周/牛顿下山法求解点到椭圆的最小值问题.cpp 第三周/牛顿下山法求解点到椭圆的最小值问题.c
        第四周/高斯消去法求解线性方程.cpp
        第五周/雅可比迭代法求解高阶稀疏矩阵.c
        第四周/高斯消去法求解线性方程.c main.cpp
        第十次作业/基于复化辛卜生公式的变步长求积算法.c
        BigHomeWork/HausdorffDistance.c BigHomeWork/draw.c BigHomeWork/draw.c BigHomeWork/draw.c)
