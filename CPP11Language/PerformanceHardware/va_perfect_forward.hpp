//
//  va_perfect_forward.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef va_perfect_forward_hpp
#define va_perfect_forward_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

struct A
{
    A()
    {
    }
    A(const A& a)
    {
        cout << "Copy Constructed " << __func__ << endl;
    }
    A(A&& a)
    {
        cout << "Move Constructed " << __func__ << endl;
    }
};

struct B
{
    B()
    {
    }
    B(const B& b)
    {
        cout << "Copy Constructed " << __func__ << endl;
    }
    B(B&& b)
    {
        cout << "Move Constructed " << __func__ << endl;
    }
};

//变长模版定义
template<typename ... T> struct MultiTypes;
template<typename T1, typename ... T>
// 每个包都解包为T1+T,其中T作为递归的父类变长类型。
struct MultiTypes<T1, T...> : public MultiTypes<T...>
{
    // 利用类型T1,T...声明实例类型t1,a和b;进行拆包的递归构造函数声明
    T1 t1;
    MultiTypes<T1, T...>(T1 a, T ... b)
    : t1(a), MultiTypes<T...>(b...)
    {
        cout << "MultiTypes<T1, T...>(T1 a, T ... b)" << endl;
    }
};
template<> struct MultiTypes<>
{
    MultiTypes<>()
    {
        cout << "MultiTypes<>()" << endl;
    }
};
//完美装发
template< template<typename... >class VariadicType, typename...Args >
// Build的返回值是一个VariadicType<Args...>用...Args作为实例化的变长类型。
// Build的参数Args&&... args是输入的...Args的变长参数的右值引用。
VariadicType<Args...> Build(Args&&... args)
{
// 根据调用端的代码分析：
//    A a;
//    B b;
//    Build<MultiTypes>(a, b);
// 返回函数对a和b每个参数进行解包；转发到VariadicType<Args...>的多类型，多参数构造函数；最终递归返回构造出一个Build<a,b>的对象。优点是构造出该对象没有任何a,b的拷贝构造和移动构造函数的调用。
    return VariadicType<Args...>(std::forward<Args>(args)...);
}

void PrintVaPerfectForward();
#endif /* va_perfect_forward_hpp */
