//  Author: 王春博
//  Date: 2024/9/3
//  Description: 浮点数交换律测试


#include "浮点数交换律测试.h"
#include<iostream>

int main() {
    double a = 2332432.2394923992034092348, b = 3294829.24772394792389424;
    std::cout << a + b << std::endl;
    std::cout << b + a << std::endl;
    std::cout << ((a+b==b+a)?"满足交换律":"不满足交换律") << std::endl;
    return 0;
}
