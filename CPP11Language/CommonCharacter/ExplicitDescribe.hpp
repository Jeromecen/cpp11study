//
//  ExplicitDescribe.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef ExplicitDescribe_hpp
#define ExplicitDescribe_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
struct Rational1{
    Rational1(int n = 0, int d = 1): num(n),den(d){
        cout<<"Rational1 call " << endl;
    }
    int num;
    int den;
};

struct Rational2{
    // 只有在直接构造目标类型或显式类型转换的时候可以使用该类型
    explicit Rational2(int n = 0, int d = 1): num(n),den(d){
        cout<<"Rational2 call " << endl;
    }
    int num;
    int den;
};

void Display1(Rational1 ra);
void Display2(Rational2 ra);
void PrintExplict();

template<typename T>
class Ptr{
public:
    Ptr(T *p):ptr(p){}
    inline explicit operator bool ()const // cpp中可以声明类型转换函数的返回值，运算符重载函数也是可以有返回值的。
    {
        if(ptr == nullptr)
        {
            return false;
        }
        return true;
    }
private:
    T *ptr;
};
#endif /* ExplicitDescribe_hpp */
