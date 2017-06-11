//
//  constexprtest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/7.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef constexprtest_hpp
#define constexprtest_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
//    const int GetConst()
//    {
//        return 1;
//    }
constexpr int GetConst()
{
    return 2;
};

class ExprData
{
public:
    constexpr ExprData(int yy, int mm, int dd):y(yy),m(mm), d(dd){}
    constexpr int getYear(){ return y;}
    constexpr int getMonth() { return m;}
    constexpr int getDay() { return d;}
    int getData() { return d;}
    int y,m,d; // 非constexpr的数据成员
};

class ConstExpr
{
public:
//    const int enumStart = 2;
    enum eNumType
    {
        E1 = GetConst(),
        E2,
    };
    void Print();
    
//    enum
//    {
//        V0 = 1 << 0,
//        V1 = 1 << 1,
//        V2 = 1 << 2,
//        VMAX = 1 << 3,
//    };
//    template <typename i = V0 | V1>
//    void LinkBitSet(){};
};
template<long num> struct FibonacciTemp
{
    static const long val = FibonacciTemp<num - 1>::val + FibonacciTemp<num - 2>::val;
};

template<> struct FibonacciTemp<0>{ static const long val = 1;};
template<> struct FibonacciTemp<1>{ static const long val = 1;};
template<> struct FibonacciTemp<2>{ static const long val = 1;};

#endif /* constexprtest_hpp */
