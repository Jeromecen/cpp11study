//
//  constexprtest.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/7.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "constexprtest.hpp"
//    const int GetConst()
//    {
//        return 1;
//    }

constexpr int Fibonacci(int n){
    return (n==1) ? 1 : ( (n==2) ? 1 : Fibonacci(n-1) + Fibonacci(n-2) );
}

void ConstExpr::Print()
{
    int arr[GetConst()] = {0};
    for(auto &e : arr)
    {
        e = 200;
    }
    
    int i = 1;
    switch(i)
    {
        case GetConst():
        {
            break;
        }
    }
    cout << "ConstExpr::Print()" << endl;
    cout << "E1" << E1 << endl;
    cout << "arr:";
    for(auto &e : arr)
    {
        cout << e << " ";
    }
    cout << endl;
    
    // constexpr常量表达式，在编译期计算值,编译前如果不使用则不会产生该标识符；const是运行时的编译器都会为其产生值。
    const int ci = 10;
    constexpr int cei = 10;
    constexpr float cef = 10.2f;
    cout << cei << "  " << cef << endl;
    
    // constexpr 用在自定义类型中，需要编写constexpr构造函数，构造的对象要是constexpr类型的，就可以获取constexpr函数成员了。
    // 非constexpr类型的函数成员不能调用,而数据成员可以调用。
    constexpr ExprData date = {2017,6,7};
    cout<< "constexpr ExprData test" << endl;
    cout << "year:" << date.getYear() << endl;
    cout << "month:" << date.getMonth() << endl;
    cout << "day:" << date.getDay() << endl;
//    cout << "day:" << date.getData() << endl; // 非constexpr类型的函数成员不能调用
    cout << date.d << endl;
    
    int fbnc[] = {Fibonacci(1), Fibonacci(2), Fibonacci(3), Fibonacci(4), Fibonacci(5), Fibonacci(6), Fibonacci(7), Fibonacci(8), Fibonacci(9), Fibonacci(10)};
    cout << "constexpr Fibonacci test:" << endl;
    for( auto &e : fbnc)
    {
        cout << e << " ";
    }
    cout << endl;
    
    int fbncTemp[] = {FibonacciTemp<1>::val, FibonacciTemp<2>::val, FibonacciTemp<3>::val, FibonacciTemp<4>::val, FibonacciTemp<5>::val, FibonacciTemp<6>::val,FibonacciTemp<7>::val, FibonacciTemp<8>::val};
    cout << "template Fibonacci test:" << endl;
    for( int e : fbncTemp)
    {
        cout << e << " ";
    }
    cout << endl;

    
}
