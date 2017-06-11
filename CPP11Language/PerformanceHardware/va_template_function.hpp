//
//  va_template_function.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/7.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef va_template_function_hpp
#define va_template_function_hpp

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
using namespace std;

double sum(int n, ...);//求n个double数据之和
void PrintDynamicArgLenFunc();

// Multiply 模板中编译器求取static const值，驱动手动编写递归实现变长乘法实现
template<long...nums> struct Multiply; // 自定义类型，变长参数声明
template<long first,long ...last> // 自定义类型，递归的解包定义
struct Multiply<first,last...>
{
    static const long val = first * Multiply<last...>::val;
};
template<> struct Multiply < > { static const long val = 1; }; // 自定义类型，终止条件

// Printf 编译器要求取模板解包的T value值，调用手动定义的递归调用，实现变长的Printf参数。
void Printf(const char *s);
template<typename T,typename ...Args> // 自定义函数，递归的解包定义
void Printf(const char * s, T value, Args... args)
{
    cout << "Printf outer begin: " << endl;
    while (*s)
    {
        if (*s=='%'&&*++s!='%')
        {
            cout << "value begin: " << endl;
            cout << value;
            cout << endl;
            return Printf(++s, args...);
        }
        cout << *s++;
        cout << endl;
    }
    throw runtime_error("extraarguments provided to Printf");
}

template <typename ...T> // ...T要链接在一起, 类型的声明
void DummyWrapper( T... t) // T...要正确， 类型的使用
{

}

template <typename T>
T Pr(T t)
{
    cout << t << " ";
    return t;
}

template <typename ...T>
void PrintDummy(T... a)
{
    DummyWrapper(Pr(a)...);// Pr(a)...展开也要正确，类型的展开
}



#endif /* va_template_function_hpp */
