//
//  SFINAETest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef SFINAETest_hpp
#define SFINAETest_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
struct SFINAE_A
{
    typedef int foo;
};

template<typename T>
void SFINAE_Foo(typename T::foo t) // 模板中要继续用typename限定，否则会有问题
{
    cout << "SFINAE_Foo(typename T::foo t) call" << endl;
}

template<typename T>
void SFINAE_Foo(T t)
{
     cout << "SFINAE_Foo(T t) call" << endl;
}


template <int I> // 该声明，暂时不清楚用意
struct SFINAE_Type
{
};

char xxx(int); // 这里只是声明
char xxx(float);
template <typename T>
SFINAE_Type<sizeof( xxx((T)0) )> SFINAE_Func(T t) // 用意是根据实例化类型，用sizeof表达式运算获取不同的SFINAE_Type返回值。
{
    // 模板参数表达式的支持，是c++ 11新引入的特性，有利于decltype和模板库更加灵活的编写和调用。
//c++11规定"没有出现外部于表达式本身的元素"都不会有SFINAE错误，表达式若有模板实例化或出现隐式构造函数调用等则是出现了外部于表达式的，是不支持的。
}
#endif /* SFINAETest_hpp */
