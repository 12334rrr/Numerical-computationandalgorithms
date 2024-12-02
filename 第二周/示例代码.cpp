//#include "stdafx.h"
//
// Created by hp on 2024/9/10.
//


#include "math.h"
#include<iostream>
int main()
{
    double a = 1.,
            b = -(1e7+1e-7),
            c = 1.,
            d,
            x1,
            x2 ;
    d = b*b-4*a*c ;
    d = sqrt(d) ;
    x1 = (-b+d)/(2*a) ;
    x2 = (-b-d)/(2*a) ;
    std::cout << "x1=" << x1 << std::endl ;
    std::cout << "x2=" << x2 << std::endl ;
    return 0;
}