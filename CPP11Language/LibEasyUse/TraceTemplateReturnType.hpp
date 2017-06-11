//
//  TraceTemplateReturnType.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef TraceTemplateReturnType_hpp
#define TraceTemplateReturnType_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
//template<typename T1, typename T2>
//decltype(t1+t2) Sum(T1 &t1, T2 &t2){ // 返回值的t1,t2是未定义的，因此decltype虽然可以使用在函数参数中，返回值中却得不到值。
//    return t1 + t2;
//}

//template<typename T1, typename T2>
//auto Sum(T1 &t1, T2 &t2){ // auto没有尾随的类型无法得到类型，cpp14中支持。
//    return t1 + t2;
//}

template<typename T1, typename T2>
// 追踪返回类型语法，将返回类型decltype写在函数参数后面，函数返回类型可用auto修饰，但是需要decltype尾随类型支持。
//  -> decltype(t1+t2)称为追踪返回类型
auto Sum(T1 &t1, T2 &t2) -> decltype(t1+t2) {
    return t1 + t2;
}

template<typename T1, typename T2>
auto Multi(T1 &t1, T2 &t2) -> decltype(t1*t2) {
    return t1 * t2;
}

// cpp98中相同类型的都是可以用泛型返回值的，所以cpp11中引入的追踪类型返回值是很大的拓展了泛型类型组合的能力，但是实际中使用并不多的。
template<typename T>
T SumSameType(T t1, T t2)
{
    return t1+t2;
}

// 普通函数也可以用追踪返回类型语法
auto NormalAddTest(int a, char c) -> int;

// 追踪返回类型语法，可以简化多重函数指针的写法。
//int ( *(*pf())() ) (); // (*pf())()是根据pf()返回类型的一个函数指针，外面的int*是一个指向该函数指针的指针
//auto pf1() -> auto(*)() -> int(*)(); // pf1是一个指向int(*)()类型的函数指针，然后指向auto(*)()类型的函数指针。pf1和pf是一样的，但是更加简单。
//auto (*pf3)() -> int; // 等价于int(*pf3)();
//int frOrigin();
//int(&fr)() = frOrigin; // 函数引用声明时候就要初始化
//auto (&fr2)() -> int = frOrigin; // 等价于int(&fr)();

// 追踪返回类型，可以广泛的用于转发，转发的需求是根据不同输入参数，得到不同目标函数返回类型（一般使用相同类型的有右值引用实现完美转发即可)
double foo(int i);
int foo(double d);
template <typename T>
auto Forward(T t) -> decltype(foo(t))
{
    return foo(t);
}

void PrintTraceTypeTest();
#endif /* TraceTemplateReturnType_hpp */
