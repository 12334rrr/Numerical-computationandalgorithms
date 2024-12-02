//  Author: 王春博
//  Date: 2024/9/3
//  Description: 浮点数结合律测试

#include "浮点数结合律测试.h"
#include<iostream>

int main() {
    double a = 1e-10, b = 1e10, c = -1e10;
    std::cout << a + b + c << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a + (b + c) << std::endl;
    std::cout << b + c << std::endl;
    return 0;
}